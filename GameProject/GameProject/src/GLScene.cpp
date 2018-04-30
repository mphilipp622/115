// updated 2/7/18

#include <GLScene.h>
#include <GLLight.h>
#include <DeltaTime.h>
#include <Timer.h>
#include <UserInterface.h>
#include <Projectile.h>

GLScene::GLScene()
{}

GLScene::GLScene(string newSceneName, string newFilepath)
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    gridSizeX = 0;
    gridSizeY = 0;
    mapFilePath = newFilepath;
    sceneName = newSceneName;

    activeEnemy = 0;

    // clear static vectors when scene is loaded, just in case there is still data in them.
    enemies.clear();

    auto finder = SceneManager::scenes.find(sceneName); // find if this scene exists in SceneManager

    if(finder == SceneManager::scenes.end())
    {
        // if scene isn't in scenemanager yet, add it
        SceneManager::scenes.insert( {sceneName, this} );
        SceneManager::activeScene = sceneName;
    }
    else
    {
        // Otherwise, update SceneManager's entry for this scene
        SceneManager::scenes[sceneName] = this;
        SceneManager::activeScene = sceneName;
    }

    if(!AudioEngine::engine->isCurrentlyPlaying("Audio/Music/Anxious.mp3"))
    {
        // Start background music if it is not already playing. This will allow the music to keep looping
        // if the user decides to retry the level instead of going to main menu when they lose/win.
        BGM = new AudioSource("Audio/Music/Anxious.mp3", 0.9, true);
        BGM->PlayMusic();
    }

}


GLScene::~GLScene()
{
}

// Static Variables for use in player and enemy class to check collisions
Projectile* GLScene::arrow;
vector<Model*> GLScene::enemies;

// Will be updated by the Enemy class to iterate through the list of enemies and let them move.
int GLScene::activeEnemy;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    // Initialize Models Here
    GenerateGrid();
    UserInterface::UI = new UserInterface();

    dTime = new DeltaTime(); // initialize delta time
    return true;
}

GLint GLScene::drawGLScene()
{
    // Draw all our models onto the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position and focal point
    gluLookAt(gridSizeX / 2, gridSizeY / 2 - 0.5, gridSizeX + 3.33 + 1.5,
            gridSizeX / 2, gridSizeY / 2 - 0.5, 0,
            0.0f, 1.0f, 0.0f);

    CheckWinCondition(); // check if win or lose condition has been met

    if(!WinLose::winLose->IsGameOver() && enemies.size() <= 0)
        // check and see if all enemies are dead. IF so, then player wins
        WinLose::winLose->Win();

    if(UserInterface::UI)
        UserInterface::UI->DrawArrows(); // render arrow icons to screen

    for(auto& tile : grid->GetTiles())
    {
        // iterate over every tile in the grid and draw them on screen
        for(auto& tile2 : tile)
            tile2->DrawModel();
    }

    if(arrow)
        // If an arrow has been fired, run its Update() function
        arrow->Update();

    if(enemies.size() > 0)
    {
        if(TurnManager::turnManager->IsEnemyTurn())
        {
            // if it's the enemy's turn, activate the next active enemy. This allows the enemy to move
            if(!enemies[activeEnemy]->IsActive())
                enemies[activeEnemy]->SetActive();
        }

        for(auto& enemy : enemies)
        {
            // Iterate over the list of enemies and run their Update() functions for rendering them to screen and moving the active enemy.
            enemy->Update();
        }
    }

    Player::player->Update(); // Player updates every frame. Draws player to screen and executes movement.

    dTime->UpdateDeltaTime(); // Gets time between last frame and this frame

	return 1;
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    // Handle window resizing.
    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;

    glViewport(0, 0, width, height); // window for our game
    glMatrixMode(GL_PROJECTION); // set the projection type for 3D space
    glLoadIdentity(); // loads identity matrix
    gluPerspective(45.0, aspectRatio, 0.1, 100); // 45 degree angle, aspect ratio, 0.1 near to 100 far. Sets the perspective of our renderer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // loads identity matrix for modelview

}
int GLScene::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Handle keyboard inputs. All menu elements are selected using numeric keys 0 - 9.

    if(uMsg == WM_KEYDOWN)
    {
        if(WinLose::winLose->IsGameOver())
        {
            // If the game is over, user can choose 1. Replay Level or 2. Main Menu
            if(wParam == VK_NUMPAD1 || wParam == 0x31) // 0x31 is hex value for keypad 1
                LoadScene("Game");
            else if(wParam == VK_NUMPAD2 || wParam == 0x32) // 0x32 is hex value for keypad 2
                LoadScene("MainMenu");
        }

        if(TurnManager::turnManager->IsEnemyTurn() || WinLose::winLose->IsGameOver())
            return 1; // don't allow input if it's not player's turn or if the game is over

        Player::player->SetInput(wParam); // Tells the player if they should move or shoot an arrow.
    }

	return 1;
}

