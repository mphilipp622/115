// updated 2/7/18

#include <GLScene.h>
#include <GLLight.h>
#include <Inputs.h>
//#include <Parallax.h>
#include <DeltaTime.h>
#include <Player.h>
//#include <Skybox.h>


//Model *modelTeapot = new Model();
Inputs *keyboardAndMouse = new Inputs();
Model *ground = new Model(0, 0, 1, 1, "ground");
//Model *ground = new Model(6.0, 0.2, 0, -1.0, "ground");
//Model *block = new Model(2.0, 0.2, 3.0, 0, "block");
//Model *block2 = new Model(2.0, 0.2, -0.5, 1.0, "block2");
Player *testPlayer = new Player(0, 0);

DeltaTime* dTime = new DeltaTime();
//Skybox* sky = new Skybox();
// Can create multiple Parallax objects to create parallaxed backgrounds
//Parallax *plx = new Parallax();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen
}

GLScene::~GLScene()
{
}


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
//    cout << "Parallax Initializing" << endl;
//    plx->ParallaxInit("Images/background.jpg");
//
//    block->InitModel("Images/Block.png", true);
//    ground->InitModel("Images/Block.png", true);
    ground->InitModel("Images/StoneGround.jpg", false);
    dTime ->UpdateDeltaTime();

//    sky->LoadTextures();

    testPlayer->InitPlayer();
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//    gluLookAt(Player::player->GetX(), Player::player->GetY(), 0.0,
//            Player::player->GetX(), Player::player->GetY(), Player::player->GetZoom(),
//            0.0f, 1.0f, 0.0f);
//    glPushMatrix();
////    glScaled(3.33, 3.33, 1);
//    sky->DrawBox();
//    glPopMatrix();
//    glPushMatrix();
//    glScaled(3.33, 3.33, 1);
//    plx->DrawSquare(screenWidth, screenHeight); // draw background
//    glPopMatrix();

//    for(auto& model : staticObjects)
//    {
//        glPushMatrix();
//        model->DrawModel();
//        glPopMatrix();
//    }
//    glPushMatrix(); // remove push/pop if you want things to interact with each other in the renderer
//    block->DrawModel();
//    glPopMatrix();
//
//    glPushMatrix();
//    ground->DrawModel();
//    glPopMatrix();
    glPushMatrix();
    ground->DrawModel();
    glPopMatrix();

//    testPlayer->Update();


//    glTranslatef(testPlayer->GetX(), testPlayer->GetY(), 0);
//    gluLookAt(testPlayer->GetX(), testPlayer->GetY(), -10.0, testPlayer->GetX(), testPlayer->GetY(), -1.0, 0, 1.0, 100.0);

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
    switch (uMsg)									// Check For Windows Messages
	{
        case WM_KEYDOWN:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->KeyPressed(testPlayer);
//            keyboardAndMouse->KeyEnv(plx, 0.1);
            break;

        case WM_KEYUP:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->KeyUp(testPlayer);
            break;
	}

	return 1;
}
