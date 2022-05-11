#include "AnimatorSystem.h"
#include "../../Engine.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

void AnimatorSystem::onUpdate(Animator& component)
{
	double deltaTime = Engine::getTimer().deltaTime();
	
	Transform& transform = component.getTransform();
	
	glm::vec3 velocity = transform.localToParentDirection(component.getVelocity());
	
	transform.setLocalPosition(transform.getLocalPosition() + velocity * (float) deltaTime);
	
	glm::vec3 rotationOffset = component.getAngularVelocity() * (float)deltaTime;
	
	glm::quat rotation = transform.getLocalRotation();
	rotation = glm::rotate(rotation, glm::radians(rotationOffset.x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(rotationOffset.y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(rotationOffset.z), glm::vec3(0, 0, 1));
	transform.setLocalRotation(rotation);
}

void AnimatorSystem::onDrawUI(Animator& component)
{
	glm::vec3 velocity = component.getVelocity();
	if (ImGui::DragFloat3("Velocity", glm::value_ptr(velocity), 0.01f))
	{
		component.setVelocity(velocity);
	}
	
	glm::vec3 angularVelocity = component.getAngularVelocity();
	if (ImGui::DragFloat3("Angular Velocity", glm::value_ptr(angularVelocity), 0.01f))
	{
		component.setAngularVelocity(angularVelocity);
	}
}
