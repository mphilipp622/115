#include <Player.h>
#include <Timer.h>
#include <TextureLoader.h>
#include <string>
#include <GLScene.h>
#include <cmath>

Timer *T;
//TextureLoader run[4];
//TextureLoader idle[1];
//TextureLoader jumpAnim[1];

Player* Player::player; // Global getter for the player object

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

Player::Player(int newX, int newY)
{
    // Collision
    width = 1;
    height = 1;

    xPos = newX;
    yPos = newY;
    playerZoom = -3.0;

    // set previous positions to our starting position
    prevXPos = xPos;
    prevYPos = yPos;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = playerZoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = playerZoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = playerZoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = playerZoom;

    actionTrigger = 0;

    tag = "player";
    player = this;
	T = new Timer();
    T->Start();
}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 1.0);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
//	if (xDirection == -1.0)
//	{
//		// flip texture to the left
//
//		glTexCoord2f(0.0, 1.0);
//		glVertex3f(-vertices[0].x, vertices[0].y, vertices[0].z);
//
//		glTexCoord2f(1.0, 1.0);
//		glVertex3f(-vertices[1].x, vertices[1].y, vertices[1].z);
//
//		glTexCoord2f(1.0, 0.0);
//		glVertex3f(-vertices[2].x, vertices[2].y, vertices[2].z);
//
//		glTexCoord2f(0.0, 0.0);
//		glVertex3f(-vertices[3].x, vertices[3].y, vertices[3].z);
//	}
//	else
//	{
//		// flip texture to the right
//
//		glTexCoord2f(0.0, 1.0);
//		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
//
//		glTexCoord2f(1.0, 1.0);
//		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
//
//		glTexCoord2f(1.0, 0.0);
//		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
//
//		glTexCoord2f(0.0, 0.0);
//		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
//	}

    glEnd();
}

void Player::InitPlayer()
{
 // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");
//    run[0].BindTexture("Images/Player/player0.png");
//    run[1].BindTexture("Images/Player/player1.png");
//    run[2].BindTexture("Images/Player/player2.png");
//    run[3].BindTexture("Images/Player/player3.png");
//
//    idle[0].BindTexture("Images/Player/play.png");
//
//    jumpAnim[0].BindTexture("Images/Player/jump.png");
}

void Player::Actions(int newAction)
{
//switch(newAction)
//    {
//    case 0:
//		// Idle
//
//        glPushMatrix();
//
//        glTranslated(xPos, yPos, playerZoom);
////        glTranslated(-0.5, -0.5, -1.0);
////        idle[0].Binder();
//        DrawPlayer();
//
//        glPopMatrix();
//        break;
//
//    case 1:
//		// Running
//
//        glPushMatrix();
//
//        glTranslated(xPos, yPos, playerZoom);
////        glTranslated(-0.5, -0.5, -1.0);
//        if(T->GetTicks() > 60)
//        {
//            moveSpeed++;
//            moveSpeed %= 4;
//            T->Reset();
//        }
//
//        run[moveSpeed].Binder();
//        DrawPlayer();
//
//        glPopMatrix();
//        break;
//    case 2:
//		// Jumping
//
//        glPushMatrix();
//
//        glTranslated(xPos, yPos, playerZoom);
////        glTranslated(-0.5, -0.5, -1.0);
//        jumpAnim[0].Binder();
//        DrawPlayer();
//
//        glPopMatrix();
//        break;
//    }
}

void Player::Update()
{
//    if(moving)
//    {
//        if(xDirection > 0)
//            MoveRight();
//        else if(xDirection < 0)
//            MoveLeft();
//
//        if(!jump)
//            Actions(1);
//        else
//            Actions(2);
//    }
//    else if(!moving && !jump)
//        Actions(0);
//
//    if(jump)
//    {
//        Jump();
//        if(!moving)
//            Actions(2);
//    }
//    else
//        ApplyGravity();
//
//    if(slowDown)
//        StopMove();
}

void Player::MoveX(int direction)
{

}

void Player::MoveY(int direction)
{

}

double Player::GetZoom()
{
    return playerZoom;
}
