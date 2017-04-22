#pragma once
#include "Vertex.h"
#include <vector>

#include "stdafx.h"

#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include "Constants.h"
using namespace std;
using namespace Constants;

class Shape
{

private:
	bool is_vertex_inside(Shape s, Vertex v) {
		if (s.vertexes.size() == 3) {
			//special triangle hitbox
			switch (s.type)
			{
			case PLAYER:
				if (v.pos_y >= s.vertexes[1].pos_y + (PLAYER_HEIGHT / 2)) {  //vertex is above triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y + (PLAYER_HEIGHT / 2) &&  //vertex Y is above triangle middle
					v.pos_y <= s.vertexes[0].pos_y && //vertex Y is below triangle top
					v.pos_x >= s.vertexes[0].pos_x - (PLAYER_WIDTH / 4)   && //vertex X is on the right of player width/4 (aproximated)
					v.pos_x <= s.vertexes[0].pos_x + (PLAYER_WIDTH / 4);   //vertex X is left of player width/4
				}
				else { //vertex is below triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y &&  //   vertex Y is above triangle bottom
					v.pos_y <= s.vertexes[1].pos_y + (PLAYER_HEIGHT / 2) &&  //vertex Y is below triangle vertical middle         
					v.pos_x >= s.vertexes[2].pos_x && v.pos_x <= s.vertexes[1].pos_x;  //vertex X is on right of triangle left and left of triangle right
				}
				break;
			case ENEMY:
				if (v.pos_y >= s.vertexes[1].pos_y + (ENEMY_HEIGHT / 2)) {  //vertex is above triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y + (ENEMY_HEIGHT / 2) &&  //vertex Y is above triangle middle                 
					v.pos_y <= s.vertexes[0].pos_y && //vertex Y is below triangle top
					v.pos_x >= s.vertexes[0].pos_x - (ENEMY_WIDTH / 4) &&  //vertex X is on the right of player width/4 (aproximated)
					v.pos_x <= s.vertexes[0].pos_x + (ENEMY_WIDTH / 4);  //vertex X is left of player width/4
				}
				else { //vertex is below triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y && //   vertex Y is above triangle bottom
					v.pos_y <= s.vertexes[1].pos_y + (ENEMY_HEIGHT / 2) &&  //vertex Y is below triangle vertical middle         
					v.pos_x >= s.vertexes[2].pos_x && //vertex X is on right of triangle left
					v.pos_x <= s.vertexes[1].pos_x;   //and left of triangle right
				}
				break;
			case ENEMY_FOV:
				//in the case of enemy FoV, the triangle hitbox logic must be inversed (since the FoV is an upside-down triangle
				if (v.pos_y >= s.vertexes[2].pos_y + (ENEMY_FOV_HEIGHT / 2)) {  //vertex is above triangle vertical middle
					return  v.pos_y <= s.vertexes[0].pos_y && //vertex is y-inside the triangle
					v.pos_x >= s.vertexes[0].pos_x && // vertex is right of the left vertex
					v.pos_x <= s.vertexes[1].pos_x; //vertex is left of right vertex (is x-inside the triangle
				}
				else { //vertex is below triangle vertical middle
					return v.pos_y >= s.vertexes[2].pos_y && //vertex is y-inside triangle
					v.pos_x >= s.vertexes[2].pos_x - (ENEMY_FOV_WIDTH / 4) && //vertex is right of FoV width/4 (aproximated)
					v.pos_x <= s.vertexes[2].pos_x + (ENEMY_FOV_WIDTH / 4); //vertex is left of FoV width/4 (aproximated)
				}
				break;
			case HOSTAGE:
				if (v.pos_y >= s.vertexes[1].pos_y + (HOSTAGE_HEIGHT / 2)) {  //vertex is above triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y + (HOSTAGE_HEIGHT / 2) &&  //vertex Y is above triangle middle
					v.pos_y <= s.vertexes[0].pos_y && //vertex Y is below triangle top
					v.pos_x >= s.vertexes[0].pos_x - (HOSTAGE_WIDTH / 4) && //vertex X is on the right of player width/4 (aproximated)
					v.pos_x <= s.vertexes[0].pos_x + (HOSTAGE_WIDTH / 4);  //vertex X is left of player width/4
				}
				else { //vertex is below triangle vertical middle
					return v.pos_y >= s.vertexes[1].pos_y &&  //vertex Y is above triangle bottom 
					v.pos_y <= s.vertexes[1].pos_y + (HOSTAGE_HEIGHT / 2) &&  //vertex Y is below triangle vertical middle         
					v.pos_x >= s.vertexes[2].pos_x && //vertex X is on right of triangle left
					v.pos_x <= s.vertexes[1].pos_x;   //and left of triangle right
				}
				break;
			}
		}
		else {
			//normal square hitbox
			return v.pos_x >= s.vertexes[0].pos_x && v.pos_x <= s.vertexes[1].pos_x && v.pos_y <= s.vertexes[0].pos_y && v.pos_y >= s.vertexes[3].pos_y;
		}
	}

public:
	int type;
	std::vector<Vertex> vertexes;
	float health; //if the shape is aplayer, enemy or hostage, it has a health value
	Vertex reference = Vertex(0.0,0.0); //if the shape is a bullet, it has a vertex as reference of the point where it was shot
	float vertical_middle;
	float horizontal_middle;
	float angle;

