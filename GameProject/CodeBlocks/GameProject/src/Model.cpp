#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>
#include <iostream>
#include <algorithm> // max and min
#include <string>

using namespace std;

Model::Model()
{
//    // rotations
//    rotateX = 0;
//    rotateY = 0;
//    rotateZ = 0;
//
//    // translations
//    zoom = -3.0;
//    xPos = -0.5;
//    yPos = -0.5;
//
//    // Create Square
//    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = 1.0;
//    vertices[1].x = 1.0; vertices[1].y = 0.0; vertices[1].z = 1.0;
//    vertices[2].x = 1.0; vertices[2].y = 1.0; vertices[2].z = 1.0;
//    vertices[3].x = 0.0; vertices[3].y = 1.0; vertices[3].z = 1.0;

}

Model::Model(float newWidth, float newHeight, double newX, double newY, string newName, string newTag)
{
    width = newWidth;
    height = newHeight;
    radius = width / 2;

    name = newName;
    tag = newTag;

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

    texture = new TextureLoader();
}
Model::Model(float newWidth, float newHeight, double newX, double newY, string newName, string newTag, AudioSource* newSource)
{
    width = newWidth;
    height = newHeight;
    radius = width / 2;

    name = newName;
    tag = newTag;

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
//    if(name != "player")
    glTranslated(xPos, yPos, zoom);
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

void Model::InitModel(string fileName, bool transparent)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead. Change it to mess with cool effects

//    texture->Binder();
    this->texture->BindTexture(fileName);

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

void Model::SetPosition(double newX, double newY)
{
    xPos = newX;
    yPos = newY;
}

void Model::SetWidth(double newWidth)
{
   width = newWidth;
}

void Model::Update()
{
    if(name != "Player")
        DrawModel();
}

bool Model::CheckCollision()
{
    return false;
}

///////////////////////
////// Collision //////
///////////////////////

bool Model::Collision(Model* collider)
{
    double widthOffset = width / 2, heightOffset = height / 2;
    if(name == "player")
    {
        // temporary workaround for player collision. Don't like this.
        widthOffset = width / 4;
        heightOffset = width / 2.6;
    }
    return Overlapping(xPos - widthOffset, xPos + widthOffset, collider->GetX() - collider->GetWidth() / 2,
                       collider->GetX() + collider->GetWidth() / 2) &&
           Overlapping(yPos - heightOffset, yPos + heightOffset, collider->GetY() - collider->GetHeight() / 2,
                       collider->GetY() + collider->GetHeight() / 2);
}

bool Model::CheckCircleCollision()
{
    return false;
//    if(name == "MusicCircle")
//    {
//        for(auto& enemy : GLScene::movableObjects)
//        {
//            if(enemy->GetTag() == "Enemy")
//            {
//                if(CollisionCircle(enemy))
//                    cout << "Music Hit " << enemy->GetName() << endl; // put enemy damage in here later.
//            }
//        }
//    }
}

bool Model::CheckCircleSquareCollision()
{
    return false;
}

bool Model::Overlapping(double min0, double max0, double min1, double max1)
{
    // Square-square overlap
    return max0 >= min1 && min0 <= max1;
}

bool Model::OverlappingCircles(double x0, double y0, double x1, double y1, double r0, double r1)
{
    // circle-to-circle overlap
    double x = x1 - x0;
    double y = y1 - y0;
    double sumRadius = r0 + r1;

    double distance = sqrt((x * x) + (y * y)); // pythagoran theorem to calculate distance between center points of both circles

    return (distance <= sumRadius); // is the distance between both center points less than the sum of both radius's? If so, then we're overlapping with another circle.

}

void Model::Move()
{
    return; // virtual move function used for polymorphism in Player and Enemy classes
}
