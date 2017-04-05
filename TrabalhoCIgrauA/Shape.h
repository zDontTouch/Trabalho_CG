#pragma once
#include "Vertex.h"
#include <vector>

#include "stdafx.h"

#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include "Constants.h"
using namespace std;

class Shape
{
public:
	int type;
	std::vector<Vertex> vertexes;

	Shape(int type, std::vector<Vertex> vertexes) {
		this->type = type;
		this->vertexes = vertexes;
	}

	void translate(float direction_up, float direction_down, float direction_left, float direction_rigth) {
		for (int v = 0; v < vertexes.size();v++) {
			vertexes[v].pos_x += direction_rigth;
			vertexes[v].pos_x -= direction_left;
			vertexes[v].pos_y += direction_up;
			vertexes[v].pos_y -= direction_down;
		}
	}

	void rotate(float angle) {
		for (int v = 0; v < vertexes.size(); v++) {
			vertexes[v].pos_x = vertexes[v].pos_x * cos(angle) - vertexes[v].pos_y * sin(angle);
			vertexes[v].pos_y = vertexes[v].pos_x * sin(angle) - vertexes[v].pos_y * cos(angle);
		}
	}

	bool is_colliding_with(Shape s) {
		//implement collision
	}

	vector<float> check_color() {
		vector<float> ret;
		switch (type)
		{
		case Constants::WALL:
			ret = { 0.0f , 0.3f , 0.0f };
			break;
		case Constants::PLAYER:
			ret = { 0.1f , 7.0f , 7.0f };
			break;
		case Constants::ENEMY:
			ret = { 0.8f , 0.0f , 0.0f };
			break;
		case Constants::ENEMY_FOV:
			ret = { 1.0f , 0.5f , 0.5f };
			break;
		case Constants::HOSTAGE:
			ret = { 1.0f , 0.0f , 1.0f };
			break;
		case Constants::BULLET:
			ret = { 0.0f , 0.0f , 0.0f };
			break;
		case Constants::POWERUP:
			ret = { 0.0f , 0.0f , 0.0f };
			break;
		}

		return ret;
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
};

