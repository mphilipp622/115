#ifndef MAINMENU_H
#define MAINMENU_H

#include <GLScene.h>
#include <GLLight.h>

class MainMenu : public GLScene
{
    public:
        MainMenu();
        virtual ~MainMenu();

        GLint initGL();
        GLint drawGLScene();

        void LoadScene(int num);

        int windowsMsg(HWND,UINT, WPARAM,LPARAM);

    protected:

    private:
        vector<Model*> maps;
        Model* background;
        Model* exit;

        double screenWidth, screenHeight;
        bool killGame;
};

#endif // MAINMENU_H
