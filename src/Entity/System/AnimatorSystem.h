#pragma once

#include "System.h"
#include "../Component/Animator.h"

class AnimatorSystem : public System<Animator>
{
protected:
	void onUpdate(Animator &component) override;
	void onDrawUI(Animator &component) override;
};
