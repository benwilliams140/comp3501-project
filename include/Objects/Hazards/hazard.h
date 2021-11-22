#pragma once

#include "Control/scene_node.h"
#include "Control/time.h"

namespace game {
class Hazard : public SceneNode {
public:
	Hazard(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
	~Hazard();

	void SetEffectiveness(float effectiveness);

protected:
	float effectiveness = 1.0f; // should always start at 1.0, until the hovertank is upgraded

	virtual void Effect() = 0; // base hazard should not have an effect
}; // Hazard class
} // namespace game