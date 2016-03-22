#include "GameObjects.h"
#include "GameObjectManager.h"

GameObject::GameObject(Vec2f& spawnPosition)
{
    m_center = spawnPosition;
}

void GameObject::update(float fDeltaTime, std::vector<Action>& playerInputs)
{
    m_center = m_center + m_velocity * fDeltaTime;

    for(auto& vertex : vertices)
    {
        vertex = vertex + m_velocity * fDeltaTime;
    }

    m_velocity = m_velocity * 0.992f;

    m_velocity.limit(0.15f);
}

const Vec2f& GameObject::getPosition()
{
    return m_center;
}

const std::vector<Vec2f>& GameObject::getVertices()
{
    return vertices;
}

PlayerVehicle::PlayerVehicle(Vec2f& spawnPosition, int color): GameObject(spawnPosition)
{
    m_iColor = color;

    vertices.resize(3);

    // Top
    vertices[0] = Vec2f{m_center.x, m_center.y + 10};
    // Left
    vertices[1] = {m_center.x - 10, m_center.y - 10};
    // Right
    vertices[2] = {m_center.x + 10, m_center.y - 10};

    m_fMS = 0.10f;
}

void PlayerVehicle::update(float fDeltaTime, std::vector<Action>& playerInputs)
{
    Vec2f projectileVel;

    if (m_shootOnCD)
    {
        m_CDtime += fDeltaTime;

        if (m_CDtime >= 500)
        {
            m_CDtime = 0;
            m_shootOnCD = false;
        }
    }

    for (auto& action : playerInputs)
    {
        if (action == Action::MoveUp)
        {
           m_velocity = m_velocity - Vec2f(0.f, m_fMS);
        }

        if (action == Action::MoveDown)
        {
           m_velocity = m_velocity + Vec2f(0.f, m_fMS);
        }

        if (action == Action::MoveLeft)
        {
            m_velocity = m_velocity - Vec2f(m_fMS, 0.f);
        }

        if (action == Action::MoveRight)
        {
            m_velocity = m_velocity + Vec2f(m_fMS, 0.f);
        }

        if (!m_shootOnCD)
        {
            if (action == Action::ShootUp)
            {
                projectileVel = projectileVel + Vec2f(0.f, -m_projMS);
            }

            if (action == Action::ShootDown)
            {
                projectileVel = projectileVel + Vec2f(0.f, m_projMS);
            }

            if (action == Action::ShootLeft)
            {
                projectileVel = projectileVel + Vec2f(-m_projMS, 0.f);
            }

            if (action == Action::ShootRight)
            {
                projectileVel = projectileVel + Vec2f(m_projMS, 0.f);
            }
        }
    }

    if (projectileVel.x != 0 || projectileVel.y != 0)
    {
        GameObjectManager::getInstance().spawnProjectile(projectileVel);
        m_shootOnCD = true;
    }

    GameObject::update(fDeltaTime, playerInputs);
}

void PlayerVehicle::render(SDL_Renderer* renderer)
{
    trigonColor(renderer, vertices[0].x, vertices[0].y, vertices[1].x ,vertices[1].y, vertices[2].x, vertices[2].y, m_iColor);
}

Obstacle::Obstacle(Vec2f& spawnPosition, float radius, int color) : GameObject(spawnPosition)
{
    m_iColor = color;
    m_fRadius = radius;
}

void Obstacle::render(SDL_Renderer* renderer)
{
    circleColor(renderer, m_center.x, m_center.y, m_fRadius, m_iColor);
}

float Obstacle::getRadius()
{
    return m_fRadius;
}

void Projectile::update(float fDeltaTime, std::vector<Action>& playerInputs)
{
    m_fTTL += fDeltaTime;
    m_velocity = m_constVel;
    Obstacle::update(fDeltaTime, playerInputs);
}

bool Projectile::hasExceededTTL()
{
    return (m_fTTL >= 5000);
}
