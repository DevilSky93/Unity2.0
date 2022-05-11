#include "PointLightSystem.h"
#include "../../Scene/Camera.h"
#include "../../Rendering/Renderer/Renderer.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/integer.hpp>

void PointLightSystem::onRender(PointLight& component, RenderContext& context)
{
	PointLight::RenderData data{};
	data.pos = component.getTransform().getWorldPosition();
	data.intensity = component.getIntensity();
	data.color = component.getLinearColor();
	data.radius = component.getRadius();
	data.castShadows = component._castShadows;
	if (component._castShadows)
	{
		data.viewProjections[0] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0));
		data.viewProjections[1] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0));
		data.viewProjections[2] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
		data.viewProjections[3] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1));
		data.viewProjections[4] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
		data.viewProjections[5] = PointLight::_projection *
								  glm::lookAt(data.pos, data.pos + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
		data.shadowMapTexture = component._shadowMap.get();
		data.shadowMapFramebuffer = component._shadowMapFb.get();
		data.mapResolution = component.getResolution();
		data.far = PointLight::FAR_DISTANCE;
	}
	
	context.renderer.requestLightRendering(data);
}

void PointLightSystem::onDrawUI(PointLight& component)
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
	
	float radius = component.getRadius();
	if (ImGui::SliderFloat("Radius", &radius, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
	{
		component.setRadius(radius);
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
