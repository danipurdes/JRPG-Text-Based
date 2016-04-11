#include <iostream>
#include <string>

#include "Actor.h"
#include "PlayerActor.h"
#include "EnemyActor.h"

//static Actor* a;
//static Actor* e;
static vector<Actor*> combatants;

void printMessageCombatantStatus () {
	std::cout << ":::Combatant Status:::" << std::endl;
	std::cout << a->get_info() << std::endl;
	std::cout << e->get_info() << std::endl;
}

void pressEnterToContinue () {
	std::cout << std::endl;
	std::cout << "Enter to continue..." << std::endl;
	std::string nlbuf;
	getline(std::cin, nlbuf);
}

int main(int argc, const char** argv) {
	// Check if name has been entered as an argument
	//std::string name;
	//if (argc > 1)
	//	name = argv[1];

	// Title
	std::cout << "JRPG Combat Prototype" << std::endl;

	// If name wasn't an argument, prompt for name
	std::string name;
	if (name == "") {
		std::cout << "Enter your name: ";
		std::cin >> name;
	}
	
	// Testing if inputting name worked
	std::cout << "Hello, " << name << std::endl;

	// Print Actor's get_info()
	a = new Actor(name, 10, 3, 6, 4, 0.5f);
	std::cout << a->get_info() << std::endl;

	std::cin.ignore();
	pressEnterToContinue();

	// A wild Skeleton appears!
	std::cout << "A skeleton wants to fight you!" << std::endl;
	e = new Actor("Skeleton", 8, 3, 6, 4, 0.5f);
	std::cout << e->get_info() << std::endl;
	pressEnterToContinue();

	//Time to battle!
	printMessageCombatantStatus();
	pressEnterToContinue();

	bool battling = true;
	while (battling) {
		if (a->health_cur > 0) {
			//Player turn
			std::cout << ":::Player's Turn:::" << std::endl;
			std::cout << "Type (a)ttack to strike with " << a->name << "!" << std::endl;
			std::cout << ">";
			std::string input;
			getline(std::cin, input);
			if (input[0] == 'a') {
				std::cout << a->name << " swings at " << e->name << "!" << std::endl;
				int dmg = a->damage;
				e->health_cur -= dmg;
				std::cout << a->name << " hits " << e->name << " for " << a->damage << " damage!" << std::endl;
				pressEnterToContinue();

				printMessageCombatantStatus();

				isEnemyDead = (e->health_cur <= 0);
			}
			else {
				std::cout << "You miss your turn!" << std::endl;
			}
			pressEnterToContinue();
		}
		else
			break;

		if (e->health_cur > 0) {
			//Enemy turn
			std::cout << ":::Enemy's Turn:::" << std::endl;
			std::cout << e->name << " swings at " << a->name << "!" << std::endl;
			int dmg = e->damage;
			a->health_cur -= dmg;
			std::cout << e->name << " hits " << a->name << " for " << e->damage << " damage!" << std::endl;
			pressEnterToContinue();

			printMessageCombatantStatus();
			pressEnterToContinue();
		}
		else {
			battling = false;
			std::cout << ":::CONGRATULATIONS:::" << std::endl;
			std::cout << "You defeated the enemy!" << std::endl;
		}
	}

	// End of prototype
	std::cout << "-end-" << std::endl;
}