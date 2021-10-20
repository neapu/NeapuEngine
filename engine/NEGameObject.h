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
    
    GameObject(String name, int nLayer = 0, GameObject* parent = nullptr);
    virtual ~GameObject();

    Vector2 position() {return m_vPosition;}
    Vector2 size() {return m_vSize;}
    String name() { return m_strName; }
    GameObject* child(const String& name) { return m_ChildrenList[name]; }
    int layer() { return m_nLayer; }
    virtual void render(ID2D1HwndRenderTarget* pRenderTarget, const Camara* camara, std::map<int, Image*>& imageList);
protected:
    void addChild(GameObject* pChild);
    void removeChild(GameObject* pChild);

protected:
    String m_strName;
    Vector2 m_vPosition;//左上角位置
    Vector2 m_vSize;//宽高
    GameObject* m_pParent;
    std::map<String, GameObject*> m_ChildrenList;
    int m_nLayer;//组内分层

    using GameObjectList = std::set<GameObject*>;
    std::map<int, GameObjectList> m_ChildLayers;
};
}
#endif // __NEGAMEOBJECT_H__