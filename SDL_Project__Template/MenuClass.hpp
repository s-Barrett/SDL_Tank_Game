#pragma once
#include "Game.hpp"


class Menu
{
public:
	Menu();
	void renderMenuItems(RenderWindow& window, SDL_Texture* menuTextures[]);
	int menuloop();
	void play();
	int options();
	int howtoplay(RenderWindow& window, GameObject& background);
private:

};