void GLScene::GenerateGrid()
{
    ifstream in(mapFilePath); // get an input stream from our filepath

    string line; // will store each line of text

	for (int i = 0; !in.eof(); i++)
	{
	    // iterate over every line of the file.

		getline(in, line); // read first row of data
		gridMap.push_back(vector<int>()); // create a new vector to represent x-values for this row

		if(gridSizeX == 0)
            gridSizeX = line.size(); // only assign x size the first time we iterate

		for (int j = 0; j < gridSizeX; j++)
            // Assign a type to this (x, y) coordinate
			gridMap[i].push_back(line.at(j) - '0'); // convert from ascii to int

		gridSizeY = i + 1; // increment y dimension of maze
	}

	grid = new Grid(gridSizeX, gridSizeY, gridMap); // assign the grid pointer to a new grid. Constructor handles creation of Tiles

	// Once the grid is initialized, we need to look specifically for our enemies and players and assign them in the scene.
    for(int i = 0; i < gridSizeX; i++)
    {
        for(int j = 0; j < gridSizeY; j++)
        {
            if(grid->GetTile(i, j)->GetType() == Type::player)
                Player::player = new Player(i, j); // create player
            if(grid->GetTile(i, j)->GetType() == Type::enemy)
                // populate enemy vector
                enemies.push_back(new Enemy(i, j, "Enemy" + to_string(i) + to_string(j)));
        }
    }
}

void GLScene::CheckWinCondition()
{
    // Opens the UI and locks player input if win or loss condition has happened
    if(WinLose::winLose->HasWon())
        UserInterface::UI->YouWin();
    else if(WinLose::winLose->HasLost())
        UserInterface::UI->YouLose();
}

void GLScene::LoadScene(string name)
{
    // Handles going from this scene to another scene

    if(name == "Game")
    {
        // reload the scene
        GLScene* newGame = new GLScene(sceneName, mapFilePath); // create new scene

        SceneManager::scenes[sceneName] = newGame; // set the key value pair in hash table to the new instance
        Reset(); // reset static data

        newGame->initGL(); // initialize new scene

        delete this; // kill old scene
    }
    else if(name == "MainMenu")
    {
        Reset(); // reset static data
        BGM->Stop(); // stop music

        // find the scene in scene manager
        auto finder = SceneManager::scenes.find(sceneName);

        if(finder != SceneManager::scenes.end())
            // Remove the scene from scene manager
            SceneManager::scenes.erase(finder);

        SceneManager::activeScene = "MainMenu"; // set active scene to main menu
        delete this; // delete this scene
    }
}

string GLScene::GetSceneName()
{
    return sceneName; // return scene name
}

void GLScene::Reset()
{
    // reset static data
    UserInterface::UI->Reset();
    WinLose::winLose->Reset();
    TurnManager::turnManager->SetTurn(0);
    activeEnemy = 0;
}
