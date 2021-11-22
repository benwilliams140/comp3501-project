#include "Objects/Hovertank/scanner.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <control/game.h>

namespace game {

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
			// Start scanning
			if (Input::getKeyDown(INPUT_KEY_C)) {
				std::vector<Artifact*> artifacts = Game::GetInstance().GetArtifacts();
				
				for (auto itr = artifacts.begin(); itr != artifacts.end(); itr++) {
					// Check if the artifact is less than 10 meters away from scanner
					if (glm::distance(GetParent()->GetParent()->GetPosition(), (*itr)->GetPosition()) < 15.0f) {
						// Check for cube vs. cube collision
						if (true) { //(Math::collision(A, B)) { // TODO - check for collision
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
		}
	}

	bool Scanner::IsScanning() const {
		return scanning_;
	}

} // namespace game