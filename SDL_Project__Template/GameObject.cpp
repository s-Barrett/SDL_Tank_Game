#include "GameObject.hpp"


GameObject::GameObject(float p_x, float p_y, SDL_Texture* p_tex)
{
    x = p_x;
    y = p_y;
    tex = p_tex;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

float GameObject::getX() //getters
{
    return x;
}

float GameObject::getY() 
{
    return y;
}

SDL_Texture* GameObject::getTex()
{
    return tex;
}

SDL_Rect GameObject::getCurrentFrame()
{
    return currentFrame;
}

void GameObject::setCurrentFrame(SDL_Rect p_currentFrame) //setters
{
    currentFrame = p_currentFrame;
}

void GameObject::setX(float p_x)
{
    x = p_x;
}

void GameObject::setY(float p_y)
{
    y = p_y;
}

void GameObject::setTex(SDL_Texture* p_tex)
{
    tex = p_tex;
}

