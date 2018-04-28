#ifndef ENEMY_H
#define ENEMY_H

#include <Pathfinder.h>
#include <Grid.h>
#include <Player.h>


using namespace std;

class Pathfinder;

class Enemy : public Model
{
    public:
        Enemy();
        Enemy(double newX, double newY, string newName);
        virtual ~Enemy();

        // Move is called once when enemy's turn begins. Will start pathfinding and set a destination to move to.
        void Move();

        // Update is called by GLScene every frame. Continuous functionality is implemented here.
        void Update();

        // Performs a cleaning routine that will delete the enemy and remove it from the enemies vector in GLScene
        void Destroy();

    protected:

    private:

        // Arrays of texture loaders for sprite animations
        TextureLoader moveRight[4];
        TextureLoader moveLeft[4];
        TextureLoader moveDown[4];
        TextureLoader moveUp[4];
        TextureLoader idleLeft[1];
        TextureLoader idleRight[1];
        TextureLoader idleUp[1];
        TextureLoader idleDown[1];

        // Keeps track of animation frames for movement
        int moveFrame;

        // Location variables
        int xDir, yDir, destX, destY;

        // timer for rendering at specific FPS
        Timer* frameTimer;

        // Pathfinding class
        Pathfinder* pathfind;

        // Called by constructor. Initializes the TextureBinders for animations
        void InitAnimations();

        // Animates the enemy based on movement
        void Animate(string animation);

        // Affects the speed of the enemies.
        float moveSpeed;

        // Called on in Update(). Progressively moves enemy to next tile in the shortest path.
        void MoveToDestination();

        // Flag for Update() to know if enemy should be moving or not.
        bool isMoving;

        // Renders enemy on screen
        void DrawEnemy();

        // Dying sound effect for enemy.
        AudioSource* dyingSound;
};

#endif // ENEMY_H
