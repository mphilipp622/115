#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include <glut.h>
#include <string>
#include <TextureLoader.h>
#include <AudioSource.h>
#include <cmath>
#include <TurnManager.h>
#include <Timer.h>

using namespace std;

// Used for x,y,z vertex values of this model
typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();

        // Constructor used for UI Elements
        Model(float, float, double, double, string, string);

        virtual ~Model();

        // Renders model in openGL
        void DrawModel();

        // Assigns model a texture
        void InitModel(string fileName, bool transparent);

        // array of vertices
        vec vertices[4];

        // collision getters
        double GetX();
        double GetY();
        float GetWidth();
        float GetHeight();

        // Update is called every frame in GLScene. Overridden in child classes
        virtual void Update();

        bool Collision(Model*); // Returns true if this model collides with the passed-in Model

        string GetName();
        string GetTag();

        // Allows the model to move in the scene. Overridden by children.
        virtual void Move();

        // Destroys this model, freeing memory. Overridden by children.
        virtual void Destroy();

        // Sets the x position of this model.
        void SetZoom(double newZoom);

        // Changes UI Button elements. Only used if this model instance is intended to be a UI element
        void ChangeImage(string filename);

        // Draws background images
        void DrawSquare(float newWidth, float newHeight);

        // Returns if this model is active. Only used by Enemy child
        bool IsActive();

        // Sets this model to active. Only used by Enemy child
        void SetActive();

    protected:
        // dimension values
        float width, height;

        // x and y positions
        double xPos, yPos;

        string name, tag;

        TextureLoader *texture; // texture for this model

        // rotation values for the model.
        double rotateX, rotateY, rotateZ;

        // z position for the model
        double zoom;

        // This model will check square-to-square collision with other objects. Useful for certain types of environmental collision maybe
        virtual bool CheckCollision();

        bool active; // tracks active status of this model. Used by Enemy child class

    private:
        // Helper function for determining if two objects are overlapping with each other. Collision checking
        bool Overlapping(double min0, double max0, double min1, double max1);
};

#endif // MODEL_H
