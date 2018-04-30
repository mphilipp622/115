#include "Player.h"

Player* Player::player;

Player::Player()
{
    //ctor
}

Player::Player(double newX, double newY)
{
    if(player)
        delete player; // if the global static player already exists, delete it.

    // initialize positions
    xPos = newX;
	yPos = newY;

	// initialize dimensions
	width = 0.6;
    height = 1.0;

    // initialize rotations
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // initialize directions
    xDir = 1.0;
    yDir = 0;

    // translations
    zoom = 0;

    // initialize move speed
    moveSpeed = 6.0;

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

    player = this; // assign the static global instance of Player to this instance

    playerLocked = false;

    arrowCount = 1; // player starts with 1 arrow

    // Give player a texture
    InitModel("Images/Player/PlayerRight0.png", true);

    // initialize animations
    InitAnimations();

    isMoving = false;

    frameTimer = new Timer();
    frameTimer->Start();

    // initialize SFX
    arrowSound = new AudioSource("Audio/SFX/Arrow.mp3", 1.0, false);
    dyingSound = new AudioSource("Audio/SFX/PlayerDie.ogg", 0.6, false);

    idleFrame = 0;
    runFrame = 0;
}

Player::~Player()
{
    //dtor
}

void Player::Update()
{
    // Update is called every frame by GLScene::DrawGLScene()
    if(isMoving)
    {
        // if the player is set to move, we move to destination until we've reached it
        MoveToDestination();

        // animate based on the direction of the player
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
        // If we are not moving, then animate idle based on the previous direction of the player
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
    // bounds check the desired destination on the grid. Return if it's not safe
    if(!Grid::grid->BoundSafe(xPos + dirX, yPos + dirY))
        return;

    // Check player collision against walls or enemies.
    if(Grid::grid->GetTile(xPos + dirX, yPos + dirY)->IsTraversable())
    {
        // Set flags
        isMoving = true;
        playerLocked = true; // player cannot input actions while moving

        Grid::grid->GetTile(xPos, yPos)->RevertType(); // set player's previous tile to traversable

        // Set our destination and direction
        destX = xPos + dirX;
        destY = yPos + dirY;
        xDir = dirX;
        yDir = dirY;
    }

}

void Player::MoveToDestination()
{
    // Increment x and y positions by our direction, normalized by delta time and multiplied by our move speed
    // This should give us semi-smooth movement
    xPos += xDir * DeltaTime::GetDeltaTime() * moveSpeed;
    yPos += yDir * DeltaTime::GetDeltaTime() * moveSpeed;

    if(xPos >= destX - 0.1 && xPos <= destX + 0.1 && yPos >= destY - 0.1 && yPos <= destY + 0.1)
    {
        // If the player is within a certain distance of the center of their destination tile,
        // set their position to the destination and stop moving.
        xPos = destX;
        yPos = destY;

        if(Grid::grid->GetTile(xPos, yPos)->IsArrows())
        {
            // Check if we've landed on arrows. If we have, increment arrow count and update our UI and Tile
            arrowCount++;
            UserInterface::UI->AddArrow();
            Grid::grid->GetTile(xPos, yPos)->RemoveArrows(); // Remove arrows from the tile, which updates the texture
        }
        if(Grid::grid->GetTile(xPos, yPos)->IsTreasure())
            // If we've landed on treasure, we win.
            WinLose::winLose->Win();
        if(Grid::grid->GetTile(xPos, yPos)->IsEnemy())
            // if we've landed on an enemy, we lose
            Die();

        Grid::grid->GetTile(xPos, yPos)->SetType(Type::player); // set the destination tile to be a player type

        isMoving = false; // stop moving

        TurnManager::turnManager->NextTurn(); // end player turn and start enemy turn
        playerLocked = false; // unlock player controls. TurnManager will keep player locked in GLScene
    }

}

void Player::DrawPlayer()
{
    // Renders player

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
    // Animates player

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

    // Create new projectile
    Projectile *newProjectile = new Projectile(xPos, yPos, 0.5, 0.5, 10.0, "Arrow", x, y);

    // Specify the texture to use based on the direction we fired
    if(x == 1.0)
        newProjectile->InitModel("Images/ArrowRight.png", true);
    else if(x == -1.0)
        newProjectile->InitModel("Images/ArrowLeft.png", true);

    if(y == 1.0)
        newProjectile->InitModel("Images/ArrowUp.png", true);
    else if(y == -1.0)
        newProjectile->InitModel("Images/ArrowDown.png", true);

    arrowCount--; // decrement our number of arrows
    arrowSound->Play(); // play the arrow sound effect
    UserInterface::UI->RemoveArrow(); // remove an arrow from the UI indicator
    GLScene::arrow = newProjectile; // set the arrow in GLScene to the new instance of projectile
}

void Player::SetInput(WPARAM newParam)
{
    // parses input and executes functionality.

    if(playerLocked)
        return; // prevent player input if they're locked

    const int aKey = 0x41, dKey = 0x44, sKey = 0x53, wKey = 0x57; // hex values for Microsoft's virtual keys

    // Note that bounds checking will be done in the Move function, not here.
    if(newParam == aKey)
        Move(-1.0, 0);
    if(newParam == dKey)
        Move(1.0, 0); // move player
    if(newParam == sKey)
        Move(0, -1.0); // move player
    if(newParam == wKey)
        Move(0, 1.0); // move player
    if(newParam == VK_LEFT)
        ShootProjectile(-1.0, 0); // shoot left
    if(newParam == VK_RIGHT)
        ShootProjectile(1.0, 0); // shoot right
    if(newParam == VK_DOWN)
        ShootProjectile(0, -1.0); // shoot down
    if(newParam == VK_UP)
        ShootProjectile(0, 1.0); // shoot up
}

void Player::SetLocked()
{
    // Projectile::Destroy() calls this to unlock player
    playerLocked = !playerLocked;
}

int Player::GetArrowCount()
{
    return arrowCount;
}

void Player::Die()
{
    dyingSound->Play(); // play our Wilhelm Scream
    WinLose::winLose->Lose(); // Set Lose Condition to true
}


void Player::InitAnimations()
{
    // Initialize the animations for the player.

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
