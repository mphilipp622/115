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
        Model(int newX, int newY, int newWidth, int newHeight, string newTag);
        virtual ~Model();
        void DrawModel();
        void InitModel(string fileName, bool transparent);

        double rotateX, rotateY, rotateZ;
        double zoom;
//        string direction;
        vec vertices[4];

        // collision getters
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();
        void SetPosition(int newX, int newY);
        void SetWidth(int newWidth);
        void SetHeight(int newHeight);

        string GetTag();
    protected:
        int width, height;
        int xPos, yPos;
        string tag;

        // returns an integer representing a type of tile
        int Collision();

    private:
};

#endif // MODEL_H
