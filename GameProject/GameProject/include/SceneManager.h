#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <unordered_map>
#include <string>

using namespace std;

class GLScene;

class SceneManager
{
    public:
        SceneManager();
        virtual ~SceneManager();

        static string activeScene;
        static unordered_map<string, GLScene*> scenes;

    protected:

    private:
};

#endif // SCENEMANAGER_H
