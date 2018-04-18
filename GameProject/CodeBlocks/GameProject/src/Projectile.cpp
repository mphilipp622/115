#include "Projectile.h"
#include <cmath>

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}
Projectile::Projectile(double newX, double newY, double newWidth, double newHeight, int newDamage, float newSpeed, string newName, double newTargetX, double newTargetY)
{
    xPos = newX;
    yPos = newY;

    prevX = newX;
    prevY = newY;

    targetX = newTargetX;
    targetY = newTargetY;

    damage = newDamage;
    speed = newSpeed;

    name = newName;

    vectorDist = sqrt(pow((targetX - xPos), 2) + pow((targetY - yPos), 2));
    normalizedX = (targetX - xPos) / vectorDist;
    normalizedY = (targetY - yPos) / vectorDist;

    width = newWidth;
    height = newHeight;

    endOfLifeTime = 5000; // 5 seconds

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = 0;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = zoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = zoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = zoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = zoom;

    texture = new TextureLoader();
    lifetime = new Timer();
    lifetime->Start();
}

void Projectile::Update()
{
    Move();

    DrawModel();

    if(lifetime->GetTicks() > endOfLifeTime)
        Destroy();
}

void Projectile::Move()
{
    prevX = xPos;
    prevY = yPos;

    xPos += normalizedX * speed * DeltaTime::GetDeltaTime();
    yPos += normalizedY * speed * DeltaTime::GetDeltaTime();

    if(CheckCollision())
        // if we collide with something, destroy object. If object is enemy, we need to deal damage
        Destroy();
    if(name == "PlayerProjectile" && CheckCollisionEnemy())
        Destroy(); // implement damage code here later
}

bool Projectile::CheckCollision()
{
    for(auto& model : GLScene::staticObjects)
    {
        if(Collision(model))
            return true;
    }


    return false;
}
bool Projectile::CheckCollisionEnemy()
{
    // check for collision with an enemy
//    for(auto& enemy : GLScene::enemies)
//    {
//        if(Collision(enemy))
//        {
//            enemy->TakeDamage(damage);
//            return true; // will ignore player collision.
//        }
//
//    }

    return false;
}

bool Projectile::CheckCircleCollision()
{
    return false;
}

bool Projectile::CheckCircleSquareCollision()
{
    return false;
}


void Projectile::Destroy()
{
    // find this projectile in the main vector and remove it. Then delete this projectile
    auto finder = find(GLScene::movableObjects.begin(), GLScene::movableObjects.end(), this);
    GLScene::movableObjects.erase(finder);
    delete this;
}