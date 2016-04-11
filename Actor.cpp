#include "Actor.h"

Actor::Actor (std::string _name, int _maxhealth, int _ap, int _damage, int _armor, float _accuracy) 
	: name(_name), health_cur(_maxhealth), health_max(_maxhealth), action_points(_ap), damage(_damage), armor(_armor), accuracy(_accuracy) {}

std::string Actor::get_info () {
	std::string info;
	info += name + " | "; 
	info += "He(" + std::to_string(health_cur) + "/" + std::to_string(health_max) + ") ";
	info += "AP(" + std::to_string(action_points) + ") ";
	info += "Da(" + std::to_string(damage) + ") ";
	info += "Ar(" + std::to_string(armor) + ") ";
	info += "Ac(" + std::to_string(accuracy) + ")";
	return info;
}