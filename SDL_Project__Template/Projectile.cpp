#include "ProjectileClass.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"

Projectile::Projectile(float p_x, float p_y, SDL_Texture* p_tex)
    : GameObject(p_x, p_y, p_tex)
{
   
}



void Projectile::setVelocityX(float VX)//setters
{
    velocityX = VX;
}
void Projectile::setVelocityY(float VY)
{
    velocityY = VY;
}


 


void Projectile::update(GameObject& p_GameObject)
{

    int currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    p_GameObject.setX(p_GameObject.getX() + velocityX * deltaTime);// update projectile position based on velocity
    p_GameObject.setY(p_GameObject.getY() + velocityY * deltaTime);

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
    };

    SDL_Rect projectilecollition;
    projectilecollition.x = p_GameObject.getX() * 3;
    projectilecollition.y = p_GameObject.getY() * 3;
    projectilecollition.w = p_GameObject.getCurrentFrame().w / 2;
    projectilecollition.h = p_GameObject.getCurrentFrame().h / 2;

    int numWalls = sizeof(walls) / sizeof(walls[0]);

    for (int i = 0; i < 14; i++) {
        // check for overlap between CollitionObj and wall

        if (SDL_HasIntersection(&projectilecollition, &walls[i])) {// collition check for walls and projectile if so reverse movement


            // determine direction of collision
            int dx = (projectilecollition.x + projectilecollition.w / 2) - (walls[i].x + walls[i].w / 2);
            int dy = (projectilecollition.y + projectilecollition.h / 2) - (walls[i].y + walls[i].h / 2);
            int width = (projectilecollition.w + walls[i].w) / 2;
            int height = (projectilecollition.h + walls[i].h) / 2;
            int crossWidth = width * dy;
            int crossHeight = height * dx;

            int m_y = p_GameObject.getY();
            int m_x = p_GameObject.getX();


            if (abs(dx) <= width && abs(dy) <= height) {

                if (crossWidth > crossHeight) {
                    if (crossWidth > -crossHeight) {

                        p_GameObject.setY(walls[i].y / 3 + walls[i].h / 3 + 3);
                        velocityY *= -1;
                        m_y += velocityY * deltaTime;
                    }
                    else {

                        p_GameObject.setX(walls[i].x / 3 - projectilecollition.w / 3 - 3);
                        velocityX *= -1;
                        m_x += velocityX * deltaTime;
                    }
                }
                else {
                    if (crossWidth > -crossHeight) {

                        p_GameObject.setX(walls[i].x / 3 + walls[i].w / 3 + 3);
                        velocityX *= -1;
                        m_x += velocityX * deltaTime;
                    }
                    else {

                        p_GameObject.setY(walls[i].y / 3 - projectilecollition.h / 3 - 3);
                        velocityY *= -1;
                        m_y += velocityY * deltaTime;
                    }
                }
            }
        }
    }







}