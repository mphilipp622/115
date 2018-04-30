Mark Philipp
Isaac Fielding
CSCI 115 Project 2

Introduction and How to Play
-----------------------

This project is a 2D, turn-based game where the user plays as a character who must navigate a maze and either destroy all the enemies or get the treasure. If either of the previously mentioned conditions are met, the player wins. If an enemy lands on the player, the player dies and the user loses.

The user can MOVE the player by using WASD on the keyboard. They can shoot arrows using the arrow keys. Any movement or any shooting consumes the player's turn and initiates the enemy turn.

W = Move Up			Up Arrow = Shoot Up
S = Move Down		Down Arrow = Shoot Down
A = Move Left		Left Arrow = Shoot Left
D = Move Right		Right Arrow = Shoot Right

The player starts with 1 arrow and can pick up more arrows off the ground by walking on top of tiles that have arrows on them. The number of arrows the player has is indicated by a UI element near the top of the window.

Compiling the Project
---------------------

1. This project MUST be compiled in the Code::Blocks IDE due to the nature of the glut and SOIL libraries that are used for graphics.

2. This project must also be compiled and run using a Windows computer due to the use of the windows.h header file for keyboard input and graphics implementations.

3. Make sure that the "Common" folder that was included in the .zip file for this project has NOT been moved from the same directory as this readme file.

4. Make sure -std=c++11 compiler flag is enabled by opening the project in code blocks and going to Project -> Build Options -> under the "Compiler Settings" -> "Compiler Flags" section, make sure "Have g++ follow the c++11 ISO C++ language standard [-std=c++11]" box is checked.

Running the Project as an EXE
-----------------------------

A Debug release .exe file can be found in the project directory. It is called "GameProject.exe". 

Fatal DLL Errors When Running Program
--------------------------------------

This should not happen, but if you experience a fatal error stating the "Application Failed To Load", then you need to copy the DLL files from the "DLLs" folder into your C:\Windows\system32 folder.

Relevant CPP Files for Grading
------------------------------

- The Maze implementation can be found in Grid.h and Grid.cpp. The initial maze generation occurs in GLScene::GenerateGrid()

- The player implementation can be found in Player.h and Player.cpp.

- The enemy implementation can be found in Enemy.h and Enemy.cpp.

- GLScene.h and GLScene.cpp are core files that run the gameplay loop. This class calls on Enemy and Player Update() functions, which drive much of the player and enemy functionality.

- Drawing the Maze is done in GLScene::DrawGLScene()

- Collisions are checked whenever the player or an enemy attempts to move onto a new tile. These collisions can be checked in Player::MoveToDestination() and Enemy::MoveToDestination()

- Arrow collisions are checked using width and height boundaries on objects. This implementation can be found in Projectile::CheckCollision(), Projectile::CheckCollisionEnemy() and Model::Collision(Model*).

- Shortest Path can be found in the Pathfinder.h and Pathfinder.cpp files. Pathfinder::GetNextTile(int, int) is where the A* implementation occurs.

- Win and Loss conditions are checked in multiple files:
	- Player Gets Chest is in Player::MoveToDestination()
	- Player Dies is in Player::Die()
	- All Enemies are Dead is in GLScene::DrawGLScene()

- Win and Loss states are managed by the WinLose class.

- Loading the maze from a file is handled by GLScene::GenerateGrid(), which passes the data to Grid::Grid() constructor.

- Scene loading is handled by GLScene::LoadScene(string) and MainMenu::LoadScene(string). Both functions utilize the SceneManager class to tell OpenGL which scene to draw, which is done in main.cpp

- The Main Menu is implemented in MainMenu.cpp.

- Some menu elements within GLScene are handled by the UserInterface class. Additionally, the arrow graphic that represents the number of arrows the player has is handled by UserInterface.cpp.

Maps and Map Creation
---------------------

The maps can be found in GameProject\Maps. There are 9 maps that are in use in the game. Map files can be edited by opening them inside of a text editor and modifying the data. Each tile of the maze is represented by an integer value. The mapping is as follows:

0 = traversable tile
1 = wall
2 = enemy
3 = player
4 = treasure
5 = arrows

If you wish to make your own map, simply create a new text file inside the Maps folder and populate it with the data you want. The filename MUST follow this syntax:

Map<num>.txt

where <num> is an integer value between 1 and 9.

Note that your map X and Y sizes MUST be the same. This means your map cannot be 8 x 4, for instance. It would have to be 8 x 8 or 4 x 4.