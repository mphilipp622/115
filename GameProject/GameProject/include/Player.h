#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <Model.h>
#include <TextureLoader.h>
#include <Grid.h>
#include <Projectile.h>
#include <WinLose.h>

class Player : public Model
{
    public:
        Player();
        Player(double newX, double newY);
        virtual ~Player();

        // Begins the move process for the player. Sets flags that work with MoveToDestination()
        void Move(double dirX, double dirY);

        // Creates an Arrow object and shoots it in the specified direction
        void ShootProjectile(double x, double y);

        // Global static getter for the player object. There is only one of these in the game
        static Player* player;

        // Called on by GLScene::DrawGLScene() every frame. Handles movement and rendering the model
        void Update();

        // Locks the user from moving or firing while an arrow is active. Called from Projectile::Destroy()
        void SetLocked();

        // Parses keyboard input for moving and shooting
        void SetInput(WPARAM newParam);

        // Returns the number of arrows the player has. Used by UserInterface::UserInterface() constructor
        int GetArrowCount();

        // Plays death sound and sets lose condition,
        void Die();

    protected:

    private:
        // Animation variables
        int runFrame, idleFrame;
        TextureLoader runRight[6];
        TextureLoader runLeft[6];
        TextureLoader runDown[6];
        TextureLoader runUp[6];
        TextureLoader idleRight[1];
        TextureLoader idleLeft[1];
        TextureLoader idleUp[1];
        TextureLoader idleDown[1];

        float moveSpeed; // adjusts the speed the player moves

        Timer* frameTimer; // used for rendering animations

        int arrowCount; // tracks the number of arrows the player has

        bool playerLocked; // will be used to stop user input while arrows move
        bool isMoving;

        // Movement and shooting variables
        int destX, destY, xDir, yDir;

        // Moves player to destination over time
        void MoveToDestination();

        // Animates the player
        void Animate(string animation);

        // Renders player in the OpenGL window
        void DrawPlayer();

        // Initializes Player Animations
        void InitAnimations();

        // SFX variables
        AudioSource* arrowSound;
        AudioSource* dyingSound;
};

#endif // PLAYER_H
