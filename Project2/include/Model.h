#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include <glut.h>
#include <string>

using namespace std;

typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();
        Model(float newX, float newY, float newWidth, float newHeight, string newTag);
        virtual ~Model();
        void DrawModel();
        void InitModel(string fileName, bool transparent);

        double rotateX, rotateY, rotateZ;
        double zoom;
//        string direction;
        vec vertices[4];

        // collision getters
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        void SetPosition(float newX, float newY);
        void SetWidth(float newWidth);
        void SetHeight(float newHeight);

        string GetTag();
    protected:
        float width, height;
        float xPos, yPos;
        string tag;

        // returns an integer representing a type of tile
        int Collision();

    private:
};

#endif // MODEL_H
