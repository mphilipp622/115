// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include <Model.h>
#include <unordered_map>
#include <AudioSource.h>
#include <AudioEngine.h>
#include <DeltaTime.h>
#include <Player.h>
#include <Grid.h>
#include <fstream>
#include <Enemy.h>
#include <TurnManager.h>
#include <SceneManager.h>
#include <UserInterface.h>

using namespace std;

class Projectile; // forward declaration of Projectile class. This is the result of including conflicting header files.

// This class is where screen rendering for OpenGL objects occurs. Different levels and menus inherit from this
class GLScene
{
    public:
        GLScene();
        GLScene(string newSceneName, string newFilepath);
        virtual ~GLScene();

        // Initialize the OpenGL renderer.
        virtual GLint initGL();

        // Main gameplay loop for frame updating.
        virtual GLint drawGLScene();

        // Handles window resizing.
        GLvoid resizeGLScene(GLsizei, GLsizei);

        // Handles mouse and keyboard input
        virtual int windowsMsg(HWND, UINT, WPARAM, LPARAM);

        // Handles the loading of scenes. E.G: Loading main menu or replaying the current level
        virtual void LoadScene(string name);

        // Returns the name of this scene
        string GetSceneName();

        // Used for keyboard inputs
        WPARAM wParam;

        // Screen height and width in pixel values
        float screenHeight, screenWidth;

        static Projectile* arrow; // static Projectile that's used when spawning and moving arrows.
        static vector<Model*> enemies; // contains all the enemies in a scene
        static int activeEnemy; // tracks which enemy is the active enemy

    protected:
        AudioSource* BGM; // Background music for the scene

        string sceneName;

    private:

        // Generates a grid based on this scene's mapFilePath.
        void GenerateGrid();

        DeltaTime* dTime; // Updated in DrawGLScene() so other classes can use it for animation/movement smoothing

        int gridSizeX, gridSizeY; // tracks the x and y size of the grid
        string mapFilePath; // tracks the filepath for the maze layout

        Grid* grid; // pointer to the grid, which contains the maze tiles and other information.

        vector<vector<int>> gridMap; // only used for maze initialization. Will read .txt file integers into here

        // Checks if a win/loss condition has been met. Called in Update()
        void CheckWinCondition();

        // Resets static and global data.
        void Reset();

};

#endif // GLSCENE_H
