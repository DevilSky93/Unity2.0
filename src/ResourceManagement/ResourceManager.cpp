#include "ResourceManager.h"
#include "../Logging/Logger.h"
#include "../Window.h"
#include "../Engine.h"
#include <fmt/format.h>
#include <GLFW/glfw3.h>

ResourceManager::ResourceManager(int threadCount):
_threadPool(threadCount, Engine::getWindow().getHandle())
{

}

Model* ResourceManager::requestModel(const std::string& name)
{
	if (!_models.contains(name))
	{
		_models[name] = std::make_unique<Model>(name);
		
		Model* model = _models[name].get();
		
		_threadPool.push_task([](Model* model)
		{
			Logger::info(fmt::format("Loading model \"{}\"", model->getName()));
			model->loadResource();
			Logger::info(fmt::format("Model \"{}\" loaded", model->getName()));
		}, model);
	}
	
	return _models[name].get();
}

Image* ResourceManager::requestImage(const std::string& name, ImageType type)
{
	if (!_images.contains(name))
	{
		_images[name] = std::make_unique<Image>(name);
		
		Image* image = _images[name].get();
		
		_threadPool.push_task([](Image* image, ImageType type)
		{
			Logger::info(fmt::format("Loading image \"{}\"", image->getName()));
			image->loadResource(type);
			Logger::info(fmt::format("Image \"{}\" loaded", image->getName()));
		}, image, type);
	}
	
	return _images[name].get();
}

Skybox* ResourceManager::requestSkybox(const std::string& name)
{
	if (!_skyboxes.contains(name))
	{
		_skyboxes[name] = std::make_unique<Skybox>(name);
		
		Skybox* skybox = _skyboxes[name].get();
		
		_threadPool.push_task([](Skybox* skybox)
		{
			Logger::info(fmt::format("Loading skybox \"{}\"", skybox->getName()));
			skybox->loadResource();
			Logger::info(fmt::format("Skybox \"{}\" loaded", skybox->getName()));
		}, skybox);
	}
	
	return _skyboxes[name].get();
}

ShaderProgram* ResourceManager::requestShaderProgram(const ShaderProgramCreateInfo& createInfo)
{
	if (!_shaderPrograms.contains(createInfo))
	{
		Logger::info("Loading shader program");
		_shaderPrograms[createInfo] = std::make_unique<ShaderProgram>(createInfo);
		Logger::info(fmt::format("Shader program loaded (id: {})", _shaderPrograms[createInfo]->getHandle()));
	}
	
	return _shaderPrograms[createInfo].get();
}

Material* ResourceManager::requestMaterial(const std::string& name)
{
	if (!_materials.contains(name))
	{
		_materials[name] = std::unique_ptr<Material>(new Material(name, this));
	}
	
	return _materials[name].get();
}
