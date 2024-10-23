#pragma once
#include "GameObject.hpp"
#include "iostream"
#include <Windows.h>


class Projectile : public GameObject
{
public:
    Projectile(float p_x, float p_y, SDL_Texture* p_tex);
    void update(GameObject& p_GameObject);
    void setVelocityY(float VY);
    void setVelocityX(float VX);
    int lastTime = SDL_GetTicks();
private:
    int mouseX = 0;
    int mouseY = 0;
    float velocityX = 0;
    float velocityY = 0;
    float speedX = 0;
    float speedY = 0;

};