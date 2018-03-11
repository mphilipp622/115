#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>
#include <iostream>
#include <Player.h>
#include <string>

using namespace std;

TextureLoader* texture = new TextureLoader();

Model::Model()
{
    //ctor
}

Model::~Model()
{
    //dtor
}

Model::Model(int newX, int newY, int newWidth, int newHeight, string newTag)
{
    width = newWidth;
    height = newHeight;

    tag = newTag;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = -3.0;
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
}

void Model::DrawModel()
{
    //render this model
    glColor3f(1.0, 1.0, 1.0);
    texture->Binder(); // update texture
//    if(this->name != "player")
    glTranslated(this->xPos, this->yPos, this->zoom);
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
}

void Model::InitModel(string fileName, bool transparent)
{
    if(transparent)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead. Change it to mess with cool effects
    }
    texture->Binder();
    cout << "Loading Model: " << fileName << endl;
    texture->BindTexture(fileName);
}

int Model::GetX()
{
    return xPos;
}

int Model::GetY()
{
    return yPos;
}

int Model::GetWidth()
{
    return width;
}

int Model::GetHeight()
{
    return height;
}

void Model::SetPosition(int newX, int newY)
{
    xPos = newX;
    yPos = newY;
}

void Model::SetWidth(int newWidth)
{
    width = newWidth;
}

void Model::SetHeight(int newHeight)
{
    height = newHeight;
}

string Model::GetTag()
{
    return tag;
}

int Model::Collision()
{
    // return Maze->GetTile(xPos, yPos)
}
