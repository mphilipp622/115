#include "MainMenu.h"

MainMenu::MainMenu()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "MainMenu";

    SceneManager::scenes.insert( {"MainMenu", this} );
    SceneManager::activeScene = "MainMenu";

    audioEngine = new AudioEngine();

    killGame = false;
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

    InitModels();

}

void MainMenu::InitModels()
{
    // instantiate UI elements
    background = new Model(1.0, 1.0, 0, 0, "Background", "BG");
    exit = new Model(1.0, 0.25, 0, 1.4 - (0.3 * 9), "ExitButton", "Button");
    exit->SetZoom(-4.0);

    for(int i = 0; i < 9; i++)
    {
        maps.push_back(new Model(1.0, 0.25, 0, 1.4 - (0.3 * i), "MapButton" + to_string(i), "Button"));
        maps.at(i)->SetZoom(-4.0);
    }

    // Bind textures for UI elements
    background->InitModel("Images/MainMenuBG.jpg", true);
    exit->InitModel("Images/UI/Exit.png", true);

    for(int i = 0; i < 9; i++)
        maps.at(i)->InitModel("Images/UI/MapButton" + to_string(i + 1) + ".png", true);

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

    for(auto& button : maps)
        button->DrawModel();

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

        GLScene* newMap = new GLScene("Game" + to_string(num), "Maps/Map" + to_string(num) + ".txt"); // create new map

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
        else if(wParam == VK_NUMPAD2 || wParam == 0x32)
            LoadScene(2);
        else if(wParam == VK_NUMPAD3 || wParam == 0x33)
            LoadScene(3);
        else if(wParam == VK_NUMPAD4 || wParam == 0x34)
            LoadScene(4);
        else if(wParam == VK_NUMPAD5 || wParam == 0x35)
            LoadScene(5);
        else if(wParam == VK_NUMPAD6 || wParam == 0x36)
            LoadScene(6);
        else if(wParam == VK_NUMPAD7 || wParam == 0x37)
            LoadScene(7);
        else if(wParam == VK_NUMPAD8 || wParam == 0x38)
            LoadScene(8);
        else if(wParam == VK_NUMPAD9 || wParam == 0x39)
            LoadScene(9);

    }

	return 1;
}
