#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <string>

class Actor {
public:
	std::string name;
	int health_cur;
	int health_max;
	int action_points_cur;
	int action_points_max;
	int damage_cur;
	int damage_def;
	int armor_cur;
	int armor_def;
	float accuracy_cur;
	float accuracy_def;
	//etc

	Actor(std::string,int,int,int,int,float);
	~Actor();

	void attack();
	void special();
	void defend();
	std::string get_info();
};

#endif