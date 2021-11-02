#ifndef __NEGAME_H__
#define __NEGAME_H__

#include "NEString.h"
#include <map>
namespace NeapuEngine {
class Scene;
class Game{
public:
    Game();
    virtual ~Game();
protected:
    void addScene(Scene* scene);
    int addImage(String strPath);
protected:
    String m_strCurrentSceneName;
    Scene* m_pCurrentScene;
    std::map<String, Scene*> m_SceneList;
};
}
#endif // __NEGAME_H__