#include "NEGameObject.h"
using namespace NeapuEngine;

GameObject::GameObject(String strName, GameObject* pParent)
	: m_strName(strName)
	, m_nLayer(0)
	, m_pParent(pParent)
{
	if (pParent) {
		pParent->addChild(this);
	}
}

NeapuEngine::GameObject::~GameObject()
{
	for (auto i : m_ChildrenList) {
		delete i.second;
	}
}

void GameObject::onRender(RenderFunc rf, void* ptr) 
{
	rf(this, ptr);
	for (auto& item : m_ChildLayers) {
		for (auto child : item.second) {
			child->onRender(rf, ptr);
		}
	}
}

void GameObject::tick() 
{
	for(auto item: m_ChildrenList){
		item.second->tick();
	}
}

void GameObject::fixedTick() 
{
	if(!m_vVelocity.isEmpty()){
		Vector2 vVelocityTick = m_vVelocity/50;
		m_vPosition = m_vPosition + vVelocityTick;
	}
	
	for(auto item: m_ChildrenList){
		item.second->fixedTick();
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

