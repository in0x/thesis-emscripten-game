#include "GameObjectManager.h"

void GameObjectManager::spawnPlayer(Vec2f& spawnPosition)
{
    if (player == nullptr)
    {
        player = std::make_shared<PlayerVehicle>(spawnPosition);
    }
}

void GameObjectManager::createRenderText(const std::string& text, const std::string& fontPath, const SDL_Color& color, SDL_Renderer* renderer, int textSize, int rectPosX, int rectPosY, int rectWidth, int rectHeight)
{
    SDL_Rect box{};
    box.x = rectPosX;
    box.y = rectPosY;
    box.w = rectWidth;
    box.h = rectHeight;

    textBoxes.push_back(
    {
        std::make_shared<RenderText>(fontPath, textSize, color, text, renderer),
        std::move(box)
    });
}

// renderAll()
// Iterates over all collections of GameObjects and renders them
void GameObjectManager::renderAll(SDL_Renderer* renderer)
{
    player->render(renderer);

    for (auto& obstacle : obstacles)
    {
        obstacle->render(renderer);
    }

    for (auto& projectile : projectiles)
    {
        projectile->render(renderer);
    }

    for (auto& attacks : attackingProj)
    {
        attacks->render(renderer);
    }

    for (auto& textBox : textBoxes)
    {
        std::get<0>(textBox)->render(renderer, std::get<1>(textBox));
    }
}

// updateAll()
// Calls the update function of all spawned GameObjects, providing them with input and the frame time
// Also controls the spawning of attacks at the player and the related cooldown
void GameObjectManager::updateAll(float fDeltaTime, std::vector<Action>& playerInputs)
{
    player->update(fDeltaTime, playerInputs);

    for (auto& obstacle : obstacles)
    {
        obstacle->update(fDeltaTime, playerInputs);
    }

    for (auto& attacks : attackingProj)
    {
        attacks->update(fDeltaTime, playerInputs);
    }

    // Iterator is used to make removal of objects from collection
    // during iteration possible
    for (auto proj_it = projectiles.begin(); proj_it != projectiles.end();)
    {
        (*proj_it)->update(fDeltaTime, playerInputs);

        if ((*proj_it)->hasExceededTTL())
        {
            proj_it = projectiles.erase(proj_it);
        }
        else
        {
            proj_it++;
        }
    }

    if (m_bSpawnOnCD)
    {
        m_fCDTime += fDeltaTime;

        if (m_fCDTime >= 1000)
        {
            m_bSpawnOnCD = false;
            m_fCDTime = 0.f;
        }
    }
    else
    {
        spawnAttackAtPlayer();
        m_bSpawnOnCD = true;
    }
}

bool GameObjectManager::checkCollisions()
{
    for (auto& obstacle : obstacles)
    {
        if ((obstacle->getPosition() - player->getPosition()).length() < obstacle->getRadius())
        {
            return true;
        }
    }

    for (auto attack_it = attackingProj.begin(); attack_it != attackingProj.end();)
    {
        bool deleteThisIter = false;

        // Check if projectile hit an attack
        for (auto proj_it = projectiles.begin(); proj_it != projectiles.end();)
        {
            // If yes, delete the projectile now and set the according flag
            if (((*attack_it)->getPosition() - (*proj_it)->getPosition()).length() < ((*attack_it)->getRadius() + (*proj_it)->getRadius()))
            {
                deleteThisIter = true;
                proj_it = projectiles.erase(proj_it);
                attack_it = attackingProj.erase(attack_it);
            }
            else
            {
                proj_it++;
            }
        }

        if (!deleteThisIter)
        {
            if (((*attack_it)->getPosition() - player->getPosition()).length() < (*attack_it)->getRadius())
            {
                return true;
            }
            attack_it++;
        }
    }

    return false;
}

// getInstance()
// Returns the a reference to the single instance of GameObjectManager
// and creates it if unitialized
GameObjectManager& GameObjectManager::getInstance()
{
    static std::shared_ptr<GameObjectManager> instance = nullptr;

    if (instance == nullptr)
    {
        instance = std::make_shared<GameObjectManager>();
    }

    return *instance;
}

// spawnObstacle()
// Test location of existing obstacles for checkCollisions
// and spawns new obstacle if possible
bool GameObjectManager::spawnObstacle(Vec2f& spawnPos, float radius)
{
    if (obstacles.size() == 0)
    {
        obstacles.push_back(std::make_shared<Obstacle>(spawnPos, radius));
        return true;
    }
    else
    {
        for (auto& other : obstacles)
        {
            if ((other->getPosition() - spawnPos).length() < radius + other->getRadius())
            {
                return false;
            }
        }
    }

    obstacles.push_back(std::make_shared<Obstacle>(spawnPos, radius));
    return true;
}

// spawnObstacles()
// Should be called once, at startup
void GameObjectManager::spawnObstacles(int windowX, int windowY, int numOfObstacles, int maxObstacleRadius, int maxTries)
{
    int i;
    float radius = 0;

    for (i = 0; i < numOfObstacles; i++)
    {
        for (int tries = 0; tries <= maxTries; tries++)
        {
            Vec2f spawnPos{float(rand() % windowX), float(rand() % windowY)};

            if (spawnPos.x > windowX || spawnPos.y > windowY) continue;

            radius = (rand() % (maxObstacleRadius - 10)) + 10;

            if (spawnObstacle(spawnPos, radius)) break;
        }
    }
}

// spawnProjectile()
// Responsible for creating a projectile shot by the player
void GameObjectManager::spawnProjectile(Vec2f& vel)
{
    Vec2f spawnPos = player->getPosition();
    projectiles.push_back(std::make_shared<Projectile>(spawnPos, 5, vel));
}

// spawnAttackAtPlayer()
// Finds a spawn position for attack, creates it and shoots it at player
void GameObjectManager::spawnAttackAtPlayer()
{
    RNG rng = RNG::get();
    // Get a random number between 0 and 3 to select a side to spawn outside of
	int sideToSpawnOn = rng.randomRange(0, 4);

	// For readability
	enum ScreenSide
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	int spawnX = 0;
	int spawnY = 0;

	// Select a box to spawn in, which 100 x the Window Dimension of the selected edge
	switch (sideToSpawnOn)
	{
	case ScreenSide::TOP:
		spawnX = rng.randomRange(X_SAFEREGION_MIN, X_SAFEREGION_MAX);
		spawnY = rng.randomRange(0, Y_SAFEREGION_MIN);
		break;

	case ScreenSide::BOTTOM:
		spawnX = rng.randomRange(X_SAFEREGION_MIN, X_SAFEREGION_MAX);
		spawnY = rng.randomRange(Y_SAFEREGION_MAX - 100, Y_SAFEREGION_MAX);
		break;

	case ScreenSide::LEFT:
		spawnX = rng.randomRange(0, X_SAFEREGION_MIN);
		spawnY = rng.randomRange(Y_SAFEREGION_MIN, Y_SAFEREGION_MAX);
		break;

	case ScreenSide::RIGHT:
		spawnX = rng.randomRange(X_SAFEREGION_MAX - 100, X_SAFEREGION_MAX);
		spawnY = rng.randomRange(Y_SAFEREGION_MIN, Y_SAFEREGION_MAX);
		break;

	}

	Vec2f spawnPos{ (float)spawnX, (float)spawnY };

	// Shoot the asteroid in the direction of the player
	Vec2f direction = (player->getPosition() - spawnPos);
    direction.normalize();
    direction = direction * 0.5;

	attackingProj.push_back(std::make_shared<Projectile>(spawnPos, rng.randomRange(5, 50), direction, 0xFFFF0000));
}
