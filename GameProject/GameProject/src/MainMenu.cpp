#include "MainMenu.h"

MainMenu::MainMenu()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "MainMenu";

    // Add main menu to the Scene Manager
    SceneManager::scenes.insert( {"MainMenu", this} );
    SceneManager::activeScene = "MainMenu";

    // Initialize the audio engine. Will be used by other classes
    audioEngine = new AudioEngine();

    killGame = false;
}

MainMenu::~MainMenu()
{
    //dtor
}

GLint MainMenu::initGL()
{
    // Initialize openGL renderer for this scene

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    InitModels(); // initialize UI Elements
}

void MainMenu::InitModels()
{
    // instantiate UI elements
    background = new Model(1.0, 1.0, 0, 0, "Background", "BG");
    exit = new Model(1.0, 0.25, 0, 1.4 - (0.3 * 9), "ExitButton", "Button");
    exit->SetZoom(-4.0); // set the Z position. UI elements will be at -4

    for(int i = 0; i < 9; i++)
    {
        // initialize UI elements for selecting maps
        maps.push_back(new Model(1.0, 0.25, 0, 1.4 - (0.3 * i), "MapButton" + to_string(i), "Button"));
        maps.at(i)->SetZoom(-4.0); // set z position of this element to -4
    }

    // Bind textures for UI elements
    background->InitModel("Images/MainMenuBG.jpg", true);
    exit->InitModel("Images/UI/Exit.png", true);

    for(int i = 0; i < 9; i++)
        // assign texture to the UI element
        maps.at(i)->InitModel("Images/UI/MapButton" + to_string(i + 1) + ".png", true);

}

GLint MainMenu::drawGLScene()
{
    // Main loop. Render openGL elements to window every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    if(killGame) // exit game
        return 0;

    glPushMatrix();
    glScaled(3.33,3.33,1.0); // Scale the background image
    background->DrawSquare(screenWidth, screenHeight);
    glPopMatrix();

    exit->DrawModel(); // render exit button

    for(auto& button : maps)
        // draw all the UI elements
        button->DrawModel();

    return 1;
}

void MainMenu::LoadScene(int num)
{
    // Handle map loading. We pass an int so we can load a txt file that contains the same int number in the filename.
    if(num == 0)
        // if user selects to exit, end the game
        killGame = true;
    else
    {
        // If user selects a map, we need to load it and play it.

        // if we already have the selected map loaded, we want to delete it
        auto finder = SceneManager::scenes.find("Game" + to_string(num)); // find the scene in scene manager

        if(finder != SceneManager::scenes.end())
            delete SceneManager::scenes["Game" + to_string(num)]; // if hashtable already has map loaded, delete it

        GLScene* newMap = new GLScene("Game" + to_string(num), "Maps/Map" + to_string(num) + ".txt"); // create new map

        SceneManager::scenes.insert( {"Game" + to_string(num), newMap} ); // insert map into hash table
        newMap->initGL(); // initialize map

        SceneManager::activeScene = "Game" + to_string(num); // set active scene to the new scene.
    }
}

int MainMenu::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg == WM_KEYDOWN)
    {
        // Handle keyboard input. User can select options 0 - 9. Hex values represent numbers 0 - 9 at top of keyboard

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
