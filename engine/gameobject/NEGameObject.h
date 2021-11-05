#ifndef __NEGAMEOBJECT_H__
#define __NEGAMEOBJECT_H__
#include "export.h"
#include "NEVector.h"
#include "NEString.h"
#include <map>
#include <set>
#include <functional>

namespace NeapuEngine {
class Camara;
class NEAPU_ENGINE_EXPORT GameObject{
public:
    GameObject(String strName, GameObject* pParent = nullptr);
    virtual ~GameObject();

    Vector2 position() {return m_vPosition;}
    Vector2 size() {return m_vSize;}
    String name() { return m_strName; }
    GameObject* child(const String& name) { return m_ChildrenList[name]; }
    void setVelocity(const Vector2& vel) {m_vVelocity=vel;}
    void setVelocityX(float s) {m_vVelocity.x = s;}
    void setVelocityY(float s) {m_vVelocity.y = s;}
    int layer() { return m_nLayer; }
    void setLayer(int nLayer) { m_nLayer = nLayer; }
    using RenderFunc = std::function<void(GameObject* pGameObject, Camara* pCamara, void* ptr)>;
    void onRender(RenderFunc rf, void* ptr);
protected:
    virtual void tick();
    virtual void fixedTick();

    void addChild(GameObject* pChild);
    void removeChild(GameObject* pChild);
    // bool isKeyDown(unsigned long keyCode);

protected:
    String m_strName;
    Vector2 m_vPosition;//左上角位置
    Vector2 m_vSize;//宽高
    Vector2 m_vVelocity;//速度
    GameObject* m_pParent;
    std::map<String, GameObject*> m_ChildrenList;
    int m_nLayer;//组内分层

    using GameObjectList = std::set<GameObject*>;
    std::map<int, GameObjectList> m_ChildLayers;
};
}
#endif // __NEGAMEOBJECT_H__