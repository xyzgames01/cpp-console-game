#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "player.h"

Player::Player(const std::string& n)
    : name(n), health(100), level(1), experience(0){
        std::cout << "Player " << name << " created with default stats.\n";
    };

void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::displayStats() const {
    std::cout << "\n" << name << "\'s" << " stats" << "\n"
          << "Health: " << health << "\n"
          << "Level: " << level << "\n"
          << "Experience Needed to level up: " << xpToLevelUp() << "\n";
}

void Player::takeDamage(int damage){
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " took " << damage << " damage. Current health: " << health << "\n";
}


void Player::gainXP(int xp){
    experience += xp;
    if(experience >= level * 10){
        experience -= level * 10;
        ++level;
        std::cout << name << " leveled up to " << level << "!\n";
    }
}

 int Player::xpToLevelUp() const {
    return level * 10 - experience;
}

void Player::train(){
    std::cout << name << " trains hard...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate training time
    std::cout << name << " has finished training and gained 15 XP!\n";    
    gainXP(15); // Gain some XP after training
}

Player::~Player(){
}