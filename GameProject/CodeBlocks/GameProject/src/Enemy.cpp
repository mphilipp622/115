#include "Enemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(double newX, double newY)
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
    pathfind = new Pathfinder();

    frameTimer = new Timer();
    frameTimer->Start();

    moveFrame = 0;
    moveSpeed = 2.0;

    InitAnimations();

    InitModel("Images/Enemy/EnemyLeft.png", true);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::Update()
{
    if(isMoving && xDir == 1)
    {
        MoveToDestination();
        Animate("MoveRight");
    }
    else if(isMoving && xDir == -1)
    {
        MoveToDestination()
        Animate("MoveLeft");
    }
    else if(isMoving && yDir == 1)
    {
        MoveToDestination();
        Animate("MoveUp");
    }
    else if(isMoving && yDir == -1)
    {
        MoveToDestination();
        Animate("MoveDown");
    }
    else
        Animate("Idle");
}

void Enemy::Move()
{
    if(isMoving) return;

    isMoving = true;
    Tile* tempTile = pathfind->GetNextTile(xPos, yPos);

    destX = tempTile->GetX();
    destY = tempTile->GetY();
    xDir = destX - xPos;
    yDir = destY - yPos;

    // once we've found our next tile, move enemy into it and set types accordingly.
    Grid::grid->GetTile(xPos, yPos)->RevertType();
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
    }

}

void Enemy::Destroy()
{
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

    idle[0].BindTexture("Images/Enemy/EnemyRight.png");
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
        DrawModel();

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
        DrawModel();

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
        DrawModel();

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
        DrawModel();

        glPopMatrix();
    }
    else if(animation == "Idle")
    {
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        idle[0].Binder();
        DrawModel();

        glPopMatrix();
    }
}

void Enemy::MoveToDestination()
{

}
