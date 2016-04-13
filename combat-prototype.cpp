#include <iostream>
#include <string>
#include <vector>

#include "Actor.h"
//#include "PlayerActor.h"
//#include "EnemyActor.h"

static Actor* a;
static Actor* e;
static std::vector<Actor*> players;
static std::vector<Actor*> enemies;

void printMessageCombatantStatus () {
	std::cout << ":::Player Party:::" << std::endl;
	for (auto i : players) {
		std::cout << i->get_info() << std::endl;
	}

	std::cout << std::endl;

	std::cout << ":::Enemy Party:::" << std::endl;
	for (auto i : enemies) {
		std::cout << i->get_info() << std::endl;
	}
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

	bool addAnotherPlayer = true;
	while (addAnotherPlayer) {
		// If name wasn't an argument, prompt for name
		std::string name;
		std::cout << "Enter party member's name: ";
		std::cin >> name;
				
		// Testing if inputting name worked
		std::cout << "Hello, " << name << std::endl;

		// Print Actor's get_info()
		Actor* a = new Actor(name, 10, 3, 6, 4, 0.5f);
		std::cout << a->get_info() << std::endl;
		players.push_back(a);

		std::cout << std::endl;
		std::cout << "Add another party member? (y/n)" << std::endl;
		std::string resp;
		std::cin >> resp;
		if (resp[0] != 'y')
			addAnotherPlayer = false;
	}
	
	std::cin.ignore();
	pressEnterToContinue();



	// A wild Skeleton appears!
	std::cout << "A spooky gang of Skeletons wants to fight you!" << std::endl;
	for (int i = 0; i < 4; i++) {
		e = new Actor("Skeleton #", 8, 3, 6, 4, 0.5f);
		e->name = e->name + std::to_string(i);
		std::cout << e->get_info() << std::endl;
		enemies.push_back(e);
	}
	
	pressEnterToContinue();

	std::vector<Actor*>* currentParty = &players;
	std::vector<Actor*>* otherParty = &enemies;

	//Time to battle!
	printMessageCombatantStatus();
	pressEnterToContinue();

	bool battling = true;
	while (battling) {
		if (currentParty->size() > 0 && otherParty->size() > 0) {
			for (auto i = currentParty->begin(); i != currentParty->end(); ++i) {
				if ((*i)->health_cur <= 0) {
					i = currentParty->erase(i);
				}
			}
			for (auto i : *currentParty) {
				if (otherParty->size() == 0) {
					break;
				}

				if (*currentParty == players) {
						std::cout << ":::" << i->name << "'s " << " Turn:::" << std::endl;
					std::cout << "Type (a)ttack to strike with " << i->name << "!" << std::endl;
					std::cout << ">";
					std::string input;
					getline(std::cin, input);
					if (input[0] == 'a') {
						auto last = otherParty->back();
						std::cout << i->name << " swings at " << last->name << "!" << std::endl;
						int dmg = i->damage;
						last->health_cur -= dmg;
						std::cout << i->name << " hits " << last->name << " for " << i->damage << " damage!" << std::endl;
						pressEnterToContinue();

						if (last->health_cur <= 0) {
							otherParty->pop_back();
						}

						printMessageCombatantStatus();
					}
					else {
						std::cout << "You miss your turn!" << std::endl;
					}

					//playerAttack();
				}
				else {
					auto last = otherParty->back();
					std::cout << i->name << " swings at " << last->name << "!" << std::endl;
					int dmg = i->damage;
					last->health_cur -= dmg;
					std::cout << i->name << " hits " << last->name << " for " << i->damage << " damage!" << std::endl;
					pressEnterToContinue();

					if (last->health_cur <= 0) {
						otherParty->pop_back();
					}

					printMessageCombatantStatus();
					
					//enemyAttack();
				}
				
				pressEnterToContinue();
			}
			
			std::vector<Actor*>* t = currentParty;
			currentParty = otherParty;
			otherParty = t;
		}
		else
			battling = false;

		// if (e->health_cur > 0) {
		// 	//Enemy turn
		// 	std::cout << ":::Enemy's Turn:::" << std::endl;
		// 	std::cout << e->name << " swings at " << a->name << "!" << std::endl;
		// 	int dmg = e->damage;
		// 	a->health_cur -= dmg;
		// 	std::cout << e->name << " hits " << a->name << " for " << e->damage << " damage!" << std::endl;
		// 	pressEnterToContinue();

		// 	printMessageCombatantStatus();
		// 	pressEnterToContinue();
		// }
		// else {
		// 	battling = false;
		// 	std::cout << ":::CONGRATULATIONS:::" << std::endl;
		// 	std::cout << "You defeated the enemy!" << std::endl;
		// }
	}

	if (players.size() > 0) {
		std::cout << ":::YOU WIN:::" << std::endl;
	}
	if (enemies.size() > 0) {
		std::cout << ":::YOU LOSE:::" << std::endl;
	}

	// End of prototype
	std::cout << "-end-" << std::endl;
}