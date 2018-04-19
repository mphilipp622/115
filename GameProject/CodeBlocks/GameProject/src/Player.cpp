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
    xPos += dirX;
    yPos += dirY;
}
