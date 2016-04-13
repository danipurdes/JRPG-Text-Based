#include "Actor.h"

Actor::Actor (std::string _name, int _maxhealth, int _ap, int _damage, int _armor, float _accuracy) 
	: name(_name), health_cur(_maxhealth), health_max(_maxhealth), 
	action_points_cur(_ap), action_points_max(_ap), 
	damage_cur(_damage), damage_def(_damage), 
	armor_cur(_armor), armor_def(_armor), 
	accuracy_cur(_accuracy), accuracy_def(_accuracy) {}

std::string Actor::get_info () {
	std::string info;
	info += name + " | "; 
	info += "He(" + std::to_string(health_cur) + "/" + std::to_string(health_max) + ") ";
	info += "AP(" + std::to_string(action_points_cur) + "/" + std::to_string(action_points_max) + ") ";
	info += "Da(" + std::to_string(damage_cur) + ") ";
	info += "Ar(" + std::to_string(armor_cur) + ") ";
	info += "Ac(" + std::to_string(accuracy_cur) + ")";
	return info;
}

void Actor::defend () {
	armor_cur += std::max(1, (int).5f);
}