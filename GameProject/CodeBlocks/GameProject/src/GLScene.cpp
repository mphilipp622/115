// updated 2/7/18

#include <GLScene.h>
#include <GLLight.h>
#include <DeltaTime.h>
#include <Timer.h>
#include <UserInterface.h>

//Model *ground = new Model(6.0, 0.3, 0, -1.0, "ground", "Environment");
//Model *block = new Model(2.0, 0.2, 3.0, 0, "block", "Environment");
//Model *block2 = new Model(2.0, 0.2, -0.5, 1.0, "block2", "Environment");
Timer *sceneTimer = new Timer();
//Model* temp2 = new Model(1, 1, 0, 1,"test2", "type");

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    gridSizeX = 0;
    gridSizeY = 0;
    mapFilePath = "Maps/TestMap.txt";
    sceneName = "Game";

    // clear static vectors when scene is loaded, just in case there is still data in them.
    enemies.clear();
    movableObjects.clear();

    auto finder = SceneManager::scenes.find("Game");

    if(finder == SceneManager::scenes.end())
    {
        // if scene isn't in scenemanager yet, add it
        SceneManager::scenes.insert( {"Game", this} );
        SceneManager::activeScene = "Game";
    }
//    testEnemy = new MeleeEnemy(0.7, 0.7, 2, 0.5, "TestEnemy");
}

GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::enemies;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{

    audioEngine = new AudioEngine();
//    player = new Player(0.0, 0);
//    testEnemy = new MeleeEnemy(0.7, 3, 0.8, 0.8, "Enemy");

    sceneTimer->Start();

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

//    block->InitModel("Images/Block.png", true);
//    block2->InitModel("Images/Block2.png", true);
//    ground->InitModel("Images/Block.png", true);
//

//    movableObjects.push_back(player);
//    enemies.push_back(testEnemy);
////    movableObjects.push_back(testEnemy);
//
//    staticObjects.push_back(block);
//    staticObjects.push_back(ground);
//    staticObjects.push_back(block2);

//    sky->LoadTextures();
//
//    player->InitPlayer();
//    Player::player = player;
//    testEnemy->InitEnemy();

//    BGM = new AudioSource("Music", "Audio/Music/BGM/DrumLoop.wav",0, 0, .8, true);
//    BGM->PlayMusic();
    dTime = new DeltaTime();
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(gridSizeX / 2, gridSizeY / 2, gridSizeX + 3.33 + 1,
            gridSizeX / 2, gridSizeY / 2, 0,
            0.0f, 1.0f, 0.0f);

    CheckWinCondition();

    if(!WinLose::winLose->IsGameOver() && enemies.size() <= 0) // check and see if all enemies are dead. IF so, then player wins
        WinLose::winLose->Win();

    if(UserInterface::UI)
        UserInterface::UI->DrawArrows(); // render arrow icons to screen

    for(auto& tile : grid->GetTiles())
    {
        for(auto& tile2 : tile)
            tile2->DrawModel();
    }

    for(auto& arrow : movableObjects)
        arrow->Update();

    for(auto& enemy : enemies)
    {
        if(TurnManager::turnManager->IsEnemyTurn())
            enemy->Move();

        enemy->DrawModel();
    }

    if(TurnManager::turnManager->IsEnemyTurn())
        TurnManager::turnManager->NextTurn(); // end turn after enemies have moved

    Player::player->DrawModel();
//    for(auto& model : staticObjects)
//        model->DrawModel();
//
//    for(auto& enemy : enemies)
//        enemy->Update();
//
//    for(auto& model : movableObjects)
//        model->Update();

    dTime->UpdateDeltaTime();

	return 1;
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
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
    if(uMsg == WM_KEYDOWN)
    {
        if(WinLose::winLose->IsGameOver())
        {
            if(wParam == VK_NUMPAD1 || wParam == 0x31) // 0x31 is hex value for keypad 1
                LoadScene("Game");
            else if(wParam == VK_NUMPAD2 || wParam == 0x32) // 0x32 is hex value for keypad 2
                LoadScene("MainMenu");
        }

        if(TurnManager::turnManager->IsEnemyTurn() || WinLose::winLose->IsGameOver())
            return 1; // don't allow input if it's not player's turn or if the game is over

        Player::player->SetInput(wParam);
    }

	return 1;
}

void GLScene::GenerateGrid()
{
    ifstream in(mapFilePath);

    string line;

	for (int i = 0; !in.eof(); i++)
	{
		getline(in, line); // read first row of data
		gridMap.push_back(vector<int>());
		gridSizeY = line.size();

		for (int j = 0; j < gridSizeY; j++)
			gridMap[i].push_back(line.at(j) - '0'); // convert from ascii to int

		gridSizeX = i + 1;
	}

	grid = new Grid(gridSizeX, gridSizeY, gridMap);

    for(int i = 0; i < gridSizeX; i++)
    {
        for(int j = 0; j < gridSizeY; j++)
        {
            if(grid->GetTile(i, j)->GetType() == Type::player)
                Player::player = new Player(i, j); // create player
            if(grid->GetTile(i, j)->GetType() == Type::enemy)
                enemies.push_back(new Enemy(i, j));

        }
    }
}

void GLScene::CheckWinCondition()
{
    if(WinLose::winLose->HasWon())
        UserInterface::UI->YouWin();
    else if(WinLose::winLose->HasLost())
        UserInterface::UI->YouLose();
}

void GLScene::LoadScene(string name)
{
    if(name == "Game")
    {
        GLScene* newGame = new GLScene();

        SceneManager::scenes["Game"] = newGame;
        Reset();
        newGame->initGL();

        delete this;
    }
    else if(name == "MainMenu")
    {
        Reset();
        SceneManager::activeScene = "MainMenu";
        delete this;
    }
}

string GLScene::GetSceneName()
{
    return sceneName;
}

void GLScene::Reset()
{
    UserInterface::UI->Reset();
    WinLose::winLose->Reset();
    TurnManager::turnManager->SetTurn(0);
}
