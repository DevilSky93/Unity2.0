#pragma once

#include "System.h"
#include "../Component/PointLight.h"

class PointLightSystem : public System<PointLight>
{
protected:
	void onRender(PointLight &component, RenderContext &context) override;
	void onDrawUI(PointLight &component) override;
};