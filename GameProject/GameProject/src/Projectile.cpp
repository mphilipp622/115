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
Projectile::Projectile(double newX, double newY, double newWidth, double newHeight, float newSpeed, string newName, double newDirX, double newDirY)
{
    // initialize starting position
    xPos = newX;
    yPos = newY;

    // initialize target position
    xDir = newDirX;
    yDir = newDirY;

    speed = newSpeed;

    name = newName;

    width = newWidth;
    height = newHeight;

    endOfLifeTime = 5000; // 5 seconds. Arrows will destroy if they've been alive for 5 seconds or more

    // initialize rotations
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
    lifetime->Start(); // start 5 second lifetime
}

void Projectile::Update()
{
    // Update() is called in GLScene::DrawGLScene
    Move(); // move arrow

    DrawModel(); // render arrow

    if(lifetime->GetTicks() > endOfLifeTime)
        Destroy(); // if arrow has been alive for 5 or more seconds, destroy it from memory
}

void Projectile::Move()
{

    // Move in a constant direction, smoothed by delta time and multiplied by speed
    xPos += xDir * speed * DeltaTime::GetDeltaTime();
    yPos += yDir * speed * DeltaTime::GetDeltaTime();

    if(CheckCollision())
        // if we collide with something, destroy object. If object is enemy, we need to deal damage
        Destroy();

    if(!Grid::grid->BoundSafe(xPos, yPos))
        Destroy(); // check if arrow has gone out of bounds

    CheckCollisionEnemy(); // if we hit an enemy, kill the enemy and destroy the arrow
}

bool Projectile::CheckCollision()
{
    // Iterate over every tile in the grid to see if we hit a wall or go out of bounds
    for(auto& tile : Grid::grid->GetTiles())
    {
        for(auto& tile2 : tile)
        {
            if(tile2->IsWall() && Collision(tile2))
                // We need the && condition for knowing if the models have overlapped in the world
                return true; // if the arrow hits a wall, return true
        }
    }

    return false;
}

void Projectile::CheckCollisionEnemy()
{
    // iterate over all the enemies in GLScene to see if we've hit one
    for(auto& enemy : GLScene::enemies)
    {
        if(Collision(enemy))
        {
            enemy->Destroy();  // kill the enemy
            Destroy(); // destroy the arrow
        }
    }
}


void Projectile::Destroy()
{
    GLScene::arrow = nullptr; // set GLScene arrow back to null
    Player::player->SetLocked(); // unlock player
    TurnManager::turnManager->NextTurn(); // start enemy turn
    delete this; // free memory
}
