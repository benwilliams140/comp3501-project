#pragma once

#include "Objects/Hazards/hazard.h"

namespace game {
class MudPool : public Hazard {
public:
	MudPool(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
	~MudPool();

	virtual void Update() override;

private:
	virtual void Effect() override;
};
} // namespace game