#ifndef GAMEOBJECTMANAGER_HPP_INCLUDED
#define GAMEOBJECTMANAGER_HPP_INCLUDED

#include "stdafx.h"
#include "GameObjects.h"
#include "rendertext.h"

/*
    GameObjectManager
    A singleton class that holds the resources for all projectiles, obstacles and the player
    Responsible for creation, destruction and interaction of all GameObjects
*/

class GameObjectManager
{
public:
    GameObjectManager() : m_bSpawnOnCD(false), m_fCDTime(0.f) { }

    void spawnPlayer(Vec2f& spawnPosition);

    void updateAll(float fDeltaTime, std::vector<Action>& playerInputs);

    void renderAll(SDL_Renderer* renderer);

    void spawnObstacles(int windowX, int windowY, int numOfObstacles, int maxObstacleRadius, int maxTries = 3);

    bool checkCollisions();

    void spawnProjectile(Vec2f& vel);

    void createRenderText(const std::string& text, const std::string& fontPath,
        const SDL_Color& color, SDL_Renderer* renderer, int textSize,
        int rectPosX, int rectPosY, int rectWidth, int rectHeight);

    static GameObjectManager& getInstance();

private:
    void spawnAttackAtPlayer();

    bool spawnObstacle(Vec2f& spawnPos, float radius);

    // Used to control the cooldown for spawning attacks.
    bool m_bSpawnOnCD;
    float m_fCDTime;

    std::shared_ptr<PlayerVehicle> player = nullptr;

    // Holds all static obstacles.
    std::vector<std::shared_ptr<Obstacle>> obstacles;

    // Holds all projectiles shot by the player.
    std::vector<std::shared_ptr<Projectile>> projectiles;

    // Holds all randomly spawnend projectiles that are shot at the player.
    std::vector<std::shared_ptr<Projectile>> attackingProj;

    std::vector<std::tuple<std::shared_ptr<RenderText>, SDL_Rect>> textBoxes;

    // Denote the screen positions for the attack spawn boxes
    static const int X_SAFEREGION_MIN = 100;
    static const int X_SAFEREGION_MAX = 1600;
    static const int Y_SAFEREGION_MIN = 100;
    static const int Y_SAFEREGION_MAX = 900;
};

#endif // GAMEOBJECTMANAGER_HPP_INCLUDED
