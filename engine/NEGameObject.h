#ifndef __NEGAMEOBJECT_H__
#define __NEGAMEOBJECT_H__
#include "export.h"
#include "NEVector.h"
#include "NEString.h"
#include <map>
#include <set>
struct ID2D1HwndRenderTarget;
namespace NeapuEngine {
class Camara;
class Image;
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
protected:
    friend class Scene;
    virtual void render(ID2D1HwndRenderTarget* pRenderTarget, const Camara* camara, std::map<int, Image*>& imageList);
    virtual void tick();
    virtual void fixedTick();

    void addChild(GameObject* pChild);
    void removeChild(GameObject* pChild);
    bool isKeyDown(unsigned long keyCode);

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