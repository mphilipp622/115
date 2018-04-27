#include "Enemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(double newX, double newY, string newName)
{
    xPos = newX;
	yPos = newY;

	xDir = 0;
	yDir = -1;
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
    moveSpeed = 6.0;

    InitAnimations();

    InitModel("Images/Enemy/EnemyLeft.png", true);

    isMoving = false;

    active = false;

    dyingSound = new AudioSource("MonsterDie", "Audio/SFX/MonsterDie.mp3", xPos, yPos, 0.6, false);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::Update()
{
    if(active)
    {
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
    if(isMoving) return;


    Tile* tempTile = pathfind->GetNextTile(xPos, yPos);
//    cout << tempTile->GetX() << ", " << tempTile->GetY() << endl;
    if(Grid::grid->GetTile(tempTile->GetX(), tempTile->GetY())->IsEnemy())
    {
        // handle the case where the next tile is an enemy. In this case, enemy should stay stationary.
        isMoving = false;
        active = false;
        destX = xPos;
        destY = yPos;

        GLScene::activeEnemy++;
        if(GLScene::activeEnemy >= GLScene::enemies.size())
            TurnManager::turnManager->NextTurn();
        GLScene::activeEnemy %= GLScene::enemies.size();
    }
    else
    {
        isMoving = true;
        destX = tempTile->GetX();
        destY = tempTile->GetY();
        xDir = destX - xPos;
        yDir = destY - yPos;
        // once we've found our next tile, move enemy into it and set types accordingly.
        Grid::grid->GetTile(xPos, yPos)->RevertType();
    }

}

void Enemy::MoveToDestination()
{
    xPos += xDir * DeltaTime::GetDeltaTime() * moveSpeed;
    yPos += yDir * DeltaTime::GetDeltaTime() * moveSpeed;

    if(xPos >= destX - 0.05 && xPos <= destX + 0.05 && yPos >= destY - 0.05 && yPos <= destY + 0.05)
    {
        xPos = destX;
        yPos = destY;

        if(Grid::grid->GetTile(xPos, yPos)->IsPlayer())
            Player::player->Die();

        Grid::grid->GetTile(xPos, yPos)->SetType(Type::enemy); // tile now has enemy

        isMoving = false;
        active = false;

        GLScene::activeEnemy++;
        if(GLScene::activeEnemy >= GLScene::enemies.size())
            TurnManager::turnManager->NextTurn();
        GLScene::activeEnemy %= GLScene::enemies.size();
    }

}

void Enemy::Destroy()
{
    dyingSound->Play();
    auto finder = find(GLScene::enemies.begin(), GLScene::enemies.end(), this); // find the enemy in the scene
    GLScene::enemies.erase(finder); // remove the enemy from the vector
    Grid::grid->GetTile(xPos, yPos)->RevertType();
    delete this; // free memory
}


void Enemy::InitAnimations()
{
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
    if(animation == "MoveRight")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
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
