#include "iostream"
#include "RenderWindow.hpp"
#include "SDL.h"
#include "GameObject.hpp"
#include <sstream>
#include <cmath>

RenderWindow::RenderWindow(const char* p_winname, int p_w, int p_h)
{
    window = SDL_CreateWindow(p_winname, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
    std::cout << "Window could not be created!\n" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Renderer could not be created!\n" << SDL_GetError() << std::endl;
    }
}

SDL_Surface* RenderWindow::loadSurface(const char* p_file) //loading surface
{
    SDL_Surface* surface = SDL_LoadBMP(p_file);
    if (surface == NULL) {
        std::cout << "Could not load surface: " << SDL_GetError() << std::endl;
    }
    return surface;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_file) // loading texture from surface
{
    SDL_Surface* surface = loadSurface(p_file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void RenderWindow::tidyUp()// used when moving from menu to game and game to menu
{
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit;
}

void RenderWindow::clear() // free the renderer
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderScore(RenderWindow& window, TTF_Font* font, int score)
{
    if (!font)
    {
        std::cout << "TTF_Font not initialized!" << std::endl;
        return;
    }

    SDL_Color textColor = { 255, 255, 255 }; // White text color
    std::stringstream scoreStream;
    scoreStream << "Score: " << score;
    std::string scoreText = scoreStream.str();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);

    if (!textSurface)
    {
        std::cout << "TTF_RenderText_Solid failed! TTF Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);

    if (!textTexture)
    {
        std::cout << "SDL_CreateTextureFromSurface failed! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h };
    SDL_RenderCopy(window.getRenderer(), textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void RenderWindow::renderplayer(GameObject& p_GameObject, float mouseX, float mouseY)// used to render player 
{
    SDL_Rect src;
    src.x = p_GameObject.getCurrentFrame().x;
    src.y = p_GameObject.getCurrentFrame().y;
    src.w = p_GameObject.getCurrentFrame().w;
    src.h = p_GameObject.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_GameObject.getX() * 3;
    dst.y = p_GameObject.getY() * 3;
    dst.w = 23 * 2;
    dst.h = 23 * 2;


    float dx = mouseX - dst.x;
    float dy = mouseY - dst.y;
    float angle = std::atan2(dy, dx) * 180 / M_PI;


    SDL_RenderCopyEx(renderer, p_GameObject.getTex(), &src, &dst, angle, NULL, SDL_FLIP_NONE);// needed to use rendercopyEX and i wanted the player to look at the mouse and this outputs an angle 
}

void RenderWindow::renderenemy(GameObject& entity, GameObject& player)
{

    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = entity.getX() * 3;
    dst.y = entity.getY() * 3;
    dst.w = 23 * 2;
    dst.h = 23 * 2;



    float dx = player.getX() - entity.getX();
    float dy = player.getY() - entity.getY();
    float angle = std::atan2(dy, dx) * 180 / M_PI;

    SDL_RenderCopyEx(renderer, entity.getTex(), &src, &dst, angle, NULL, SDL_FLIP_NONE);//same with this wanted the entity to look at the player 
}

void RenderWindow::renderprojectile(GameObject& p_GameObject)
{
    SDL_Rect src;
    src.x = p_GameObject.getCurrentFrame().x;
    src.y = p_GameObject.getCurrentFrame().y;
    src.w = p_GameObject.getCurrentFrame().w;
    src.h = p_GameObject.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_GameObject.getX() * 3;
    dst.y = p_GameObject.getY() * 3;
    dst.w = 7;
    dst.h = 7;

   SDL_RenderFillRect(renderer, &dst);


    SDL_RenderCopy(renderer, p_GameObject.getTex(), &src, &dst);
}


void RenderWindow::renderBackground(GameObject& p_GameObject)
{
    SDL_RenderCopy(renderer, p_GameObject.getTex(), NULL, NULL);// left last two as NULL so it would fill screen no matter the res
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::showBoundingBoxes()// this was just for when i was creating the bounding boxes 
{
    SDL_Rect walls[] = {
    { 100, 75, 75, 90 },
    { 175, 75, 125, 20 },
    { 500, 100, 140, 105 },
    { 235, 190, 100, 70 },
    { 100, 300, 20, 85 },
    { 100, 300, 125, 20 },
    { 485, 420, 25, 110 },
    { 675, 420, 25, 110 },
    { 470, 345, 215, 20 },
    { 85, 505, 275, 20 },
    { 300, 370, 65, 25 },
    { 300, 370, 25, 80 },
    { 180, 430, 120, 20 },
    { 0, 0, 800, 20 },
    { 0, 580, 800, 20 },
    { 0, 0, 20, 800 },
    { 780, 0, 20, 800 }
    };

    int numwalls = sizeof(walls) / sizeof(walls[0]); 

    for (int i = 0; i < numwalls; i++)
    {
        SDL_RenderFillRect(renderer, &walls[i]);
    }


}

SDL_Renderer* RenderWindow::getRenderer()// getter 
{
    return renderer;
}

