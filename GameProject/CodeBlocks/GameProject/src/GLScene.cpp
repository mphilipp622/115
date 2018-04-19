// updated 2/7/18

#include <GLScene.h>
#include <GLLight.h>
#include <DeltaTime.h>
#include <Timer.h>

//Model *ground = new Model(6.0, 0.3, 0, -1.0, "ground", "Environment");
//Model *block = new Model(2.0, 0.2, 3.0, 0, "block", "Environment");
//Model *block2 = new Model(2.0, 0.2, -0.5, 1.0, "block2", "Environment");
Model* temp1 = new Model(0.5, 0.5, 0, 0, "test", "type");
Timer *sceneTimer = new Timer();
Model* temp2 = new Model(0.5, 0.5, 4, 4,"test2", "type");



GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    gridSizeX = 0;
    gridSizeY = 0;
    mapFilePath = "Maps/TestMap.txt";

//    testEnemy = new MeleeEnemy(0.7, 0.7, 2, 0.5, "TestEnemy");
}

GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::staticObjects;
vector<Model*> GLScene::enemies;

// static input for player to use as well
Inputs* GLScene::keyboardAndMouse;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{

    audioEngine = new AudioEngine();
//    player = new Player(0.0, 0);
//    testEnemy = new MeleeEnemy(0.7, 3, 0.8, 0.8, "Enemy");

    keyboardAndMouse = new Inputs();
    sceneTimer->Start();

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    GenerateGrid();

    temp1->InitModel("Images/wall.png", true);
    temp2->InitModel("Images/Block.png", true);
    // Initialize Models Here
//    cout << "Parallax Initializing" << endl;

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
    gluLookAt(0, 0, 6,
            0, 0, 0,
            0.0f, 1.0f, 0.0f);
//    glPushMatrix();
////    glScaled(3.33, 3.33, 1);
//    sky->DrawBox();
//    glPopMatrix();
//    glPushMatrix();
//    glScaled(12, 12, 1);
//    glPopMatrix();
//    glPushMatrix();
//    glScaled(12, 12, 1);
//    glPopMatrix();

    temp1->DrawModel();
    temp2->DrawModel();

//    for(auto& tile : grid->GetTiles())
//    {
//        for(auto& tile2 : tile)
//            tile2->DrawModel();
//
//    }

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
//        testAudio->UpdatePosition();

//        testAudio->Update();
//        testAudio->Play();
//        PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
        keyboardAndMouse->wParamKeys = wParam;
        keyboardAndMouse->KeyPressed(player);
    }
    if(uMsg == WM_KEYUP)
    {
        keyboardAndMouse->wParamKeys = wParam;
        keyboardAndMouse->KeyUp(player);
    }
    if(uMsg == WM_MOUSEMOVE)
    // should constantly update mouse pointer x and y positions
        keyboardAndMouse->SetMousePointer(LOWORD(lParam), HIWORD(lParam));
    if(uMsg == WM_LBUTTONDOWN)
    {
        // left-click functionality
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(player, lParam);
    }
    if(uMsg == WM_RBUTTONDOWN)
    {
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(player, lParam);
    }
//    if(uMsg == WM_MOUSEWHEEL)
//        keyboardAndMouse->WheelMove(player, GET_WHEEL_DELTA_WPARAM(wParam));

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

//	for (int i = 0; i < gridSizeX; i++)
//	{
//		for (int j = 0; j < gridSizeY; j++)
//			cout << grid->GetTile(i, j)->GetType();
//		cout << endl;
//	}
}

