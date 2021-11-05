#include "NEGame.h"
#include "NEScene.h"
using namespace NeapuEngine;

Game::Game() 
    : m_pCurrentScene(nullptr)
{
    
}

Game::~Game() 
{
    
}

bool Game::addScene(Scene* scene) 
{
    String strSceneName = scene->name();
    if(m_SceneList.find(strSceneName)==m_SceneList.end()){
        m_SceneList[strSceneName] = scene;
        if(!m_pCurrentScene){
            m_pCurrentScene = scene;
            m_strCurrentSceneName = strSceneName;
        }
        
        return true;
    }
    return false;
}
