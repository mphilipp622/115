#include "Player.h"

Player* Player::player;

Player::Player()
{
    //ctor
}

Player::Player(double newX, double newY)
{
    xPos = newX;
	yPos = newY;

	width = 1.0;
    height = 1.0;

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

    player = this;

    InitModel("Images/Player/play.png", true);
}

Player::~Player()
{
    //dtor
}

void Player::Move(double dirX, double dirY)
{
//    if(xPos + dirX > GLScene::grid->GetSizeX() || xPos + dirX < 0)
//        return; // bounds checking on the grid.
//    if(yPos + dirY > GLScene::grid->GetSizeY() || yPos + dirY < 0)
//        return;
//
//    if(GLScene::grid->GetTile(xPos +dirX, yPos + dirY)->IsTraversable())
//    {
//        xPos += dirX;
//        yPos += dirY;
//    }
}

bool Player::CheckCollision(int x, int y)
{

}


void Player::ShootProjectile(double x, double y)
{
    double dirX = 0;
    double dirY = 0;

    if(x > xPos) // shoot right
        dirX = 1.0;
    else if(x < xPos) // shoot left
        dirX = -1.0;
    if(y < yPos) // shoot down
        dirY = -1.0;
    else if(y > yPos) // shoot up
        dirY = 1.0;
//    Projectile *newProjectile = new Projectile(xPos, yPos, 0.5, 0.5, 1, 4.0, "PlayerProjectile", x + xPos, y + yPos); // sends relative mouse pointer location
//    newProjectile->InitModel("Images/Note.png", true);
//    GLScene::movableObjects.push_back(newProjectile);
}
