#include "Player.h"

Player* Player::player;

Player::Player()
{
    //ctor
}

Player::Player(double newX, double newY)
{
    if(player)
        delete player;

    xPos = newX;
	yPos = newY;

	width = 0.6;
    height = 1.0;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    xDir = 1.0;
    yDir = 0;

    // translations
    zoom = 0;

    moveSpeed = 3.0;

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

    playerLocked = false;

    arrowCount = 1; // player starts with 1 arrow

    InitModel("Images/Player/PlayerRight0.png", true);

    InitAnimations();

    isMoving = false;

    frameTimer = new Timer();
    frameTimer->Start();

    arrowSound = new AudioSource("ArrowSound", "Audio/SFX/Arrow.mp3", xPos, yPos, 1.0, false);
    dyingSound = new AudioSource("PlayerDie", "Audio/SFX/PlayerDie.ogg", xPos, yPos, 0.6, false);
    idleFrame = 0;
    runFrame = 0;
}

Player::~Player()
{
    //dtor
}

void Player::Update()
{
    if(isMoving)
    {
        MoveToDestination();
        if(xDir > 0)
            Animate("RunRight");
        else if(xDir < 0)
            Animate("RunLeft");
        else if(yDir > 0)
            Animate("RunUp");
        else if(yDir < 0)
            Animate("RunDown");
    }
    else
    {
        if(xDir > 0)
            Animate("IdleRight");
        else if(xDir < 0)
            Animate("IdleLeft");
        else if(yDir > 0)
            Animate("IdleUp");
        else if(yDir <0)
            Animate("IdleDown");
    }

}

void Player::Move(double dirX, double dirY)
{
    // bounds checking on the grid.
    if(!Grid::grid->BoundSafe(xPos + dirX, yPos + dirY))
        return;

    // Check player collision against walls or enemies.
    if(Grid::grid->GetTile(xPos + dirX, yPos + dirY)->IsTraversable())
    {
        isMoving = true;
        playerLocked = true;
        Grid::grid->GetTile(xPos, yPos)->RevertType(); // set player's previous tile to traversable

        destX = xPos + dirX;
        destY = yPos + dirY;
        xDir = dirX;
        yDir = dirY;
    }

}

void Player::MoveToDestination()
{
    xPos += xDir * DeltaTime::GetDeltaTime() * moveSpeed;
    yPos += yDir * DeltaTime::GetDeltaTime() * moveSpeed;

    if(xPos >= destX - 0.05 && xPos <= destX + 0.05 && yPos >= destY - 0.05 && yPos <= destY + 0.05)
    {
        xPos = destX;
        yPos = destY;

        if(Grid::grid->GetTile(xPos, yPos)->IsArrows())
        {
            arrowCount++;
            UserInterface::UI->AddArrow();
            Grid::grid->GetTile(xPos, yPos)->RemoveArrows();
        }
        if(Grid::grid->GetTile(xPos, yPos)->IsTreasure())
            WinLose::winLose->Win();
        if(Grid::grid->GetTile(xPos, yPos)->IsEnemy())
            Die();

        Grid::grid->GetTile(xPos, yPos)->SetType(Type::player);

        isMoving = false;

        TurnManager::turnManager->NextTurn(); // end player turn and start enemy turn
        playerLocked = false;
    }

}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

		// flip texture to the right

		glTexCoord2f(0.0, 1.0);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glEnd();
}

void Player::Animate(string animation)
{
    if(animation == "RunRight")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            runFrame++;
            runFrame %= 4;
            frameTimer->Reset();
        }

        runRight[runFrame].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "RunLeft")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            runFrame++;
            runFrame %= 4;
            frameTimer->Reset();
        }

        runLeft[runFrame].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "RunUp")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            runFrame++;
            runFrame %= 4;
            frameTimer->Reset();
        }

        runUp[runFrame].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "RunDown")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            runFrame++;
            runFrame %= 4;
            frameTimer->Reset();
        }

        runDown[runFrame].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "IdleLeft")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleLeft[0].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "IdleRight")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleRight[0].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "IdleDown")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleDown[0].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "IdleUp")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleUp[0].Binder();
        DrawPlayer();

        glPopMatrix();
    }
}

void Player::ShootProjectile(double x, double y)
{
    if(arrowCount <= 0)
        return; // Make sure we have arrows before firing.

    playerLocked = true; // player will be locked from input while arrow is moving.

    Projectile *newProjectile = new Projectile(xPos, yPos, 0.5, 0.5, 1, 6.0, "Arrow", x + xPos, y + yPos);

    if(x == 1.0)
        newProjectile->InitModel("Images/ArrowRight.png", true);
    else if(x == -1.0)
        newProjectile->InitModel("Images/ArrowLeft.png", true);

    if(y == 1.0)
        newProjectile->InitModel("Images/ArrowUp.png", true);
    else if(y == -1.0)
        newProjectile->InitModel("Images/ArrowDown.png", true);

    arrowCount--;
    arrowSound->Play();
    UserInterface::UI->RemoveArrow();
    GLScene::movableObjects.push_back(newProjectile);
}

void Player::SetInput(WPARAM newParam)
{
    if(playerLocked)
        return; // prevent player input

    wParam = newParam;

    const int aKey = 0x41, dKey = 0x44, sKey = 0x53, wKey = 0x57;
    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(wParam == aKey) // includes boundary checking
        Move(-1.0, 0);
    if(wParam == dKey)
        Move(1.0, 0); // move player
    if(wParam == sKey)
        Move(0, -1.0); // move player
    if(wParam == wKey)
        Move(0, 1.0); // move player
    if(wParam == VK_LEFT)
        ShootProjectile(-1.0, 0); // shoot left
    if(wParam == VK_RIGHT)
        ShootProjectile(1.0, 0); // shoot right
    if(wParam == VK_DOWN)
        ShootProjectile(0, -1.0); // shoot down
    if(wParam == VK_UP)
        ShootProjectile(0, 1.0); // shoot up
}

void Player::SetLocked()
{
    playerLocked = !playerLocked;
}

int Player::GetArrowCount()
{
    return arrowCount;
}

void Player::Die()
{
    dyingSound->Play();
    WinLose::winLose->Lose();
}


void Player::InitAnimations()
{
    for(int i = 0; i < 6; i++)
        runLeft[i].BindTexture("Images/Player/PlayerLeft" + to_string(i) + ".png");

    for(int i = 0; i < 6; i++)
        runRight[i].BindTexture("Images/Player/PlayerRight" + to_string(i) + ".png");

    for(int i = 0; i < 6; i++)
        runUp[i].BindTexture("Images/Player/PlayerUp" + to_string(i) + ".png");

    for(int i = 0; i < 6; i++)
        runDown[i].BindTexture("Images/Player/PlayerDown" + to_string(i) + ".png");

    idleRight[0].BindTexture("Images/Player/PlayerRight0.png");
    idleLeft[0].BindTexture("Images/Player/PlayerLeft0.png");
    idleUp[0].BindTexture("Images/Player/PlayerUp0.png");
    idleDown[0].BindTexture("Images/Player/PlayerDown0.png");
}
