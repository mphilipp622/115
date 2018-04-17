#include "Player.h"

Player* Player::player;

Player::Player()
{
    //ctor
}

Player::Player(double newX, double newY)
{

}

Player::~Player()
{
    //dtor
}

void Player::InitPlayer()
{
     // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");
    run[0].BindTexture("Images/Player/player0.png");
    run[1].BindTexture("Images/Player/player1.png");
    run[2].BindTexture("Images/Player/player2.png");
    run[3].BindTexture("Images/Player/player3.png");

    idle[0].BindTexture("Images/Player/play.png");

}

void Player::Move(double dirX, double dirY)
{

}
