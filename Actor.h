#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <string>

class Actor {
public:
	std::string name;
	int team_id;
	int health_cur;
	int health_max;
	int action_points;
	int damage;
	int armor;
	float accuracy;
	//etc

	Actor(std::string,int,int,int,int,int,float);
	~Actor();

	void attack();
	void defend();
	std::string get_info();
};

#endif