	Shape(int type, std::vector<Vertex> vertexes) {
		this->type = type;
		this->vertexes = vertexes;
		switch (type)
		{
		case PLAYER:
			health = PLAYER_HEALTH;
			vertical_middle = ((this->vertexes[1].pos_y + this->vertexes[0].pos_y) / 2);
			horizontal_middle = this->vertexes[0].pos_x;
			break;
		case ENEMY:
			health = ENEMY_HEALTH;
			vertical_middle = ((this->vertexes[1].pos_y + this->vertexes[0].pos_y) / 2);
			horizontal_middle = this->vertexes[0].pos_x;
			break;
		case HOSTAGE:
			health = HOSTAGE_HEALTH;
			break;
		case ENEMY_FOV:
			vertical_middle = ((this->vertexes[0].pos_y + this->vertexes[2].pos_y) / 2);
			horizontal_middle = this->vertexes[2].pos_x;
		default:
			break;
		}
	}

	Shape(int type, std::vector<Vertex> vertexes, Vertex reference, float angle) {
		this->type = type;
		this->vertexes = vertexes;
		switch (type)
		{
		case BULLET:
			this->reference = reference;
			this->angle = angle;
			break;
		}
	}

	void translate(float direction_up, float direction_down, float direction_left, float direction_rigth) {
		for (int v = 0; v < vertexes.size();v++) {
			vertexes[v].pos_x += direction_rigth;
			vertexes[v].pos_x -= direction_left;
			vertexes[v].pos_y += direction_up;
			vertexes[v].pos_y -= direction_down;
		}

		this->vertical_middle += direction_up;
		this->vertical_middle -= direction_down;
		this->horizontal_middle += direction_rigth;
		this->horizontal_middle -= direction_left;
	}

	void rotate(float angle) {

		for (int i = 0; i < this->vertexes.size(); i++) {
			//translate to origin
			this->vertexes[i].pos_x -= this->horizontal_middle;
			this->vertexes[i].pos_y -= this->vertical_middle;

			//apply rotation
			double angle_sin = sin(angle);
			double angle_cos = cos(angle);

			double new_x = this->vertexes[i].pos_x * angle_cos - this->vertexes[i].pos_y * angle_sin;
			double new_y = this->vertexes[i].pos_x * angle_sin + this->vertexes[i].pos_y * angle_cos;

			//revert translation to origin
			this->vertexes[i].pos_x = new_x + horizontal_middle;
			this->vertexes[i].pos_y = new_y + vertical_middle;
		}
	}

	void rotate(float angle, Vertex rotation_reference) {

		for (int i = 0; i < this->vertexes.size(); i++) {
			//translate to origin
			this->vertexes[i].pos_x -= rotation_reference.pos_x;
			this->vertexes[i].pos_y -= rotation_reference.pos_y;

			//apply rotation
			double angle_sin = sin(angle);
			double angle_cos = cos(angle);

			double new_x = this->vertexes[i].pos_x * angle_cos - this->vertexes[i].pos_y * angle_sin;
			double new_y = this->vertexes[i].pos_x * angle_sin + this->vertexes[i].pos_y * angle_cos;

			//revert translation to origin
			this->vertexes[i].pos_x = new_x + rotation_reference.pos_x;
			this->vertexes[i].pos_y = new_y + rotation_reference.pos_y;
		}
	}

	void move_bullet() {

		//moving bullet to origin acording to reference point
		for (int i = 0; i < this->vertexes.size(); i++) {
			this->vertexes[i].pos_x -= this->reference.pos_x;
			this->vertexes[i].pos_y -= this->reference.pos_y;
		}

		//undoing the rotation of the bullet
		this->rotate(angle * -1,this->reference);

		//moving bullet
		for(int i=0;i<this->vertexes.size();i++){
			this->vertexes[i].pos_y += BULLET_MOVEMENT_TIC;
		}
		
		//redoing rotation
		this->rotate(angle,this->reference);

		//back to original position
		for (int i = 0; i < this->vertexes.size(); i++) {
			this->vertexes[i].pos_x += this->reference.pos_x;
			this->vertexes[i].pos_y += this->reference.pos_y;
		}

	}

	bool is_colliding_with(Shape s) {

		for (int i = 0; i < this->vertexes.size(); i++) {
			if (is_vertex_inside(s, this->vertexes[i]))
				return true;
		}

		for (int i = 0; i < s.vertexes.size(); i++) {
			if (is_vertex_inside(*this, s.vertexes[i]))
				return true;
		}

		return false;

	}

	vector<float> check_color() {
		vector<float> ret;
		switch (type)
		{
		case WALL:
			return WALL_COLOR;
			break;
		case PLAYER:
			if (this->health == 3) {
				return PLAYER_COLOR_FULL;
			}
			else if (this->health == 2) {
				return PLAYER_COLOR_MEDIUM;
			}
			else if(this->health == 1){
				return PLAYER_COLOR_LOW;
			}
			else {
				return PLAYER_COLOR_DEAD;
			}
			
			break;
		case ENEMY:
			return ENEMY_COLOR;
			break;
		case ENEMY_FOV:
			return ENEMY_FOV_COLOR;
			break;
		case HOSTAGE:
			return HOSTAGE_COLOR;
			break;
		case BULLET:
			return BULLET_COLOR;
			break;
		case POWERUP:
			return POWERUP_COLOR;
			break;
		}
	}

	void draw() {
		vector<float> color = check_color();
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_POLYGON);
		for (Vertex v : vertexes) {
			glVertex2f(v.pos_x, v.pos_y);
		}
		glEnd();
	}

	Shape simulate_translation(float direction_up, float direction_down, float direction_left, float direction_rigth) {
		Shape ret(PLAYER, { this->vertexes[0], this->vertexes[1], this->vertexes[2] });
		ret.translate(direction_up, direction_down, direction_left, direction_rigth);
		return ret;
	}

};

