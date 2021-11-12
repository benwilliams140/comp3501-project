#pragma once

#include "Control/scene_node.h"
#include "Control/time.h"

namespace game {
class Hazard : public SceneNode {
public:
	Hazard(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
	~Hazard();

protected:
	virtual void Effect() = 0; // base hazard should not have an effect
}; // Hazard class
} // namespace game