#pragma once
#include <SDL.h>
#include <vector>


class GameObject
{
public:
    GameObject(float p_x, float p_y, SDL_Texture* p_tex);
    float getX();
    float getY();
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    void setX(float p_x);
    void setY(float p_y);
    void setTex(SDL_Texture* p_tex);
    void setCurrentFrame(SDL_Rect p_currentFrame);
private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};