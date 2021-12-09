#include "Objects/Hovertank/scanner.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <control/game.h>
#include "Control/mathematics.h"

namespace game {
	using namespace Math;

	Scanner::Scanner(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		// Initialize the scan cone effect
		scanCone_ = Game::GetInstance().CreateInstance<SceneNode>("Scan Cone", HOVERTANK_SCANNER_CONE, "Simple", "uv6");
		scanCone_->SetParent(this);
		scanCone_->SetActive(false);
		
		artifact_ = nullptr;
		scanning_ = false;
	}

	Scanner::~Scanner() {}

	void Scanner::Update(void) {
		if (scanning_) {
			static float scanMaxTime = 2.0f;
			float scanDeltaTime = Time::GetElapsedTime() - scanStartTime_;
			float rot_factor = 20.0f * Time::GetDeltaTime();

			// Update scanning animation
			if (scanDeltaTime < (scanMaxTime/2.0f)) {
				Rotate(glm::angleAxis(glm::radians(rot_factor), glm::vec3(1,0,0)));
			} else if (scanDeltaTime < scanMaxTime) {
				Rotate(glm::angleAxis(glm::radians(-rot_factor), glm::vec3(1,0,0)));
			} else {
				// Inform player of artifact discovered
				Game::GetInstance().GetPlayer()->DiscoveredArtifact(artifact_);
				// Stop scanning
				scanCone_->SetActive(false);
				scanning_ = false;
			}
		} else {
			// Checks for any artifacts nearby
			std::vector<Artifact*> artifacts = Game::GetInstance().GetArtifacts();
				
			for (auto itr = artifacts.begin(); itr != artifacts.end(); itr++) {
				// Check if the artifact is less than 10 meters away from scanner
				if (glm::distance(GetParent()->GetParent()->GetPosition(), (*itr)->GetPosition()) < 10.0f) {
					// Check for point vs. cube collision
					if (isCollidingSphereToSphere({GetScanPoint(), 0.5F}, (*itr)->GetCollider())) {
						// Activate button prompt
						((HUD*)Game::GetInstance().GetMenu(MenuType::HUD))->ActivateTooltip("[C] Scan Object", 0.25f);
						
						// Start scanning
						if (Input::getKeyDown(INPUT_KEY_C)) {
							// Record artifact discovered
							artifact_ = (*itr);
							// Start scanning animation
							scanning_ = true;
							scanStartTime_ = Time::GetElapsedTime();
							scanCone_->SetActive(true);
						}
					}
				}
			}

			// Checks for any care packages nearby
			std::vector<CarePackage*> carePackages = Game::GetInstance().GetCarePackages();

			for (auto itr = carePackages.begin(); itr != carePackages.end(); itr++) {
				// Check if the care packages is less than 10 meters away from scanner
				if (glm::distance(GetParent()->GetParent()->GetPosition(), (*itr)->GetPosition()) < 10.0f) {
					// Check for point vs. cube collision
					if (isCollidingSphereToSphere({GetScanPoint(), 0.5F}, (*itr)->GetCollider())) {
						// Activate button prompt
						((HUD*)Game::GetInstance().GetMenu(MenuType::HUD))->ActivateTooltip("[C] open care package", 0.25f);
						
						// Start scanning
						if (Input::getKeyDown(INPUT_KEY_C)) {
							// TODO - action of picking up care package
							(*itr)->Open();
							delete* itr;
						}
					}
				}
			}
		}
	}

	bool Scanner::IsScanning(void) const {
		return scanning_;
	}

	Point3 Scanner::GetScanPoint(void) const {
		Vector4 P = GetWorldTransform() * glm::vec4(GetPosition() + glm::vec3(0.0f, -2.0f, 2.5f), 1.0f);
		return Point3(P.x, P.y, P.z);
	}

} // namespace game