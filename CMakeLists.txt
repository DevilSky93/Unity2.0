cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(Unity2)

add_executable(Unity2 vendor/imguizmo-f7bbbe3/src/ImCurveEdit.cpp vendor/imguizmo-f7bbbe3/src/ImGradient.cpp vendor/imguizmo-f7bbbe3/src/ImGuizmo.cpp vendor/imguizmo-f7bbbe3/src/ImSequencer.cpp vendor/glad/src/glad.c vendor/imgui/include/imgui.cpp vendor/imgui/include/imgui_demo.cpp vendor/imgui/include/imgui_draw.cpp vendor/imgui/include/imgui_stdlib.cpp vendor/imgui/include/imgui_tables.cpp vendor/imgui/include/imgui_widgets.cpp src/Main.cpp src/Engine.cpp src/Engine.h src/Logging/Logger.cpp src/Logging/Logger.h src/Window.cpp src/Window.h src/Helper/FileHelper.cpp src/Helper/FileHelper.h src/Helper/GlfwHelper.cpp src/Helper/GlfwHelper.h src/GLObject/BufferBase.cpp src/GLObject/BufferBase.h src/GLObject/ShaderProgram.cpp src/GLObject/ShaderProgram.h src/Helper/ShaderHelper.cpp src/Helper/ShaderHelper.h src/Helper/StringHelper.cpp src/Helper/StringHelper.h src/Exception/OpenGLException.h src/GLObject/Buffer.h src/GLObject/ShaderStorageBuffer.h src/GLObject/Texture.cpp src/GLObject/Texture.h src/GLObject/CreateInfo/TextureCreateInfo.h src/GLObject/Mesh.cpp src/GLObject/Mesh.h src/GLObject/VertexArray.h src/ResourceManagement/Model.cpp src/ResourceManagement/Model.h src/ResourceManagement/Resource.h src/ResourceManagement/ResourceManager.cpp src/ResourceManagement/ResourceManager.h src/ResourceManagement/Image.cpp src/ResourceManagement/Image.h src/Helper/TextureHelper.cpp src/Helper/TextureHelper.h src/GLObject/ShaderProgram_setUniform.cpp src/GLObject/Framebuffer.cpp src/GLObject/Framebuffer.h src/GLObject/Cubemap.cpp src/GLObject/Cubemap.h src/GLObject/CreateInfo/CubemapCreateInfo.h src/Helper/MathHelper.cpp src/Helper/MathHelper.h src/Scene/Transform.cpp src/Scene/Transform.h src/Helper/VectorHelper.h src/GLObject/Material/Material.cpp src/GLObject/Material/Material.h src/GLObject/CreateInfo/ShaderProgramCreateInfo.h src/GLObject/Material/MaterialMapDefinition.h src/Helper/JsonHelper.cpp src/Helper/JsonHelper.h src/ResourceManagement/Skybox.cpp src/ResourceManagement/Skybox.h src/stdfloat.h src/Scene/Scene.cpp src/Scene/Scene.h src/Scene/Camera.cpp src/Scene/Camera.h src/UI/UIHelper.cpp src/UI/UIHelper.h src/UI/Impl/imgui_impl_glfw.cpp src/UI/Impl/imgui_impl_glfw.h src/UI/Impl/imgui_impl_opengl3.cpp src/UI/Impl/imgui_impl_opengl3.h src/UI/Impl/imgui_impl_opengl3_loader.h src/UI/Window/UIMisc.cpp src/UI/Window/UIMisc.h src/Rendering/Renderer/RasterizationRenderer.cpp src/Rendering/Renderer/RasterizationRenderer.h src/Helper/RenderHelper.cpp src/Helper/RenderHelper.h src/Rendering/PostProcessingEffect/PostProcessingEffect.h src/Rendering/PostProcessingEffect/ToneMappingEffect.cpp src/Rendering/PostProcessingEffect/ToneMappingEffect.h src/UI/Window/UIHierarchy.cpp src/UI/Window/UIHierarchy.h src/UI/Window/UIInspector.cpp src/UI/Window/UIInspector.h src/UI/Window/UIResourceExplorer.cpp src/UI/Window/UIResourceExplorer.h src/Enums/ResourceType.h src/ResourceManagement/StbImage.cpp src/ResourceManagement/StbImage.h src/Rendering/Pass/RenderPass.cpp src/Rendering/Pass/RenderPass.h src/Rendering/Pass/GeometryPass.cpp src/Rendering/Pass/GeometryPass.h src/Rendering/Pass/ShadowMapPass.cpp src/Rendering/Pass/ShadowMapPass.h src/Rendering/RenderRegistry.h src/Rendering/Pass/LightingPass.cpp src/Rendering/Pass/LightingPass.h src/Rendering/Pass/PostProcessingPass.cpp src/Rendering/Pass/PostProcessingPass.h src/Rendering/Pass/SkyboxPass.cpp src/Rendering/Pass/SkyboxPass.h src/Enums/ImageType.h src/Rendering/Pass/ZPrePass.cpp src/Rendering/Pass/ZPrePass.h src/Rendering/Pass/GBufferDebugPass.cpp src/Rendering/Pass/GBufferDebugPass.h src/Timer.cpp src/Timer.h src/GLObject/CreateInfo/SamplerCreateInfo.h src/GLObject/Sampler.cpp src/GLObject/Sampler.h src/Rendering/PostProcessingEffect/ExposureEffect.cpp src/Rendering/PostProcessingEffect/ExposureEffect.h src/Rendering/PostProcessingEffect/BloomEffect.cpp src/Rendering/PostProcessingEffect/BloomEffect.h src/Rendering/PostProcessingEffect/PostProcessingEffect.cpp src/Entity/Entity.cpp src/Entity/Entity.h src/Entity/Component/Component.h src/Iterator/ComponentIterator.h src/Iterator/ComponentConstIterator.h src/Entity/Component/Component.cpp src/Entity/Component/ShapeRenderer.cpp src/Entity/Component/ShapeRenderer.h src/Entity/Component/Animator.cpp src/Entity/Component/Animator.h src/Entity/Component/LightBase.cpp src/Entity/Component/LightBase.h src/Entity/Component/PointLight.cpp src/Entity/Component/PointLight.h src/Entity/Component/DirectionalLight.cpp src/Entity/Component/DirectionalLight.h src/Iterator/ComponentIterator.cpp src/Iterator/ComponentConstIterator.cpp src/Iterator/EntityConstIterator.cpp src/Iterator/EntityConstIterator.h src/Iterator/EntityIterator.cpp src/Iterator/EntityIterator.h src/Event.h src/UI/Window/UIMenuBar.cpp src/UI/Window/UIMenuBar.h src/UI/Window/UIViewport.cpp src/UI/Window/UIViewport.h src/RenderContext.h src/Helper/ThreadHelper.cpp src/Helper/ThreadHelper.h src/ObjectSerialization.h src/ObjectSerialization.cpp  src/Rendering/Shape/Shape.cpp src/Rendering/Shape/Shape.h src/Rendering/Shape/MeshShape.cpp src/Rendering/Shape/MeshShape.h src/Rendering/Shape/SphereShape.cpp src/Rendering/Shape/SphereShape.h src/Rendering/Renderer/RaytracingRenderer.cpp src/Rendering/Renderer/RaytracingRenderer.h src/Rendering/Renderer/Renderer.cpp src/Rendering/Renderer/Renderer.h src/Rendering/Pass/RaytracePass.cpp src/Rendering/Pass/RaytracePass.h src/Rendering/Shape/PlaneShape.cpp src/Rendering/Shape/PlaneShape.h src/GLObject/Material/MaterialMap.h src/GLObject/Material/MaterialMapType.h src/PerfCounter/PerfStep.h src/PerfCounter/GpuPerfCounter.cpp src/PerfCounter/GpuPerfCounter.h src/Logging/Impl/ILoggerColor.h src/Logging/Impl/Win32LoggerColor.cpp src/Logging/Impl/Win32LoggerColor.h src/Logging/LogColorFlags.h)

set_property(TARGET Unity2 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(Unity2 PRIVATE /Zc:__cplusplus)
target_compile_features(Unity2 PRIVATE cxx_std_20)

find_path(STB_INCLUDE_DIRS "stb.h")
target_include_directories(Unity2 PRIVATE ${STB_INCLUDE_DIRS})

find_package(assimp CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE assimp::assimp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE fmt::fmt)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE glm::glm)

find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE magic_enum::magic_enum)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Unity2 PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Unity2 PRIVATE
    "vendor/glad/include"
	"vendor/imgui/include"
	"vendor/thread-pool/include"
	"vendor/concurrentqueue/include"
	"vendor/imguizmo-f7bbbe3/include")

add_custom_command(TARGET Unity2 PRE_BUILD
		COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")