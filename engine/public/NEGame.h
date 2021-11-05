#ifndef __NEGAME_H__
#define __NEGAME_H__

#include "NEString.h"
#include <functional>
#include <map>
namespace NeapuEngine {
class Scene;
class Game{
public:
    Game();
    virtual ~Game();
    // void setRenderer(std::function<void(void* ptr)> renderFunc) {m_RenderFunc=renderFunc;};
    Scene* currentScene() {return m_pCurrentScene;}
protected:
    bool addScene(Scene* scene);
    int addImage(String strPath);
protected:
    String m_strCurrentSceneName;
    Scene* m_pCurrentScene;
    std::map<String, Scene*> m_SceneList;
    // std::function<void(void* ptr)> m_RenderFunc;
};
}
#endif // __NEGAME_H__