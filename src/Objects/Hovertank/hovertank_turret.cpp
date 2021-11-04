#include "Objects/Hovertank/hovertank_turret.h"
#include <Objects/Projectiles/linear_projectile.h>

namespace game {

	HoverTankTurret::HoverTankTurret(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		selectedAbility_ = availableAbilities_.end();
	}


	HoverTankTurret::~HoverTankTurret() {
	}


	void HoverTankTurret::Update(void) {
		Rotate(this->GetAngM());
	}

	void HoverTankTurret::UseSelectedAbility(Projectile** outProj, glm::vec3 forward, Resource* geometry, Resource* material, Resource* texture) {
		if (selectedAbility_ == availableAbilities_.end()) return; // no selected ability (probably because none are added)

		(*selectedAbility_)->UseAbility(outProj, forward, geometry, material, texture);
	}

	void HoverTankTurret::SelectNextAbility() {
		// increase the vector iterator, wrapping to the beginning if needed
		if (++selectedAbility_ == availableAbilities_.end()) {
			selectedAbility_ = availableAbilities_.begin();
		}
	}

	void HoverTankTurret::SelectPreviousAbility() {
		// decrease the vector iterator, wrapping to the end if needed
		if (selectedAbility_-- == availableAbilities_.begin()) {
			selectedAbility_ = availableAbilities_.end() - 1;
		}
	}
	
	bool HoverTankTurret::AddAbility(Ability* ability) {
		if (availableAbilities_.size() >= abilityInventorySize_) return false;
		else {
			availableAbilities_.push_back(ability);
			// select the newly added ability
			selectedAbility_ = std::find(availableAbilities_.begin(), availableAbilities_.end(), ability);
			return true;
		}
	}

	std::vector<Projectile*> HoverTankTurret::RemoveDeadProjectiles() {
		std::vector<Projectile*> projectilesToRemove;
		for (auto it = availableAbilities_.begin(); it != availableAbilities_.end(); ++it) {
			std::vector<Projectile*> temp = (*it)->RemoveDeadProjectiles();
			projectilesToRemove.insert(projectilesToRemove.end(), temp.begin(), temp.end());
		}
		return projectilesToRemove;
	}

	void HoverTankTurret::SetForward(glm::vec3 forward) {
		forward_ = forward;
	}

	glm::vec3 HoverTankTurret::GetForward(void) {
		return GetOrientation() * glm::normalize(forward_);
	}

} // namespace game 