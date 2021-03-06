#include "Engine.h"
#include "Helper/GlfwHelper.h"
#include <stdexcept>
#include "UI/UIHelper.h"
#include "GLObject/Framebuffer.h"
#include "Logging/Logger.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "ResourceManagement/ResourceManager.h"
#include "Scene/Scene.h"
#include "Entity/Component/ShapeRenderer.h"
#include "Helper/RenderHelper.h"
#include <fmt/format.h>
#include "Entity/Entity.h"
#include "UI/Window/UIViewport.h"
#include "UI/Window/UIInspector.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

std::unique_ptr<Window> Engine::_window;
std::unique_ptr<ResourceManager> Engine::_globalResourceManager;
std::unique_ptr<Scene> Engine::_scene;

Timer Engine::_timer;

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			Logger::error(message, "OPGL");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			Logger::warning(message, "OPGL");
			break;
		case GL_DEBUG_SEVERITY_LOW:
			Logger::info(message, "OPGL");
			break;
	}
}

void Engine::init()
{
	GlfwHelper::Init();
	
	stbi_set_flip_vertically_on_load(true);
	stbi_flip_vertically_on_write(true);
	
//	Logger::SetLogLevel(Logger::LogLevel::Warning);
	
	_window = std::make_unique<Window>();
	
	_globalResourceManager = std::make_unique<ResourceManager>(1);
	
	Logger::info(fmt::format("GLFW Version: {}", glfwGetVersionString()), "GLFW");
	Logger::info(fmt::format("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION))), "OPGL");
	Logger::info(fmt::format("GPU: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))), "OPGL");
	
	glEnable(GL_DEBUG_OUTPUT);
#if defined(_DEBUG)
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
	glDebugMessageCallback(messageCallback, nullptr);
	
	Material::initialize();
	Framebuffer::initDrawToDefault();
	RenderHelper::initDrawScreenQuad();
	Entity::initAllocators();
	ShapeRenderer::initAllocators();
	UIViewport::initAllocators();
	
	_scene = std::make_unique<Scene>();
	
	UIHelper::init();
}

void Engine::run()
{
	while (!_window->shouldClose())
	{
		glfwPollEvents();
		
		_timer.onNewFrame();
		UIHelper::onNewFrame();
		
		_scene->onUpdate();
		
		UIHelper::render();
		
		_window->swapBuffers();
	}
}

void Engine::shutdown()
{
	UIHelper::shutdown();
	_scene.reset();
	_globalResourceManager.reset();
	_window.reset();
	glfwTerminate();
}

Window& Engine::getWindow()
{
	return *_window;
}

ResourceManager& Engine::getGlobalRM()
{
	return *_globalResourceManager;
}

Scene& Engine::getScene()
{
	return *_scene;
}

void Engine::setScene(std::unique_ptr<Scene>&& scene)
{
	UIInspector::setSelected(std::any());
	_scene = std::move(scene);
}

Timer& Engine::getTimer()
{
	return _timer;
}
