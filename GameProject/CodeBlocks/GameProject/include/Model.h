#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include <glut.h>
#include <string>
#include <TextureLoader.h>
#include <AudioSource.h>
#include <cmath>
#include <TurnManager.h>

using namespace std;

typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();
        Model(float, float, double, double, string, string);
        Model(float, float, double, double, string, string, AudioSource*);
        virtual ~Model();
        void DrawModel();
        void InitModel(string fileName, bool transparent);

        void InitPlayer();

        double rotateX, rotateY, rotateZ;
        double zoom;
//        string direction;
        vec vertices[4];

        // collision getters
        double GetX();
        double GetY();
        float GetWidth();
        float GetHeight();
        void SetPosition(double, double);
        void SetWidth(double);

        virtual void Update();

        bool Collision(Model*);

        string GetName();
        string GetTag();

        virtual void Move();
        virtual void Destroy();

        void SetZoom(double newZoom);

    protected:
        float width, height, radius;
        double xPos, yPos;
        string name, tag;
        TextureLoader *texture;

        // This model will check square-to-square collision with other objects. Useful for certain types of environmental collision maybe
        virtual bool CheckCollision();

    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
        bool OverlappingCircles(double x0, double y0, double x1, double y1, double r0, double r1);
};

#endif // MODEL_H
