#ifndef GAMEOBJECTS_HPP_INCLUDED
#define GAMEOBJECTS_HPP_INCLUDED

#include "stdafx.h"

// class GameObject
// This class represents entities within the game, such as the player and obstacles
class GameObject
{
public:
    GameObject(Vec2f& spawnPosition);
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update(float fDeltaTime, std::vector<Action>& playerInputs);
    const Vec2f& getPosition();
    const std::vector<Vec2f>& getVertices();

protected:
    Vec2f m_center {};
    Vec2f m_velocity {};

    std::vector<Vec2f> vertices{};

    unsigned int m_iColor = 0xFF000000;

    float m_fMS = 0.f;
};

class PlayerVehicle : public GameObject
{
public:
    PlayerVehicle(Vec2f& spawnPosition, int color = 0xFF0000FF);
    virtual void render(SDL_Renderer* renderer) override;
    virtual void update(float fDeltaTime, std::vector<Action>& playerInputs) override;

private:
    bool m_shootOnCD = false;
    float m_CDtime = 0.f;
    float m_projMS = 0.40f;
};

class Obstacle : public GameObject
{
public:
    Obstacle(Vec2f& spawnPosition, float radius, int color = 0xFFFF0000);
    virtual void render(SDL_Renderer* renderer) override;
    float getRadius();

private:
    float m_fRadius = 0;
};

class Projectile : public Obstacle
{
public:
    Projectile(Vec2f& spawnPosition, float radius, Vec2f& velocity, int color = 0xFF0000FF) : Obstacle(spawnPosition, radius, color)
    {
        m_constVel = velocity;
    }

    virtual void update(float fDeltaTime, std::vector<Action>& playerInputs) override;

    bool hasExceededTTL();
private:
    float m_fTTL = 0;
    Vec2f m_constVel;
};

#endif //GAMEOBJECTS_HPP_INCLUDED
