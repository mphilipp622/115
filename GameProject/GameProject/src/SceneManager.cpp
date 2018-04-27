#include "SceneManager.h"
#include <GLScene.h>

unordered_map<string, GLScene*> SceneManager::scenes;
string SceneManager::activeScene;

SceneManager::SceneManager()
{
    //ctor
    activeScene = "MainMenu";
    scenes = {};
}

SceneManager::~SceneManager()
{
    //dtor
}

