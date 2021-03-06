#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>
#include <iostream>
#include <algorithm> // max and min
#include <string>

using namespace std;

Model::Model()
{

}

Model::Model(float newWidth, float newHeight, double newX, double newY, string newName, string newTag)
{
    // Initialize dimensions
    width = newWidth;
    height = newHeight;

    name = newName;
    tag = newTag;

    // Initialize rotations
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = 0;
    xPos = newX;
    yPos = newY;

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

    // Initialize texture loader
    texture = new TextureLoader();
}

Model::~Model()
{

}
void Model::DrawModel()
{
    //render this model

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    texture->Binder(); // update texture

    glTranslated(xPos, yPos, zoom); // tell openGL where this model should render
    glRotated(rotateX, 1, 0, 0);
    glRotated(rotateY, 0, 1, 0);
    glRotated(rotateZ, 0, 0, 1);

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
    glPopMatrix();
}

void Model::DrawSquare(float newWidth, float newHeight)
{
    // Draw a background

    glColor3f(1.0,1.0,1.0);
    texture->Binder();
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1.0);
        glVertex3f(-newWidth/newHeight,-1,-8.0f);

        glTexCoord2f(1.0, 1.0);
        glVertex3f(newWidth/newHeight,-1,-8.0f);

        glTexCoord2f(1.0, 0);
        glVertex3f(newWidth/newHeight,1,-8.0f);

        glTexCoord2f(0, 0);
        glVertex3f(-newWidth/newHeight,1,-8.0f);
     glEnd();
}

void Model::InitModel(string fileName, bool transparent)
{

    if(transparent)
    {
        // initialize this model with transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead. Change it to mess with cool effects
    }

    texture->BindTexture(fileName); // assign texture to model
}

double Model::GetX()
{
    return xPos;
}

double Model::GetY()
{
    return yPos;
}

float Model::GetWidth()
{
    return width;
}

float Model::GetHeight()
{
    return height;
}

string Model::GetName()
{
    return name;
}

string Model::GetTag()
{
    return tag;
}

void Model::Update()
{
    DrawModel(); // The default Update behavior simply draws the model into the openGL renderer
}

bool Model::CheckCollision()
{
    // The base model class will never check collision. This will happen in Enemy and Player.
    // This function is implemented because it is virtual but not abstract.
    return false;
}

bool Model::Collision(Model* collider)
{
    // Half the width and height are used for collision checking
    double widthOffset = width / 2, heightOffset = height / 2;

    // Send the x and y upper and lower boundaries to the helper function to see if they overlap.
    // Will return true if they overlap, false if not.
    return Overlapping(xPos - widthOffset, xPos + widthOffset, collider->GetX() - collider->GetWidth() / 2,
                       collider->GetX() + collider->GetWidth() / 2) &&
           Overlapping(yPos - heightOffset, yPos + heightOffset, collider->GetY() - collider->GetHeight() / 2,
                       collider->GetY() + collider->GetHeight() / 2);
}


bool Model::Overlapping(double min0, double max0, double min1, double max1)
{
    // Square-square overlap helper function. Called by Collision(Model*).
    return max0 >= min1 && min0 <= max1;
}

void Model::Move()
{
    // virtual move function used for polymorphism in Player and Enemy classes. Implemented because it is not abstract
    return;
}

void Model::Destroy()
{
    delete this; // remove this instance from memory.
}

void Model::SetZoom(double newZoom)
{
    zoom = newZoom;
}

bool Model::IsActive()
{
    return active;
}

void Model::SetActive()
{
    /*
    This function will also initiate the Move() functionality of the enemy. This is because, in GLScene,
    when a new enemy is set to active, we want that enemy to begin pathfinding immediately. As a result,
    this function both sets active to true AND starts the Move process for the newly active enemy.
    */
    active = true;
    Move();
}
