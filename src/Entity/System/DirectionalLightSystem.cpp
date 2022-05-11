#include "DirectionalLightSystem.h"
#include "../../Scene/Camera.h"
#include "../../Rendering/Renderer/Renderer.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/integer.hpp>

void DirectionalLightSystem::onRender(DirectionalLight& component, RenderContext& context)
{
	DirectionalLight::RenderData data{};
	data.fragToLightDirection = -component.getLightDirection();
	data.intensity = component.getIntensity();
	data.color = component.getLinearColor();
	data.angularDiameter = component.getAngularDiameter();
	data.castShadows = component._castShadows;
	if (component._castShadows)
	{
		data.lightViewProjection = DirectionalLight::_projection *
								   glm::lookAt(
									   context.camera.getPosition(),
									   context.camera.getPosition() + component.getLightDirection(),
									   glm::vec3(0, 1, 0));
		data.shadowMapTexture = component._shadowMap.get();
		data.shadowMapFramebuffer = component._shadowMapFb.get();
		data.mapResolution = component.getResolution();
		data.mapSize = component._mapSize;
		data.mapDepth = component._mapDepth;
	}
	
	context.renderer.requestLightRendering(data);
}

void DirectionalLightSystem::onDrawUI(DirectionalLight& component)
{
	glm::vec3 imGuiSrgbColor = component.getSrgbColor();
	if (ImGui::ColorEdit3("Color", glm::value_ptr(imGuiSrgbColor)))
	{
		component.setSrgbColor(imGuiSrgbColor);
	}
	
	float intensity = component.getIntensity();
	if (ImGui::DragFloat("Intensity", &intensity, 0.01f))
	{
		component.setIntensity(intensity);
	}
	
	float angularDiameter = component.getAngularDiameter();
	if (ImGui::SliderFloat("Angular Diameter", &angularDiameter, 0.0f, 10.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
	{
		component.setAngularDiameter(angularDiameter);
	}
	
	bool castShadows = component.getCastShadows();
	if (ImGui::Checkbox("Cast Shadows", &castShadows))
	{
		component.setCastShadows(castShadows);
	}
	
	std::array<const char*, 8> resolutions = {"64", "128", "256", "512", "1024", "2048", "4096", "8192"};
	int currIndex = glm::log2(component.getResolution() / 64);
	if (ImGui::BeginCombo("Shadow Resolution", resolutions[currIndex]))
	{
		for (int i = 0; i < resolutions.size(); i++)
		{
			bool selected = i == currIndex;
			if (ImGui::Selectable(resolutions[i], selected))
			{
				currIndex = i;
				component.setResolution(64 * glm::pow(2, i));
			}
			
			if (selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		
		ImGui::EndCombo();
	}
}
