#include "MainMenu.h"

MainMenu::MainMenu()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "MainMenu";

    SceneManager::scenes.insert( {"MainMenu", this} );
    SceneManager::activeScene = "MainMenu";

    background = new Model(1.0, 1.0, 0, 0, "Background", "BG");
    exit = new Model(1.0, 0.25, 0, -1.0, "ExitButton", "Button");
    exit->SetZoom(-4.0);
}

MainMenu::~MainMenu()
{
    //dtor
}

GLint MainMenu::initGL()
{
    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);


    background->InitModel("Images/MainMenuBG.jpg", true);
    exit->InitModel("Images/UI/Exit.png", true);
}

GLint MainMenu::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    if(killGame) // exit game
        return 0;

    glPushMatrix();
    glScaled(3.33,3.33,1.0);
    background->DrawSquare(screenWidth, screenHeight);
    glPopMatrix();

    exit->DrawModel();

    return 1;
}

void MainMenu::LoadScene(int num)
{
    if(num == 0)
        killGame = true;
    else
    {
            // if we already have this map loaded, we want to delete it
        auto finder = SceneManager::scenes.find("Game" + to_string(num));

        if(finder != SceneManager::scenes.end())
            delete SceneManager::scenes["Game" + to_string(num)]; // if hashtable already has map loaded, delete it

        GLScene* newMap = new GLScene(); // create new map

        SceneManager::scenes.insert( {"Game" + to_string(num), newMap} ); // insert map into hash table
        newMap->initGL(); // initialize map

        SceneManager::activeScene = "Game" + to_string(num);
    }


}

int MainMenu::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg == WM_KEYDOWN)
    {
        if(wParam == VK_NUMPAD0 || wParam == 0x30)
            LoadScene(0);
        else if(wParam == VK_NUMPAD1 || wParam == 0x31)
            LoadScene(1);
//        if(wParam == VK_NUMPAD1 || wParam == 0x31) // 0x31 is hex value for keypad 1
//            LoadScene("Game");
//        else if(wParam == VK_NUMPAD2 || wParam == 0x32) // 0x32 is hex value for keypad 2
//            LoadScene("MainMenu");

    }

	return 1;
}
