#pragma once
#include "SDL.h"
#include "GameObject.hpp"
#include <vector>
#include "SDL_ttf.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_winname, int p_w, int p_h);
	SDL_Surface* loadSurface(const char* p_file);
	SDL_Texture* loadTexture(const char* p_file);
	void renderBackground(GameObject& p_GameObject);
	void renderplayer(GameObject& p_GameObject, float mouseX, float mouseY);
	void renderenemy(GameObject& entity, GameObject& player);
	void renderprojectile(GameObject& p_GameObject);
	void renderScore(RenderWindow& window, TTF_Font* font, int score);
	void tidyUp();
	void clear();
	void display();
	SDL_Renderer* getRenderer();
	void showBoundingBoxes();
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
};