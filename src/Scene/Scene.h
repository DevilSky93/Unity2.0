#pragma once

#include "../ResourceManagement/Skybox.h"
#include "../ResourceManagement/ResourceManager.h"
#include "Camera.h"
#include "Transform.h"
#include "../Iterator/EntityIterator.h"
#include "../Iterator/EntityConstIterator.h"
#include "../Entity/System/System.h"

#include <nlohmann/json.hpp>
#include <filesystem>

class Renderer;
class Animator;
class ShapeRenderer;
class PointLight;
class DirectionalLight;

class Scene
{
public:
	Scene(std::string name = "Untitled Scene");
	~Scene();
	
	void onUpdate();
	void onPreRender(RenderContext& context);
	
	Entity& createEntity(Transform& parent);
	EntityIterator removeEntity(EntityIterator where);
	
	EntityIterator entities_begin();
	EntityIterator entities_end();
	EntityConstIterator entities_cbegin() const;
	EntityConstIterator entities_cend() const;
	
	Transform& getRoot();
	
	Skybox* getSkybox();
	void setSkybox(Skybox* skybox);
	
	ResourceManager& getRM();
	
	static void load(const std::filesystem::path& path);
	void save(const std::filesystem::path& path);
	
	const std::string& getName() const;

private:
	std::unique_ptr<Transform> _root;
	std::list<std::unique_ptr<Entity>> _entities;
	std::string _name;
	Skybox* _skybox = nullptr;
	ResourceManager _resourceManager;
	
	System<Animator> _animators;
	System<ShapeRenderer> _shapeRenderers;
	System<PointLight> _pointLights;
	System<DirectionalLight> _directionalLights;
	
	static void deserializeEntity(const nlohmann::ordered_json& json, Transform& parent, int version, Scene& scene);
	nlohmann::ordered_json serializeEntity(const Entity& entity) const;
};
