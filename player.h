#pragma once
#include <iostream>
#include <string>

class Player
{
    std::string name;
    int health = 100;
    int level = 1;
    int experience = 0;
public:
    Player(const std::string& name);
    ~Player();

    void displayStats() const;
    void setName(const std::string& newName);
    void takeDamage(int amount);
    void gainXP(int amount);
    int xpToLevelUp() const;
    void train();
};
