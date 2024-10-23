#include "EntityClass.hpp"
#include "SDL.h"


Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
    : GameObject(p_x, p_y, p_tex), lastTime(SDL_GetTicks()), m_width(20), m_height(20), m_dead(false), m_shootInterval(3000.0f), m_lastShootTime(SDL_GetTicks())
{

    int w, h;

    SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);

    m_width = static_cast<float>(w);
    m_height = static_cast<float>(h);

    m_x = getX();
    m_y = getY();

}


void Entity::shootAtPlayer(GameObject& player, std::vector<Projectile>& projectiles, SDL_Texture* projectileTexture)//rotational location of the player
{
    float dx = player.getX() - getX();
    float dy = player.getY() - getY();


    float distance = std::sqrt(dx * dx + dy * dy);
    float dirX = dx / distance;
    float dirY = dy / distance;

    float speed = 50.0f;
    float velocityX = speed * dirX;// calculating velocity to the pass to update
    float velocityY = speed * dirY;

    float spawnX = getX() + (m_width / 2 - 10); // Adjust the spawn position that the vector will return to
    float spawnY = getY() + (m_height / 2 - 10);

    projectiles.emplace_back(Projectile(spawnX, spawnY, projectileTexture));
    projectiles.back().setVelocityX(velocityX);
    projectiles.back().setVelocityY(velocityY);
}


void Entity::update(GameObject& p_GameObject, GameObject& player, std::vector<Projectile>& projectiles, std::vector<Projectile>& playerprojectiles, SDL_Texture* projectileTexture)
{

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - m_lastShootTime > m_shootInterval) {//using a timer to delay the next shot
        shootAtPlayer(player, projectiles, projectileTexture);
        Beep(100, 20);
        m_lastShootTime = currentTime;
    }

    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    SDL_Rect walls[] = {// collition walls
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

    SDL_Rect entityCollision;
    entityCollision.x = p_GameObject.getX() * 3;
    entityCollision.y = p_GameObject.getY() * 3;
    entityCollision.w = p_GameObject.getCurrentFrame().w;
    entityCollision.h = p_GameObject.getCurrentFrame().h;

    for (Projectile& projectile : playerprojectiles)
    {
        SDL_Rect projectileCollision;
        projectileCollision.x = projectile.getX() * 3;
        projectileCollision.y = projectile.getY() * 3;
        projectileCollision.w = projectile.getCurrentFrame().w / 2;
        projectileCollision.h = projectile.getCurrentFrame().h / 2;


        if (SDL_HasIntersection(&entityCollision, &projectileCollision))
        {
            std::cout << "entity hit" << std::endl;

            m_dead = true;
        }
    }



    SDL_Rect entitycollition;
    entitycollition.x = p_GameObject.getX() * 3;
    entitycollition.y = p_GameObject.getY() * 3;
    entitycollition.w = p_GameObject.getCurrentFrame().w;
    entitycollition.h = p_GameObject.getCurrentFrame().h;

    int numWalls = sizeof(walls) / sizeof(walls[0]);

    for (int i = 0; i < 14; i++) {
        //check for overlap between entitycollition and wall

        if (SDL_HasIntersection(&entitycollition, &walls[i])) {

           
            //determine direction of collision
            int dx = (entitycollition.x + entitycollition.w / 2) - (walls[i].x + walls[i].w / 2);
            int dy = (entitycollition.y + entitycollition.h / 2) - (walls[i].y + walls[i].h / 2);
            int width = (entitycollition.w + walls[i].w) / 2;
            int height = (entitycollition.h + walls[i].h) / 2;
            int crossWidth = width * dy;
            int crossHeight = height * dx;

            if (abs(dx) <= width && abs(dy) <= height) {

                if (crossWidth > crossHeight) {
                    if (crossWidth > -crossHeight) {

                        p_GameObject.setY(walls[i].y / 3 + walls[i].h / 3);
                        m_velocityY *= -1;
                        m_y += m_velocityY * deltaTime;
                    }
                    else {

                        p_GameObject.setX(walls[i].x / 3 - entitycollition.w / 3);
                        m_velocityX *= -1;
                        m_x += m_velocityX * deltaTime;
                    }
                }
                else {
                    if (crossWidth > -crossHeight) {

                        p_GameObject.setX(walls[i].x / 3 + walls[i].w / 3);
                        m_velocityX *= -1;
                        m_x += m_velocityX * deltaTime;
                    }
                    else {

                        p_GameObject.setY(walls[i].y / 3 - entitycollition.h / 3);
                        m_velocityY *= -1;
                        m_y += m_velocityY * deltaTime;
                    }
                }
            }
        }
    }





    //change direction randomly every few seconds
    if (currentTime % 3000 < 100) {
        directionX = static_cast<float>(rand() % 3 - 1); //rand value between 3 and -1
        directionY = static_cast<float>(rand() % 3 - 1);
    }
    m_velocityX += directionX * m_acceleration * deltaTime;
    m_velocityY += directionY * m_acceleration * deltaTime;
    float speed = std::sqrt(m_velocityX * m_velocityX + m_velocityY * m_velocityY);
    if (speed > m_maxSpeed) {
        m_velocityX *= m_maxSpeed / speed;//giving entity velocity to move on update
        m_velocityY *= m_maxSpeed / speed;
    }

    // Calculate new position using lerping
    float targetX = m_x + m_velocityX * deltaTime;
    float targetY = m_y + m_velocityY * deltaTime;
    float lerpX = lerp(m_x, targetX, m_lerpFactor);
    float lerpY = lerp(m_y, targetY, m_lerpFactor);
    m_x = lerpX;
    m_y = lerpY;

    // Reverse direction if entity hits a wall
    if (m_x < 0 || m_x > 270 - m_width) {
        m_velocityX *= -1;
        m_x += m_velocityX * deltaTime;
    }
    if (m_y < 0 || m_y > 210 - m_height) {
        m_velocityY *= -1;
        m_y += m_velocityY * deltaTime;
    }
    
    p_GameObject.setX(m_x);
    p_GameObject.setY(m_y);
  

}



float Entity::lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

bool Entity::isDead() const
{
    return m_dead;
}