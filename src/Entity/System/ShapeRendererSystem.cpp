#include "ShapeRendererSystem.h"
#include "../../Engine.h"
#include "../../Scene/Camera.h"
#include "../../Scene/Scene.h"
#include "../../Rendering/Renderer/Renderer.h"
#include <imgui.h>
#include <imgui_stdlib.h>

void ShapeRendererSystem::onRender(ShapeRenderer& component, RenderContext& context)
{
	ShapeRenderer::RenderData data{};
	data.material = component.getDrawingMaterial();
	data.shape = &component.getShape();
	data.owner = &component.getEntity();
	data.contributeShadows = component.getContributeShadows();
	data.matrix = component.getTransform().getLocalToWorldMatrix();
	
	context.renderer.requestShapeRendering(data);
}

void ShapeRendererSystem::onDrawUI(ShapeRenderer& component)
{
	Material* material = component.getDrawingMaterial();
	std::string materialName = material->getName();
	ImGui::InputText("Material", &materialName, ImGuiInputTextFlags_ReadOnly);
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MaterialDragDrop");
		if (payload)
		{
			std::string newMaterialName = *(*static_cast<const std::string**>(payload->Data));
			if (newMaterialName == "internal/Default Material")
			{
				component.setMaterial(Material::getDefault());
			}
			else
			{
				component.setMaterial(Engine::getScene().getRM().requestMaterial(newMaterialName));
			}
		}
		ImGui::EndDragDropTarget();
	}
	
	bool contributeShadows = component.getContributeShadows();
	if (ImGui::Checkbox("Contribute Shadows", &contributeShadows))
	{
		component.setContributeShadows(contributeShadows);
	}
	
	if (ImGui::BeginCombo("Shape", component._selectedShape.c_str()))
	{
		for (auto it = ShapeRenderer::_allocators.begin(); it != ShapeRenderer::_allocators.end(); it++)
		{
			const bool is_selected = (component._selectedShape == it->first);
			if (ImGui::Selectable(it->first.c_str(), is_selected))
			{
				component._selectedShape = it->first;
				component.setShapeByIdentifier(component._selectedShape);
			}
			
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	
	component.getShape().onDrawUi();
}
