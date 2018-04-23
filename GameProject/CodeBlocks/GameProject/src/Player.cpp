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

	width = 1.0;
    height = 1.0;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    xDir = 1.0;
    yDir = 0;

    // translations
    zoom = 0;

    moveSpeed = 2.0;

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

    InitModel("Images/Player/play.png", true);

    for(int i = 0; i < 4; i++)
        run[i].BindTexture("Images/Player/player" + to_string(i) + ".png");

    idle[0].BindTexture("Images/Player/play.png");

    isMoving = false;

    frameTimer = new Timer();
    frameTimer->Start();

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
        Animate("Run");
    }
    else
        Animate("Idle");
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
    }

}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

	if (xDir == -1.0)
	{
		// flip texture to the left

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(-vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(-vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-vertices[3].x, vertices[3].y, vertices[3].z);
	}
	else
	{
		// flip texture to the right

		glTexCoord2f(0.0, 1.0);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	}

    glEnd();

}

void Player::Animate(string animation)
{
    if(animation == "Run")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            runFrame++;
            runFrame %= 4;
            frameTimer->Reset();
        }

        run[runFrame].Binder();
        DrawPlayer();

        glPopMatrix();
    }
    else if(animation == "Idle")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            idleFrame++;
            idleFrame %= 1;
            frameTimer->Reset();
        }

        idle[idleFrame].Binder();
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
    WinLose::winLose->Lose();
}
