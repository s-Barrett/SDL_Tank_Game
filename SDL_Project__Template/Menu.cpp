#include "MenuClass.hpp"
#include <SDL_mixer.h>


Menu::Menu()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize!\n";
	}
    if (TTF_Init() == -1)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;// initilise everything
    }
}

void Menu::renderMenuItems(RenderWindow& window, SDL_Texture* menuTextures[])
{
    for (int i = 0; i < 4; ++i)
    {
        SDL_Rect textRect = { 300, 100 + i * 100, 200, 50 };
        SDL_RenderCopy(window.getRenderer(), menuTextures[i], nullptr, &textRect); // create Rects for the menu buttons
    }
}

int Menu::menuloop()
{
	//Game MyGame;
	bool exitFlag{ false };

	do
	{

		RenderWindow window("Menu", 800, 600);// window creation and window size

        SDL_Texture* menuBackGround = window.loadTexture("MenuBackground.bmp");
        SDL_Texture * howtoplayBackground = window.loadTexture("HowToPlayBackground.bmp");// pointers to all the bmps
		SDL_Texture* menuTextures[4];
		menuTextures[0] = window.loadTexture("StartButton.bmp");
		menuTextures[1] = window.loadTexture("HowToPlayButton.bmp");
		menuTextures[2] = window.loadTexture("OptionsButton.bmp");
		menuTextures[3] = window.loadTexture("ExitButton.bmp");

        GameObject htpBackground(0, 0, howtoplayBackground);
        GameObject menuBackground(0, 0, menuBackGround);

        SDL_Event event;
        while (!exitFlag)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    exitFlag = true;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);// mouse state to see what button is pressed

                    for (int i = 0; i < 4; ++i)
                    {
                        SDL_Rect itemRect = { 200, 100 + i * 100, 200, 50 };
                        if (x >= itemRect.x && x <= (itemRect.x + itemRect.w) && y >= itemRect.y && y <= (itemRect.y + itemRect.h))// if mouse overlaps button and left mouse is clicked jump to said case statment
                        {
                            switch (i)
                            {
                            case 0:
                                window.tidyUp();
                                play();
                                break;
                            case 1:
                                howtoplay(window, htpBackground);
                                break;
                            case 2:
                                options();
                                break;
                            case 3:
                                window.tidyUp();
                                exitFlag = true;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }

            window.clear();
            window.renderBackground(menuBackground);//render the background
            renderMenuItems(window, menuTextures); //render the menu items
            window.display();

            SDL_Delay(16); // cap the frame rate (about 60 FPS)
        }

        // clean up the textures before exiting the loop
        for (int i = 0; i < 4; ++i)
        {
            SDL_DestroyTexture(menuTextures[i]);
        }
        SDL_DestroyTexture(menuBackGround);

    } while (exitFlag == false);

    SDL_Quit();
    return 0;
}


void Menu::play()
{
	Game* MyGame = new Game();
	delete MyGame;
}

int Menu::options()
{
   
	return 0;
}
int Menu::howtoplay(RenderWindow& window, GameObject& htpBackground)
{

    window.clear();
    window.renderBackground(htpBackground);
    window.display();
    SDL_Delay(10000);
    window.tidyUp();
    play();

	return 0;
}

