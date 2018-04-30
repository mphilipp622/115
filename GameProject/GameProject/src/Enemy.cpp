#include "Enemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(double newX, double newY, string newName)
{
    // initialize variables.
    xPos = newX;
	yPos = newY;

	xDir = 0;
	yDir = -1;  // starts all the enemies looking downwards.
	destX = 0;
	destY = 0;

	width = 1.0;
    height = 1.0;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = 0;

    name = newName;

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
    pathfind = new Pathfinder();

    frameTimer = new Timer();
    frameTimer->Start();

    moveFrame = 0;
    moveSpeed = 10.0;

    InitAnimations();

    InitModel("Images/Enemy/EnemyLeft.png", true);

    isMoving = false;

    active = false;

    dyingSound = new AudioSource("Audio/SFX/MonsterDie.mp3", 0.6, false);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::Update()
{
    if(active)
    {
        // Move and animate the enemy

        if(isMoving && xDir > 0)
        {
            MoveToDestination();
            Animate("MoveRight");
        }
        else if(isMoving && xDir < 0)
        {
            MoveToDestination();
            Animate("MoveLeft");
        }
        else if(isMoving && yDir > 0)
        {
            MoveToDestination();
            Animate("MoveUp");
        }
        else if(isMoving && yDir <0)
        {
            MoveToDestination();
            Animate("MoveDown");
        }
    }
    else
    {
        // Draw the enemy being idle.

        if(xDir > 0)
            Animate("IdleRight");
        else if(xDir < 0)
            Animate("IdleLeft");
        else if(yDir > 0)
            Animate("IdleUp");
        else if(yDir < 0)
            Animate("IdleDown");
    }

}

void Enemy::Move()
{
    if(isMoving) return; // safety check to make sure enemy is not already moving.

    Tile* tempTile = pathfind->GetNextTile(xPos, yPos);

    if(Grid::grid->GetTile(tempTile->GetX(), tempTile->GetY())->IsEnemy())
    {
        // handle the case where the next tile is an enemy. In this case, enemy should stay stationary.
        isMoving = false;
        active = false;
        destX = xPos;
        destY = yPos;

        // Move to next enemy's turn in GLScene
        GLScene::activeEnemy++;
        if(GLScene::activeEnemy >= GLScene::enemies.size())
            TurnManager::turnManager->NextTurn();
        GLScene::activeEnemy %= GLScene::enemies.size();
    }
    else
    {
        // If next tile in path is traversable, move
        isMoving = true;
        destX = tempTile->GetX(); // set enemy's destination to the new tile
        destY = tempTile->GetY();
        xDir = destX - xPos; // specify enemy's direction for animations
        yDir = destY - yPos;

        // once we've found our next tile, move enemy into it and set types accordingly.
        Grid::grid->GetTile(xPos, yPos)->RevertType();
    }

}

void Enemy::MoveToDestination()
{
    // Move the enemy to the destination tile
    xPos += xDir * DeltaTime::GetDeltaTime() * moveSpeed;
    yPos += yDir * DeltaTime::GetDeltaTime() * moveSpeed;

    if(xPos >= destX - 0.1 && xPos <= destX + 0.1 && yPos >= destY - 0.1 && yPos <= destY + 0.1)
    {
        // If the enemy is within a certain distance of the center of the destination tile, snap them to it and end movement.
        xPos = destX;
        yPos = destY;

        // If enemy lands on player, kill the player
        if(Grid::grid->GetTile(xPos, yPos)->IsPlayer())
            Player::player->Die();

        Grid::grid->GetTile(xPos, yPos)->SetType(Type::enemy); // tile now has enemy

        isMoving = false;
        active = false;

        // Tell GLScene it is next enemy's turn
        GLScene::activeEnemy++;
        if(GLScene::activeEnemy >= GLScene::enemies.size())
            TurnManager::turnManager->NextTurn();
        GLScene::activeEnemy %= GLScene::enemies.size();
    }

}

void Enemy::Destroy()
{
    dyingSound->Play(); // Plays a dying sound
    auto finder = find(GLScene::enemies.begin(), GLScene::enemies.end(), this); // find the enemy in the scene
    GLScene::enemies.erase(finder); // remove the enemy from the vector
    Grid::grid->GetTile(xPos, yPos)->RevertType(); // Revert the enemy's tile back to it's normal type
    delete this; // free memory
}


void Enemy::InitAnimations()
{
    // Initialize all the animations for the enemy. Animations are stored in TextureBinder arrays
    // Filenames use a numbering convention so we can iterate through them easily with a for loop
    for(int i = 0; i < 4; i++)
        moveUp[i].BindTexture("Images/Enemy/EnemyUp" + to_string(i) + ".png");

    for(int i = 0; i < 4; i++)
        moveDown[i].BindTexture("Images/Enemy/EnemyDown" + to_string(i) + ".png");

    for(int i = 0; i < 4; i++)
        moveRight[i].BindTexture("Images/Enemy/EnemyRight" + to_string(i) + ".png");

    for(int i = 0; i < 4; i++)
        moveLeft[i].BindTexture("Images/Enemy/EnemyLeft" + to_string(i) + ".png");

    idleRight[0].BindTexture("Images/Enemy/EnemyRight.png");
    idleLeft[0].BindTexture("Images/Enemy/EnemyLeft.png");
    idleUp[0].BindTexture("Images/Enemy/EnemyUp.png");
    idleDown[0].BindTexture("Images/Enemy/EnemyDown.png");
}

void Enemy::Animate(string animation)
{
    // Animate the enemy depending on the direction they're moving.
    if(animation == "MoveRight")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom); // render enemy's new position

        if(frameTimer->GetTicks() > 60)
        {
            // every 60 ms, update the frame
            moveFrame++;
            moveFrame %= 4;
            frameTimer->Reset();
        }

        moveRight[moveFrame].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "MoveLeft")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            moveFrame++;
            moveFrame %= 4;
            frameTimer->Reset();
        }

        moveLeft[moveFrame].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "MoveUp")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            moveFrame++;
            moveFrame %= 4;
            frameTimer->Reset();
        }

        moveUp[moveFrame].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "MoveDown")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            moveFrame++;
            moveFrame %= 4;
            frameTimer->Reset();
        }

        moveDown[moveFrame].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "IdleRight")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleRight[0].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "IdleLeft")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleLeft[0].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "IdleUp")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleUp[0].Binder();
        DrawEnemy();

        glPopMatrix();
    }
    else if(animation == "IdleDown")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idleDown[0].Binder();
        DrawEnemy();

        glPopMatrix();
    }
}

void Enemy::DrawEnemy()
{
    // Create vertices and texture coordinates for the enemy. Used for OpenGL rendering
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

    glEnd();
}
