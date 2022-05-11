#pragma once

#include <vector>
#include <unordered_map>
#include "../../GuidContainer.h"
#include "../../RenderContext.h"

template<typename TComponent>
class System
{
public:
	virtual ~System() = default;
	
	void update();
	void render(RenderContext& context);
	void drawUI();
	
protected:
	virtual void onUpdate(TComponent& component) {};
	virtual void onRender(TComponent& component, RenderContext& context) {};
	virtual void onDrawUI(TComponent& component) {};

protected:
	GuidContainer<TComponent> _container;
};

template<typename TComponent>
void System<TComponent>::update()
{
	auto it = _container.begin();
	auto end = _container.end();
	for (;it != end; it++)
	{
		onUpdate(*it);
	}
}

template<typename TComponent>
void System<TComponent>::render(RenderContext& context)
{
	auto it = _container.begin();
	auto end = _container.end();
	for (;it != end; it++)
	{
		onRender(*it, context);
	}
}

template<typename TComponent>
void System<TComponent>::drawUI()
{
	auto it = _container.begin();
	auto end = _container.end();
	for (;it != end; it++)
	{
		onDrawUI(*it);
	}
}
