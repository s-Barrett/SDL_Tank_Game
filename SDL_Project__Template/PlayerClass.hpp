#pragma once
#include "GameObject.hpp"
#include "iostream"
#include "ProjectileClass.hpp"

class Player : public GameObject
{
public:
    Player(float p_x, float p_y, SDL_Texture* p_tex);
    void handleInput(SDL_Event& event, std::vector<Projectile>& projectiles, SDL_Texture* projectileTexture, float mouseX, float mouseY);
    void move(GameObject& p_GameObject);
    void update(GameObject& p_GameObject, std::vector<Projectile>& projectiles);
    int lastTime = SDL_GetTicks();
    bool isDead() const;
private:

    float velocityX = 0;
    float velocityY = 0;
    float speedX = 15; 
    float speedY = 15;
    int mouseX = 0;
    int mouseY = 0;
    float m_width = 0;
    float m_height = 0;
    bool m_dead;
};