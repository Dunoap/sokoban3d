#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <core/Logger.h>

#include <core/ModelLoader.h>
#include <core/TextureLoader.h>
#include <core/AnimationLoader.h>

#include <core/Resource.h>
#include <core/resources/Texture.h>
#include <core/resources/Model.h>
#include <core/resources/BaseAnimation.h>

enum resourceType {
	ALL = 0,
	TEXTURE,
	MESH
};

class ResourceManager {
public:
	ResourceManager();

	~ResourceManager();

    template <class Resource>
    static Resource* add(std::string);
        
    static Model* getModel(std::string);
	static Texture* getTexture(std::string);
	static BaseAnimation* getAnimation(std::string);
        
        
	static bool remove(resourceType r, std::string id);
	static bool empty(resourceType r);
private:
	static std::map<std::string, Texture*> m_textureList;
	static std::map<std::string, Model*> m_modelList;
	static std::map<std::string, BaseAnimation*> m_animationList;
        
	static ModelLoader m_modelLoader;
	static TextureLoader m_textureLoader;
	static AnimationLoader m_animationLoader;
};

template <> 
inline Model* ResourceManager::add<Model>(std::string path)
{
	if(m_modelList.find(path) != m_modelList.end()) { 
		return m_modelList[path];
	}
	Model* m = m_modelLoader.load(path);
    m_modelList[path] = m;
	return m_modelList[path];
}

template <>
inline BaseAnimation* ResourceManager::add<BaseAnimation>(std::string path)
{
	if(m_animationList.find(path) != m_animationList.end()) { 
		return m_animationList[path];
	}
	BaseAnimation* t = m_animationLoader.load(path);
	m_animationList[path] = t;
	return m_animationList[path];
}

template <>
inline Texture* ResourceManager::add<Texture>(std::string path)
{
	if(m_textureList.find(path) != m_textureList.end()) { 
		return m_textureList[path];
	}
	Texture* t = m_textureLoader.load(path);
	m_textureList[path] = t;
	return m_textureList[path];
}

#endif
