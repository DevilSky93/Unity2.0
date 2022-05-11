#pragma once

#include "System.h"
#include "../Component/DirectionalLight.h"

class DirectionalLightSystem : public System<DirectionalLight>
{
protected:
	void onRender(DirectionalLight &component, RenderContext &context) override;
	void onDrawUI(DirectionalLight &component) override;
};
