#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <windows.h>
#include "utils.h"
#include "player.h"

const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int ENTER = 13;

const int CREATE_CHARACTER = 0;
const int EXIT = 1;
const int PLAYER_ACTIONS = 2;
const int FIGHT = 3;
const int DISPLAY_STATS = 4;
const int TAKE_DAMAGE = 5;
const int TRAIN = 6;
const int BACK = 7;

const int MAIN_MENU = 0;
const int ACTIONS_MENU = 1;
const int PLAYER_MENU = 2;


void clearScreen() {
    system("cls");
}

struct MenuOption {
    std::string label;
    int actionId;
};

struct Menu {
    int id;
    std::string title;
    std::vector<MenuOption> options;
};

void displayMenu(const Menu& menu, int selected) {
    std::cout << "=== " << menu.title << " ===" <<std::endl;
    for (size_t i = 0; i < menu.options.size(); ++i) {
        if (i == selected) {
            std::cout << "> " << menu.options[i].label << " <\n";
        } else {
            std::cout << menu.options[i].label << "\n";
        }
    }
}

void handleInput(int& key, int& selected, size_t menuSize) {
    if (key == UP_ARROW) { // Up arrow
        selected = (selected - 1 + menuSize) % menuSize;
    } else if (key == DOWN_ARROW) { // Down arrow
        selected = (selected + 1) % menuSize;
    }
}

int main() {

    Player p("Hero");

    MenuOption createCharacter{"Create Character", CREATE_CHARACTER};
    MenuOption exitOption{"Exit", EXIT};
    MenuOption playerActions{"Player Actions", PLAYER_ACTIONS};
    MenuOption fight{"Fight", FIGHT};
    MenuOption displayStats{"Display Stats", DISPLAY_STATS};
    MenuOption takeDamage{"Take Damage", TAKE_DAMAGE};
    MenuOption train{"Train", TRAIN};
    MenuOption back{"Back", BACK};

    Menu mainMenu{MAIN_MENU, "Main Menu", {createCharacter, exitOption}};
    Menu actionsMenu{ACTIONS_MENU, "Action Menu", {playerActions, fight, exitOption}};
    Menu playerMenu{PLAYER_MENU, "Player Menu", {displayStats, train, back}};

    std::vector<Menu> menus = {mainMenu, actionsMenu, playerMenu};

    int menuIndex = MAIN_MENU; 
    int lastMenuIndex = menuIndex;
    int selected = 0;
    bool running = true;

    while (running)
    {
        clearScreen();

        Menu& currentMenu = menus[menuIndex];
        size_t menuSize = menus[menuIndex].options.size(); 
        
        displayMenu(currentMenu, selected);
        
        int key = _getch();
        handleInput(key, selected, menuSize);

        if (key == ENTER){
            switch (menus[menuIndex].options[selected].actionId) {
                case CREATE_CHARACTER:{ 
                        std::string name;
                        std::cout << "Enter player name: ";
                        std::cin >> name;
                        std::cout << "Welcome to the adventure: " << name << "\n";
                        p.setName(name);
                        menuIndex = actionsMenu.id;
                        std::cout << "Press any key to continue...\n";
                        _getch();
                    }
                    break;
                case EXIT: 
                    running = false;
                    break;
                case PLAYER_ACTIONS: 
                    lastMenuIndex = menuIndex;
                    menuIndex = playerMenu.id;
                    selected = 0;
                    break;
                case FIGHT: 
                    std::cout << "You engage in a fight!\n";
                    p.takeDamage(Utils::getRandomInt(5, 20));
                    std::cout << "Press any key to continue...\n";
                    _getch();
                    break;
                case DISPLAY_STATS:
                    p.displayStats();
                    std::cout << "Press any key to continue...\n";
                    _getch();
                    break;
                case TAKE_DAMAGE:
                    p.takeDamage(Utils::getRandomInt(5, 20)); 
                    std::cout << "Press any key to continue...\n";
                    _getch();
                    break;
                case TRAIN:
                    p.train();
                    std::cout << "Press any key to continue...\n";
                    _getch();
                    break;
                case BACK:
                    menuIndex = lastMenuIndex;
                    selected = 0; 
                    break;
            }
        }
    }
    return 0;
}