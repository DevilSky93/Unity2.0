#pragma once

#include "System.h"
#include "../Component/ShapeRenderer.h"

class ShapeRendererSystem : public System<ShapeRenderer>
{
protected:
	void onRender(ShapeRenderer &component, RenderContext &context) override;
	void onDrawUI(ShapeRenderer &component) override;
};
