#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>

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
	// Title
	std::cout << "JRPG Combat Prototype" << std::endl;

	srand(time(NULL));

	bool addAnotherPlayer = true;
	while (addAnotherPlayer) {
		// If name wasn't an argument, prompt for name
		std::string name;
		std::cout << "Enter party member's name: ";
		std::cin >> name;
				
		// Testing if inputting name worked
		std::cout << "Hello, " << name << std::endl;

		// Generate Actor's stats
		int health_rand = rand() % 11 + 5;
		int ap_rand = rand() % 4 + 1;
		int damage_rand = rand() % 5 + 3;
		int armor_rand = rand() % 3 + 0;
		float accuracy_rand = (float)(rand() % 51 + 50)/100.0f;

		// Print Actor's get_info()
		Actor* a = new Actor(name, health_rand, ap_rand, damage_rand, armor_rand, accuracy_rand);
		std::cout << a->get_info() << std::endl;
		players.push_back(a);

		std::cout << std::endl;
		std::cout << "Add another party member? (y/n)" << std::endl;
		std::string resp;
		std::cin >> resp;
		if (resp[0] != 'y' || players.size() >= 3)
			addAnotherPlayer = false;
	}
	
	std::cin.ignore();
	pressEnterToContinue();



	// A wild Skeleton appears!
	std::cout << "A spooky gang of Skeletons wants to fight you!" << std::endl;
	int count_skel = rand() % 4 + 3;
	for (int i = 0; i < 4; i++) {
		// Generate Actor's stats
		int health_rand = rand() % 11 + 5;
		int ap_rand = rand() % 4 + 1;
		int damage_rand = rand() % 5 + 3;
		int armor_rand = rand() % 3 + 0;
		float accuracy_rand = (float)(rand() % 51 + 50)/100.0f;

		e = new Actor("Skeleton #", health_rand, ap_rand, damage_rand, armor_rand, accuracy_rand);
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
					std::cout << ":::" << i->name << "'s " << "Turn:::" << std::endl;
					std::cout << "a - standard attack" << std::endl;
					std::cout << "s - special attack" << std::endl;
					std::cout << "d - guard" << std::endl;
					std::cout << "f - item menu" << std::endl;
					std::cout << ">";

					i->armor_cur = i->armor_def;

					std::string input;
					getline(std::cin, input);
					switch (input[0]) {
						case 'a' : {
							auto last = otherParty->back();
							std::cout << i->name << " swings at " << last->name << "!" << std::endl;
							int dmg = i->damage_cur;
							int arm = last->armor_cur;
							int acc = i->accuracy_cur * 100;
							
							int roll = rand() % 100;
							std::cout << "Rolled " << roll << " | Needed less than " << acc << std::endl;
							if (acc >= roll) {
								int amount_damage = std::max(0, (dmg - arm));
								last->health_cur -= amount_damage;
								std::cout << i->name << " hits " << last->name << " for " << amount_damage << " damage!" << std::endl;
							}
							else {
								std::cout << i->name << " missed " << last->name << "!" << std::endl;
							}
							pressEnterToContinue();

							if (last->health_cur <= 0) {
								otherParty->pop_back();
							}

							printMessageCombatantStatus();

							break;
						}
						case 's' : {
							auto last = otherParty->back();
							if (i->action_points_cur > 0) {
								i->action_points_cur--;
								std::cout << i->name << " shoots a fireball at " << last->name << "!" << std::endl;
								int dmg = i->damage_cur;
								int arm = last->armor_cur;
								int bonus = i->accuracy_cur * dmg;
								
								int roll = rand() % (bonus + 1);
								int amount_damage = std::max(0, dmg + roll - arm);
								last->health_cur -= amount_damage;
								std::cout << "Fireball hits for " << amount_damage << " damage!";
							}
							pressEnterToContinue();

							if (last->health_cur <= 0) {
								otherParty->pop_back();
							}
							
							printMessageCombatantStatus();

							break;
						}
						case 'd' : {
							std::cout << i->name << " braces themselves!" << std::endl;
							i->defend();

							pressEnterToContinue();
							
							printMessageCombatantStatus();

							break;
						}
						case 'f' : {
							std::cout << "Select an item by index number:" << std::endl;
							std::cout << "1. potion (+10 He)" << std::endl;
							std::cout << "2. strength herb (+4 Da)" << std::endl;
							std::cout << "3. focus brace (x2 Ac)" << std::endl;
							std::cout << "4. grenade (8 Da)" << std::endl;
							std::string choice_str;
							int choice_ind;
							getline(std::cin, choice_str);
							auto last = otherParty->back();
							if (choice_str != "") {
								choice_ind = stoi(choice_str);

								

								switch (choice_ind) {
									case 1 : {
										std::cout << "Used a potion!" << std::endl;
										i->health_cur = std::min(i->health_cur + 10, i->health_max);
										break;
									}
									case 2 : {
										std::cout << "Used a strength herb!" << std::endl;
										i->damage_cur += 4;
										break;
									}
									case 3 : {
										std::cout << "Used a focus brace!" << std::endl;
										i->accuracy_cur = std::min(i->accuracy_cur * 2, 1.0f);
										break;
									}
									case 4 : {
										std::cout << "Used a grenade!" << std::endl;
										last->health_cur = 8 - last->armor_cur; 
										break;
									}
								}
							}

							pressEnterToContinue();

							if (last->health_cur <= 0) {
								otherParty->pop_back();
							}
							
							printMessageCombatantStatus();
						}
						
					}
					//playerAttack();
				}
				else {
					auto last = otherParty->back();
					//std::cout << i->name << " swings at " << last->name << "!" << std::endl;
					int dmg = i->damage_cur;
					int arm = last->armor_cur;
					int acc = i->accuracy_cur * 100;
					
					int roll = rand() % 100;
					//std::cout << "Rolled " << roll << " | Needed less than " << acc << std::endl;
					if (acc >= roll) {
						int amount_damage = std::max(0, (dmg - arm));
						last->health_cur -= amount_damage;
						std::cout << i->name << " hits " << last->name << " for " << amount_damage << " damage!" << std::endl;
					}
					else {
						std::cout << i->name << " missed " << last->name << "!" << std::endl;
					}
					//pressEnterToContinue();

					if (last->health_cur <= 0) {
						otherParty->pop_back();
					}

					//printMessageCombatantStatus();
					
					//enemyAttack();
				}
				
			}

			pressEnterToContinue();
			printMessageCombatantStatus();
			pressEnterToContinue();

			std::vector<Actor*>* t = currentParty;
			currentParty = otherParty;
			otherParty = t;
		}
		else {
			battling = false;
		}
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