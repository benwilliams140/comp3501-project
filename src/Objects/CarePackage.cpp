#include "Objects/CarePackage.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

#include "Control/game.h"

namespace game {
	using namespace Math;

	CarePackage::CarePackage(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		Game::GetInstance().AddCarePackage(this);
		
		parachute_ = Game::GetInstance().CreateInstance<SceneNode>("Parachute", "Parachute", "Lighting", "ParachuteTexture");
		parachute_->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		parachute_->SetParent(this);

		state_ = PackageState::FALLING;

	}

	CarePackage::~CarePackage() {
		Game::GetInstance().RemoveCarePackage(this);
		Game::GetInstance().RemoveInstance(parachute_);
		Game::GetInstance().RemoveInstance(this);
	}

	void CarePackage::Update(void) {
		static float fallVel = -7.5f;
		glm::vec3 hitPoint;

		switch (state_) {
		case PackageState::FALLING: 
			// Make parachute sway back and forth on the y axis 
			parachute_->Rotate(glm::angleAxis(glm::pi<float>()/2.0f * glm::sin(Time::GetElapsedTime() * 10.0f) * Time::GetDeltaTime(), glm::vec3(0.0f, 1.0f, 0.0f)));
			// Translate care package down with the force of gravity
			Translate(glm::vec3(0.0f, fallVel, 0.0f) * Time::GetDeltaTime());
			// Check for terrain collision detection
			if (Game::GetInstance().GetTerrain()->Collision(GetPosition(), 2.0f, hitPoint)) {
				hitPoint.y += 1.0f;
				if (GetPosition().y <= hitPoint.y) {
					SetPosition(hitPoint);
					state_ = PackageState::GROUNDED;
					landingTime_ = Time::GetElapsedTime();
				}
			}
			break;
		case PackageState::GROUNDED:
			if (parachute_->GetActive()) {
				// Make parachute continue to fall
				parachute_->Translate(glm::vec3(0.0f, fallVel, 0.0f) * Time::GetDeltaTime());
				// Check how much time elapsed since landing, and deactivate parachute after 3 seconds
				if (Time::GetElapsedTime() - landingTime_ >= 4.0f) {
					parachute_->SetActive(false);
				}
			}
			break;
		}
	}

	void CarePackage::Open()
	{
		storedAbility_->SetActive(true);
		Game::GetInstance().GetPlayer()->GetTank()->GetTurret()->AddAbility(storedAbility_);
	}

	void CarePackage::SetStoredAbility(Ability* ability)
	{
		storedAbility_ = ability;
	}

	SphereCollider CarePackage::GetCollider(void) const {
		return {GetPosition(), 1.5f};
	}
}