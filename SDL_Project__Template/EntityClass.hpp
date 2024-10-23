#pragma once
#include "GameObject.hpp"
#include "GameObject.hpp"
#include "ProjectileClass.hpp"
#include "Game.hpp"
#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib> 

class Entity : public GameObject
{
public:
    Entity(float x, float y, SDL_Texture* texture);
    void update(GameObject& p_GameObject, GameObject& player, std::vector<Projectile>& projectiles, std::vector<Projectile>& playerprojectiles, SDL_Texture* projectileTexture);
    void shootAtPlayer(GameObject& player, std::vector<Projectile>& projectiles, SDL_Texture* projectileTexture);
    float lerp(float a, float b, float t);
    bool isDead() const;
private:
    float x, y;
    float m_shootInterval;
    float m_lastShootTime;
    int lastTime;
    int m_lerpFactor = 5;
    float m_velocityX = 0.0;
    float m_velocityY = 0.0;
    float m_acceleration = 0.5;
    float m_maxSpeed = 2.0;
    float directionX = 0.0f; 
    float directionY = 0.0f;
    float m_x;
    float m_y;
    float m_width = 0;
    float m_height = 0;
    bool m_dead;
};