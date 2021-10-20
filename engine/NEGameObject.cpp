#include "NEGameObject.h"
using namespace NeapuEngine;

GameObject::GameObject(String name, int nLayer, GameObject* parent)
	: m_strName(name)
	, m_nLayer(nLayer)
	, m_pParent(parent)
{
	if (parent) {
		parent->addChild(this);
	}
}

NeapuEngine::GameObject::~GameObject()
{
	for (auto i : m_ChildrenList) {
		delete i.second;
	}
}

void NeapuEngine::GameObject::render(ID2D1HwndRenderTarget* pRenderTarget, const Camara* camara, std::map<int, Image*>& imageList)
{
	for (auto& item : m_ChildLayers) {
		for (auto child : item.second) {
			child->render(pRenderTarget, camara, imageList);
		}
	}
}

void GameObject::addChild(GameObject* pChild)
{
	if (m_ChildrenList.find(pChild->name()) == m_ChildrenList.end()) {
		m_ChildrenList[pChild->name()] = pChild;
		int nLayer = pChild->layer();
		m_ChildLayers[nLayer].insert(pChild);
	}
}

void GameObject::removeChild(GameObject* pChild)
{
	if (m_ChildrenList.find(pChild->name()) != m_ChildrenList.end()) {
		m_ChildrenList.erase(pChild->name());
		int nLayer = pChild->layer();
		m_ChildLayers[nLayer].erase(pChild);
		delete pChild;
	}
}
