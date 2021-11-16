#include "Objects/Player.h"
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
	}


	Player::~Player() {}

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

	HoverTank* Player::GetTank() {
		return tank;
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
		health = health - damage;
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

	void Player::gainMoney(float gain) {
		money += gain;
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
		artifacts.push_back(newArtifact);
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