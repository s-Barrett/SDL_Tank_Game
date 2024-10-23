#include "Game.hpp"
#include "MenuClass.hpp"
#include <cstdlib>
#include <SDL_mixer.h>

Menu MyMenu;


Game::Game()  
{
    Menu MyMenu;

    RenderWindow window("TANK GAME v1.0", 800, 600);

    SDL_Texture* backgroundTexture = window.loadTexture("background.bmp");//all the pointers for textures sounds fonts
    SDL_Texture* playerTexture = window.loadTexture("tankRed.bmp");
    SDL_Texture* EntityTexture = window.loadTexture("tankBlue.bmp");
    SDL_Texture* enemyprojectileTexture = window.loadTexture("enemyProjectile.bmp");
    SDL_Texture* playerprojectileTexture = window.loadTexture("playerProjectile.bmp");
    SDL_Texture* deadTexture = window.loadTexture("deadText.bmp");
    SDL_Texture* wonTexture = window.loadTexture("wonText.bmp");

    Mix_Chunk* explosion = Mix_LoadWAV("enemyDeath.ogg");
    TTF_Font* font = TTF_OpenFont("PP.ttf", 20);
    Mix_Music* music = Mix_LoadMUS("BackingTrack.ogg");


    GameObject background(0, 0, backgroundTexture);// creating all the gameobject classes
    GameObject deadtext(0, 0, deadTexture);
    GameObject wontext(0, 0, wonTexture);
    Player player(10, 10, playerTexture);
    
    
    int score = 0;

    std::vector<Entity> entitees = { Entity(40, 150, EntityTexture),// making entity vectors
                                    Entity(180, 160, EntityTexture),
                                    Entity(90, 100, EntityTexture),
                                    Entity(180, 20, EntityTexture) };


    std::vector<Projectile> projectiles;// making projectile vectors
    std::vector<Projectile> playerprojectiles;

    Mix_PlayMusic(music, -1);
 

    bool gameover = false;

    while (gameover == false)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Event event;
        while (SDL_PollEvent(&event) == true)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = true;
                break;
            default:
                player.handleInput(event, playerprojectiles, playerprojectileTexture, mouseX, mouseY);// player input handle
                break;
            }
        }



        //gameloop

        

        window.clear();
        window.renderBackground(background);

       

        window.renderplayer(player, mouseX, mouseY);
       

        player.move(player);
        player.update(player, projectiles);

        window.renderScore(window, font, score);


        for (Entity& renderEntitys : entitees)
        {
            window.renderenemy(renderEntitys, player);
        }
        for (Entity& updateEntitys : entitees)
        {
            updateEntitys.update(updateEntitys, player, projectiles, playerprojectiles , enemyprojectileTexture);

        }

        for (Projectile& proj : projectiles)
        {
            window.renderprojectile(proj);
            proj.update(proj);
        }


        for (Projectile& playerproj : playerprojectiles)
        {
            window.renderprojectile(playerproj);
            playerproj.update(playerproj);
        }
        //remove dead projectiles
        
     
        for (auto it = entitees.begin(); it != entitees.end();)
        {
            if (it->isDead())
            {
                score += 100;// add score when entity dies
                it = entitees.erase(it);
                Mix_PlayChannel(-1, explosion, 0);// play explotion sound when entity dies
            }
            else
            {
                ++it;
            }
        }
     
        if (player.isDead() == true)
        {
            SDL_Delay(1000);
            window.clear();
            window.renderBackground(deadtext);
            window.display();
            SDL_Delay(2000);
            window.tidyUp();
            MyMenu.menuloop();//when player dies clean up and take back to menu
      
        }
       
        bool allEntitiesDead = true;
        for (const auto& entity : entitees)
        {
            if (!entity.isDead())
            {
                allEntitiesDead = false;
                break;
            }
        }

  
        if (allEntitiesDead)
        {
            SDL_Delay(1000);
            window.clear();
            window.renderBackground(wontext);
            window.display();
            SDL_Delay(2000);
            window.tidyUp();
            MyMenu.menuloop();//when all entitys die clean up and take back to menu
      
        }
        
        SDL_Delay(16);

        window.display();
   



    }
    TTF_CloseFont(font);// close fonts 
    TTF_Quit();
}



