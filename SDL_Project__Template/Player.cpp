#include "PlayerClass.hpp"
#include "SDL.h"
#include "GameObject.hpp"
#include "ProjectileClass.hpp"
#include <windows.h>


Player::Player(float p_x, float p_y, SDL_Texture* p_tex)
    : GameObject(p_x, p_y, p_tex)
{
    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    m_width = static_cast<float>(w);
    m_height = static_cast<float>(h);
}


void Player::handleInput(SDL_Event& event, std::vector<Projectile>& projectiles, SDL_Texture* projectileTexture,float mouseX, float mouseY)// input handler for player
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {

        switch (event.key.keysym.sym)// wasd for movement keys
        {
        case SDLK_w:
            velocityY -= speedY;
            break;
        case SDLK_s:
            velocityY += speedY;
            break;
        case SDLK_a:
            velocityX -= speedX;
            break;
        case SDLK_d:
            velocityX += speedX;
            break;
        }

    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            velocityY += speedY;
            break;
        case SDLK_s:
            velocityY -= speedY;
            break;
        case SDLK_a:
            velocityX += speedX;
            break;
        case SDLK_d:
            velocityX -= speedX;
            break;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)// left mouse for shootign then setting the projectiles speed moving it to velocity then updating it
    {
     

        float dx = mouseX - getX() * 3;
        float dy = mouseY - getY() * 3;


        float distance = std::sqrt(dx * dx + dy * dy);
        float dirX = dx / distance;
        float dirY = dy / distance;

        float speed = 50.0f;
        float velocityX = speed * dirX;
        float velocityY = speed * dirY;

        float spawnX = getX() + (m_width / 2 - 10); // Adjust the spawn position as needed
        float spawnY = getY() + (m_height / 2 - 10);

        projectiles.emplace_back(Projectile(spawnX, spawnY, projectileTexture));
        projectiles.back().setVelocityX(velocityX);
        projectiles.back().setVelocityY(velocityY);

        Beep(100, 10);// sound for when player shoots
    }
}


void Player::move(GameObject& p_GameObject)
{

    float currentTime = SDL_GetTicks(); // get the current time
    float deltaTime = (currentTime - lastTime) / 1000.0f; // calculate deltaTime in seconds
    lastTime = currentTime; // update lastTime

    float newX = p_GameObject.getX() + velocityX * deltaTime;
    float newY = p_GameObject.getY() + velocityY * deltaTime;
    p_GameObject.setX(newX);
    p_GameObject.setY(newY);//move player to newx and y

}

void Player::update(GameObject& p_GameObject, std::vector<Projectile>& projectiles)
{

    SDL_Rect playerCollision;
    playerCollision.x = p_GameObject.getX() * 3;//players collition 
    playerCollision.y = p_GameObject.getY() * 3;
    playerCollision.w = p_GameObject.getCurrentFrame().w;
    playerCollision.h = p_GameObject.getCurrentFrame().h;

    for (Projectile& projectile : projectiles)
    {
        SDL_Rect projectileCollision;
        projectileCollision.x = projectile.getX() * 3;
        projectileCollision.y = projectile.getY() * 3;
        projectileCollision.w = projectile.getCurrentFrame().w / 4;
        projectileCollision.h = projectile.getCurrentFrame().h / 4;


        if (SDL_HasIntersection(&playerCollision, &projectileCollision))// see if player collition has intersection with projectile if true player dies
        {
            std::cout << "player hit" << std::endl;
            m_dead = true;
        }
    }



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
    { 0, 0, 800, 10 },
    { 0, 580, 800, 20 },
    { 0, 0, 10, 800 },
    { 780, 0, 20, 800 }
  };

    int numWalls = sizeof(walls) / sizeof(walls[0]);



    for (int i = 0; i < numWalls; i++) {
        // check for overlap between CollitionObj and wall

        if (SDL_HasIntersection(&playerCollision, &walls[i])) {// see if player had intersection with walls if sound reverse the direction 

            //std::cout << "is colliding" << std::endl;

            // determine direction of collision
            int dx = (playerCollision.x + playerCollision.w / 2) - (walls[i].x + walls[i].w / 2);
            int dy = (playerCollision.y + playerCollision.h / 2) - (walls[i].y + walls[i].h / 2);
            int width = (playerCollision.w + walls[i].w) / 2;
            int height = (playerCollision.h + walls[i].h) / 2;
            int crossWidth = width * dy;
            int crossHeight = height * dx;

            if (abs(dx) <= width && abs(dy) <= height) {
                //collision detected adjust players position
                if (crossWidth > crossHeight) {
                    if (crossWidth > -crossHeight) {
                        //collision on bottom side of wall
                        p_GameObject.setY(walls[i].y / 3 + walls[i].h / 3 + 1);
                    }
                    else {
                        //collision on left side of wall
                        p_GameObject.setX(walls[i].x / 3 - playerCollision.w / 3 - 1);
                    }
                }
                else {
                    if (crossWidth > -crossHeight) {
                        //collision on right side of wall
                        p_GameObject.setX(walls[i].x / 3 + walls[i].w / 3 + 1);
                    }
                    else {
                        // collision on top side of wall
                        p_GameObject.setY(walls[i].y / 3 - playerCollision.h / 3 - 1);
                    }
                }
            }
        }
    }


}

bool Player::isDead() const
{
    return m_dead;
}