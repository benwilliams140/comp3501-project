#include "Objects/Player.h"
#include "Control/game.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <sstream>

namespace game {

	Player::Player(float hitPoints, float ePoints, HoverTank* theTank) {
		health = hitPoints;
		maxHealth = hitPoints;
		energy = ePoints;
		maxEnergy = ePoints;
		tank = theTank;
		money = 0;
		healthRegenCooldown_ = 0.0f;
		energyRegenCooldown_ = 0.0f;
	}


	Player::~Player() {}

	void Player::Update()
	{
		if (startTime_ > 0) {
			startTime_ -= Time::GetDeltaTime();
		} else {
			startTime_ = 0;
		}

		energyRegenCooldown_ -= Time::GetDeltaTime();
		healthRegenCooldown_ -= Time::GetDeltaTime();

		if (energyRegenCooldown_ <= 0.0f) recharge(15.0f * Time::GetDeltaTime());
		if (healthRegenCooldown_ <= 0.0f) repair(15.0f * Time::GetDeltaTime());
	}

	//getters
	float Player::GetHealth(void) {
		return health;
	}

	float Player::GetMaxHealth(void) {
		return maxHealth;
	}

	float Player::GetEnergy(void) {
		return energy;
	}

	float Player::GetMaxEnergy(void) {
		return maxEnergy;
	}

	float Player::GetMoney(void) {
		return money;
	}

	int Player::GetNumArtifacts()
	{
		return artifacts.size();
	}

	HoverTank* Player::GetTank() {
		return tank;
	}

	float Player::GetInjuredStartTime() {
		return startTime_;
	}

	float Player::GetInjuredMaxTime() {
		return maxTime_;
	}

	//setters
	void Player::SetHealth(float newHealth) {
		health = newHealth;
	}

	void Player::SetMaxHealth(float newHealth) {
		maxHealth = newHealth;
	}

	void Player::SetEnergy(float newEnergy) {
		energy = newEnergy;
	}

	void Player::SetMaxEnergy(float newEnergy) {
		maxEnergy = newEnergy;
	}

	bool Player::isAlive() {
		return health > 0;
	}

	
	void Player::decreaseHealth(float damage) {
		//have the player take damage and lose health
		startTime_ = maxTime_;
		health = health - damage;
		healthRegenCooldown_ = maxCooldown_;
		if (health <= 0.0f) {
			Game::GetInstance().SetState(State::GAME_OVER);
		}
	}

	void Player::repair(float gain) {
		//replenish health, and making sure it does not go past the max
		if (maxHealth < health + gain) {
			health = maxHealth;
		}
		else {
			health += gain;
		}
	}

	void Player::energyLost(float lostEnergy) {
		//make the tank the player controls lose energy
		energy = energy - lostEnergy;
		energyRegenCooldown_ = maxCooldown_;
		if (energy < 0) {//make sure it doesn't go below zero
			energy = 0;
		}
	}

	void Player::recharge(float gain) {
		//replenish energy, and making sure ist does not go past the max
		if (maxEnergy < energy + gain) {
			energy = maxEnergy;
		}
		else {
			energy += gain;
		}
	}

	void Player::AddMoney(float money) {
		this->money += money;
	}

	bool Player::purchase(float payment) {
		//return true if paymenrt can go through, false otherwise
		if (money - payment < 0) {
			return false;
		}
		else {
			money -= payment;
			return true;
		}
	}

	void Player::DiscoveredArtifact(Artifact* newArtifact) {
		//add a discovered artifact
		AddMoney(newArtifact->Discover());
		artifacts.push_back(newArtifact);
		if (artifacts.size() >= Game::GetInstance().GetArtifacts().size()) {
			Game::GetInstance().SetState(State::YOU_WIN);
		}
	}

	Artifact* Player::GetArtifact(int id) {
		//retrieve an artifact based of id
		for (int i = 0; i < artifacts.size(); i++) {
			if (id == artifacts[i]->GetId()) {
				return artifacts[i];
			}
		}
		return NULL;
	}

	void Player::printArtifacts() {
		//used for testing
		for (int i = 0; i < artifacts.size(); i++) {
			std::cout << "Artifact Name: " << artifacts[i]->GetArtifactName() << "ID: "<< artifacts[i]->GetName()<< "Value: "<< artifacts[i]->GetValue()<<"\n";
		}
	}

	
}