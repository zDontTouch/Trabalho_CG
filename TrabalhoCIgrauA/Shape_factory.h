#pragma once
#include "Shape_factory.h"
#include "Shape.h"
#include "Vertex.h"
#include "Constants.h"
using namespace std;

//definig contants to the game elements' size
float PLAYER_HEIGHT = 0.2;
float PLAYER_WIDTH = 0.15;

float ENEMY_HEIGHT = 0.1;
float ENEMY_WIDTH = 0.05;

float POWERUP_HEIGHT = 0.1;
float POWERUP_WIDTH = POWERUP_HEIGHT;

float ENEMY_FOV_HEIGHT = 0.3;
float ENEMY_FOV_WIDTH = 0.25;

float HOSTAGE_HEIGHT = 0.1;
float HOSTAGE_WIDTH = 0.1;

float BULLET_HEIGHT = 0.01;
float BULLET_WIDTH = BULLET_HEIGHT;

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

	Shape* create_shape(int type, Vertex anchor, float height, float width) {
		vector<Vertex> vert{ anchor, Vertex(anchor.pos_x+width,anchor.pos_y), Vertex(anchor.pos_x + width,anchor.pos_y - height), Vertex(anchor.pos_x,anchor.pos_y-height) };
		Shape ret(type, vert);
		return &ret;
	}

};

