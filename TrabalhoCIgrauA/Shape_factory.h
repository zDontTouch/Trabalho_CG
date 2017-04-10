#pragma once
#include "Shape_factory.h"
#include "Shape.h"
#include "Vertex.h"
#include "Constants.h"
using namespace std;
using namespace Constants;



class Shape_factory
{


public:
	Shape create_shape(int type, Vertex anchor) {

		switch (type)
		{
		case Constants::PLAYER:
		{	
			vector<Vertex> vert{ anchor, Vertex(anchor.pos_x + (PLAYER_WIDTH / 2), anchor.pos_y - PLAYER_HEIGHT) , Vertex(anchor.pos_x - (PLAYER_WIDTH / 2), anchor.pos_y - PLAYER_HEIGHT) };
			Shape ret(type, vert);
			return ret;
			break;
		}
		case Constants::ENEMY:
		{
			vector<Vertex> vert{ anchor, Vertex(anchor.pos_x + (ENEMY_WIDTH / 2), anchor.pos_y - ENEMY_HEIGHT) , Vertex(anchor.pos_x - (ENEMY_WIDTH / 2), anchor.pos_y - ENEMY_HEIGHT) };
			Shape ret(type, vert);
			return ret;
			break;
		}
		case Constants::POWERUP:
		{
			vector<Vertex> vert{ anchor, Vertex(anchor.pos_x + POWERUP_WIDTH, anchor.pos_y) , Vertex(anchor.pos_x + POWERUP_WIDTH, anchor.pos_y - POWERUP_HEIGHT) , Vertex(anchor.pos_x,anchor.pos_y-POWERUP_HEIGHT) };
			Shape ret(type, vert);
			return ret;
			break;
		}
		case Constants::ENEMY_FOV:
		{
			vector<Vertex> vert{ Vertex(anchor.pos_x - ENEMY_FOV_WIDTH/2, anchor.pos_y + ENEMY_FOV_HEIGHT), Vertex(anchor.pos_x + ENEMY_FOV_WIDTH / 2, anchor.pos_y + ENEMY_FOV_HEIGHT), anchor };
			Shape ret(type, vert);
			return ret;
			break;
		}
		case Constants::HOSTAGE:
		{
			vector<Vertex> vert{ anchor, Vertex(anchor.pos_x + (PLAYER_WIDTH / 2), anchor.pos_y - PLAYER_HEIGHT) , Vertex(anchor.pos_x - (PLAYER_WIDTH / 2), anchor.pos_y - PLAYER_HEIGHT) };
			Shape ret(type, vert);
			return ret;
			break;
		}
		case Constants::BULLET:
		{
			vector<Vertex> vert{ anchor, Vertex(anchor.pos_x + BULLET_WIDTH,anchor.pos_y), Vertex(anchor.pos_x + BULLET_WIDTH,anchor.pos_y - BULLET_HEIGHT), Vertex(anchor.pos_x,anchor.pos_y - BULLET_HEIGHT) };
			Shape ret(type, vert);
			return ret;
			break;
		}

		}

	}

	Shape create_shape(int type, Vertex anchor, float height, float width) {
		vector<Vertex> vert{ anchor, Vertex(anchor.pos_x+width,anchor.pos_y), Vertex(anchor.pos_x + width,anchor.pos_y - height), Vertex(anchor.pos_x,anchor.pos_y-height) };
		Shape ret(type, vert);
		return ret;
	}

};

