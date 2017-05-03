// openGLteste.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include "Shape.h"
#include "Shape_factory.h"
#include "Vertex.h"
#include "Constants.h"
#include <time.h>
using namespace Constants;
using namespace std;

//game menu value
//this variable defines if the player is currently on the menu or is already in the game map
bool is_in_menu = true;
bool player_in_menu = false;
int menu_door_selected = 0;
vector<Vertex> menu_door_1{ Vertex(-99.0,-92.5), Vertex(-97.0,-92.5), Vertex(-97.0,-91.5), Vertex(-99.0,-91.5) };
vector<Vertex> menu_door_2{ Vertex(-96.5,-92.5), Vertex(-94.5,-92.5), Vertex(-94.5,-91.5), Vertex(-96.5,-91.5) };
vector<Vertex> menu_door_3{ Vertex(-94.0,-92.5), Vertex(-92.0,-92.5), Vertex(-92.0,-91.5), Vertex(-94.0,-91.5) };
vector<Shape> additional_bullets{};

double player_angle = 0;
double previous_mouse_x_position = 0.0;
double previous_mouse_y_position = 10.0;
bool is_mouse_clicked = false;
double current_mouse_angle = 0;
int magazine = 15;
int current_powerup = NONE;
int powerup_bullets = 0;
int direction1[4] = { 1, 1, 1, 1 };
int direction2[5] = { 1, 1, 1, 1, 1 };
int direction3[6] = { 1, 1, 1, 1, 1, 1 };
int enemy_velocity = 35;

//this function calculates the angle between the old and the current mouse position, in order to rotate the player object
double get_mouse_angle(int posX, int posY) {
	float normalized_previous = sqrt(pow(previous_mouse_x_position, 2) + pow(previous_mouse_y_position, 2));
	float normalized_current = sqrt(pow(posX, 2) + pow(posY, 2));

	float internal_product = (previous_mouse_x_position * posX) + (previous_mouse_y_position * posY);

	float angle_cos = internal_product / (normalized_previous * normalized_current);

	float angle = acos(angle_cos);

	//calculating delta to check for negative angles
	int delta_x = posX - previous_mouse_x_position;
	int delta_y = posY - previous_mouse_y_position;

	return angle;
}

bool IS_RIGHT_KEY_PRESSED = false;
bool IS_LEFT_KEY_PRESSED = false;
bool IS_UP_KEY_PRESSED = false;
bool IS_DOWN_KEY_PRESSED = false;

Shape_factory factory;

//creating player
Shape player = factory.create_shape(Constants::PLAYER, Vertex(8.0, -6.0));

//////////////////////////////////////////
//           creating map walls         //
//////////////////////////////////////////
//map 1
Shape wall1_1 = factory.create_shape(Constants::WALL, Vertex(4.5, 4.0), 10.0, 0.5);
Shape wall1_2 = factory.create_shape(Constants::WALL, Vertex(-10.0, 5.0), 0.5, 5.0);
Shape wall1_3 = factory.create_shape(Constants::WALL, Vertex(-3.35, 10.0), 3.5, 0.5);
Shape wall1_4 = factory.create_shape(Constants::WALL, Vertex(-1.0, 9.0), 7.0, 0.5);
Shape wall1_5 = factory.create_shape(Constants::WALL, Vertex(-0.85, 9.0), 0.5, 7.0);
Shape wall1_6 = factory.create_shape(Constants::WALL, Vertex(-8.0, -8.0), 3.0, 0.5);
Shape wall1_7 = factory.create_shape(Constants::WALL, Vertex(-8.35, -6.0), 0.5, 8.35);
Shape wall1_9 = factory.create_shape(Constants::WALL, Vertex(-5.5, 2.0), 8.0, 0.5);
Shape wall1_10 = factory.create_shape(Constants::WALL, Vertex(6.5, 7.0), 7.0, 0.5);
Shape wall1_11 = factory.create_shape(Constants::WALL, Vertex(6.5, 0.0), 0.5, 6.5);
Shape wall1_12 = factory.create_shape(Constants::WALL, Vertex(0.0, 0.0), 6.5, 0.5);
Shape wall1_13 = factory.create_shape(Constants::WALL, Vertex(0.5, 0.0), 0.5, 4.0);
Shape wall1_14 = factory.create_shape(Constants::WALL, Vertex(-10.0, 10.0), 0.2, 22.0);
Shape wall1_15 = factory.create_shape(Constants::WALL, Vertex(-10.0, 10.0), 22.0, 0.2);
Shape wall1_16 = factory.create_shape(Constants::WALL, Vertex(-10.0, -9.8), 0.2, 22.0);
Shape wall1_17 = factory.create_shape(Constants::WALL, Vertex(9.8, 10.0), 22.0, 0.2);

vector<Shape> map1{
	wall1_1,
	wall1_2,
	wall1_3,
	wall1_4,
	wall1_5,
	wall1_6,
	wall1_7,
	wall1_9,
	wall1_10,
	wall1_11,
	wall1_12,
	wall1_13,
	wall1_14,
	wall1_15,
	wall1_16,
	wall1_17
};
//map 2
Shape wall2_1 = factory.create_shape(Constants::WALL, Vertex(190.0, 0.0), 0.5, 4.0);
Shape wall2_2 = factory.create_shape(Constants::WALL, Vertex(194.0, 4.0), 9.0, 0.5);
Shape wall2_3 = factory.create_shape(Constants::WALL, Vertex(194.0, 10.0), 4.0, 0.5);
Shape wall2_4 = factory.create_shape(Constants::WALL, Vertex(194.0, 7.0), 0.5, 6.0);
Shape wall2_5 = factory.create_shape(Constants::WALL, Vertex(202.0, 10.0), 6.0, 0.5);
Shape wall2_6 = factory.create_shape(Constants::WALL, Vertex(202.0, 6.0), 0.5, 6.0);
Shape wall2_7 = factory.create_shape(Constants::WALL, Vertex(207.0, 10.0), 2.0, 0.5);
Shape wall2_8 = factory.create_shape(Constants::WALL, Vertex(202.0, 1.0), 0.5, 8.0);
Shape wall2_9 = factory.create_shape(Constants::WALL, Vertex(204.0, -6.0), 0.5, 6.0);
Shape wall2_10 = factory.create_shape(Constants::WALL, Vertex(197.0, -3.0), 0.5, 7.0);
Shape wall2_11 = factory.create_shape(Constants::WALL, Vertex(200.0, -3.0), 7.0, 0.5);
Shape wall2_12 = factory.create_shape(Constants::WALL, Vertex(190.0, 10.0), 20.0, 0.2);
Shape wall2_13 = factory.create_shape(Constants::WALL, Vertex(190.0, 10.0), 0.2, 20.0);
Shape wall2_14 = factory.create_shape(Constants::WALL, Vertex(209.8, 10.0), 20.0, 0.2);
Shape wall2_15 = factory.create_shape(Constants::WALL, Vertex(190.0, -9.8), 0.2, 20.0);

vector<Shape> map2{
	wall2_1,
	wall2_2,
	wall2_3,
	wall2_4,
	wall2_5,
	wall2_6,
	wall2_7,
	wall2_8,
	wall2_9,
	wall2_10,
	wall2_11,
	wall2_12,
	wall2_13,
	wall2_14,
	wall2_15
};

//map 3
Shape wall3_1 = factory.create_shape(Constants::WALL, Vertex(290.0, 0.5), 0.5, 8.0);
Shape wall3_2 = factory.create_shape(Constants::WALL, Vertex(294.0, 0.5), 7.0, 0.5);
Shape wall3_3 = factory.create_shape(Constants::WALL, Vertex(293.0, 8.0), 0.5, 7.0);
Shape wall3_4 = factory.create_shape(Constants::WALL, Vertex(295.0, 8.0), 4.0, 0.5);
Shape wall3_5 = factory.create_shape(Constants::WALL, Vertex(300.0, 6.0), 6.0, 0.5);
Shape wall3_6 = factory.create_shape(Constants::WALL, Vertex(300.0, 0.5), 0.5, 10.0);
Shape wall3_7 = factory.create_shape(Constants::WALL, Vertex(304.0, 10.0), 4.0, 0.5);
Shape wall3_8 = factory.create_shape(Constants::WALL, Vertex(307.0, 6.5), 0.5, 3.0);
Shape wall3_9 = factory.create_shape(Constants::WALL, Vertex(307.0, -6.0), 0.5, 3.0);
Shape wall3_10 = factory.create_shape(Constants::WALL, Vertex(304.0, -4.0), 6.0, 0.5);
Shape wall3_11 = factory.create_shape(Constants::WALL, Vertex(297.0, -7.0), 0.5, 7.0);
Shape wall3_12 = factory.create_shape(Constants::WALL, Vertex(292.0, -8.0), 2.0, 0.5);
Shape wall3_13 = factory.create_shape(Constants::WALL, Vertex(298.0, -3.0), 0.5, 3.0);
Shape wall3_14 = factory.create_shape(Constants::WALL, Vertex(290.0, 10.0), 20.0, 0.2);
Shape wall3_15 = factory.create_shape(Constants::WALL, Vertex(290.0, 10.0), 0.2, 20.0);
Shape wall3_17 = factory.create_shape(Constants::WALL, Vertex(290.0, -9.8), 0.2, 20.0);
Shape wall3_18 = factory.create_shape(Constants::WALL, Vertex(309.8, 9.8), 20.0, 0.2);

vector<Shape> map3{
	wall3_1,
	wall3_2,
	wall3_3,
	wall3_4,
	wall3_5,
	wall3_6,
	wall3_7,
	wall3_8,
	wall3_9,
	wall3_10,
	wall3_11,
	wall3_12,
	wall3_13,
	wall3_14,
	wall3_15,
	wall3_17,
	wall3_18
};

//official walls vector, which will be set once the player chooses the phase
vector<Shape> map;

//////////////////////////////////////////
//           creating enemies           //
//////////////////////////////////////////

//enemies1
Shape enemy1_1 = factory.create_shape(Constants::ENEMY, Vertex(-8.0, 7.0));
Shape enemy1_2 = factory.create_shape(Constants::ENEMY, Vertex(-2.0, -2.0));
Shape enemy1_3 = factory.create_shape(Constants::ENEMY, Vertex(3.0, 4.0));
Shape enemy1_4 = factory.create_shape(Constants::ENEMY, Vertex(2.0, -6.0));

vector<Shape> enemies1{
	enemy1_1,
	enemy1_2,
	enemy1_3,
	enemy1_4
};

//enemies2
Shape enemy2_1 = factory.create_shape(Constants::ENEMY, Vertex(192.5, 7.0));
Shape enemy2_2 = factory.create_shape(Constants::ENEMY, Vertex(192.0, -4.0));
Shape enemy2_3 = factory.create_shape(Constants::ENEMY, Vertex(200.0, 3.0));
Shape enemy2_4 = factory.create_shape(Constants::ENEMY, Vertex(206.0, -2.0));
Shape enemy2_5 = factory.create_shape(Constants::ENEMY, Vertex(196.0, -8.0));

vector<Shape> enemies2{
	enemy2_1,
	enemy2_2,
	enemy2_3,
	enemy2_4,
	enemy2_5
};

//enemies3
Shape enemy3_1 = factory.create_shape(Constants::ENEMY, Vertex(292.0, -5.0));
Shape enemy3_2 = factory.create_shape(Constants::ENEMY, Vertex(306.0, -2.0));
Shape enemy3_3 = factory.create_shape(Constants::ENEMY, Vertex(303.0, 1.0));
Shape enemy3_4 = factory.create_shape(Constants::ENEMY, Vertex(300.0, -6.0));
Shape enemy3_5 = factory.create_shape(Constants::ENEMY, Vertex(292.0, 2.0));
Shape enemy3_6 = factory.create_shape(Constants::ENEMY, Vertex(303.0, 7.0));

vector<Shape> enemies3{
	enemy3_1,
	enemy3_2,
	enemy3_3,
	enemy3_4,
	enemy3_5,
	enemy3_6
};

vector<Shape> enemies;

//////////////////////////////////////////
//           creating hostages          //
//////////////////////////////////////////

//hostages1
Shape hostage1_1 = factory.create_shape(Constants::HOSTAGE, Vertex(-9.3, 6.0));
Shape hostage1_2 = factory.create_shape(Constants::HOSTAGE, Vertex(-8.8, 6.0));

vector<Shape> hostages1{
	hostage1_1,
	hostage1_2
};

//hostages2
Shape hostage2_1 = factory.create_shape(Constants::HOSTAGE, Vertex(197.3, 8.0));
Shape hostage2_2 = factory.create_shape(Constants::HOSTAGE, Vertex(198.0, 8.0));

vector<Shape> hostages2{
	hostage2_1,
	hostage2_2
};

//hostages3
Shape hostage3_1 = factory.create_shape(Constants::HOSTAGE, Vertex(291.3, 4.8));
Shape hostage3_2 = factory.create_shape(Constants::HOSTAGE, Vertex(292.0, 4.8));

vector<Shape> hostages3{
	hostage3_1,
	hostage3_2
};

vector<Shape> hostages;

//////////////////////////////////////////
//         creating enemy's FoV         //
// ps: the enemy FoVs must be created   //
//   in the same sequence as enemies    //
//////////////////////////////////////////

//enemy_fov1
Shape enemy_fov1_1 = factory.create_shape(Constants::ENEMY_FOV, enemy1_1.vertexes[0], enemy1_1.angle);
Shape enemy_fov1_2 = factory.create_shape(Constants::ENEMY_FOV, enemy1_2.vertexes[0], enemy1_2.angle);
Shape enemy_fov1_3 = factory.create_shape(Constants::ENEMY_FOV, enemy1_3.vertexes[0], enemy1_3.angle);
Shape enemy_fov1_4 = factory.create_shape(Constants::ENEMY_FOV, enemy1_4.vertexes[0], enemy1_4.angle);

vector<Shape> enemy_fov1{
	enemy_fov1_1,
	enemy_fov1_2,
	enemy_fov1_3,
	enemy_fov1_4
};

//enemy_fov2
Shape enemy_fov2_1 = factory.create_shape(Constants::ENEMY_FOV, enemy2_1.vertexes[0], enemy2_1.angle);
Shape enemy_fov2_2 = factory.create_shape(Constants::ENEMY_FOV, enemy2_2.vertexes[0], enemy2_2.angle);
Shape enemy_fov2_3 = factory.create_shape(Constants::ENEMY_FOV, enemy2_3.vertexes[0], enemy2_3.angle);
Shape enemy_fov2_4 = factory.create_shape(Constants::ENEMY_FOV, enemy2_4.vertexes[0], enemy2_4.angle);
Shape enemy_fov2_5 = factory.create_shape(Constants::ENEMY_FOV, enemy2_5.vertexes[0], enemy2_5.angle);

vector<Shape> enemy_fov2{
	enemy_fov2_1,
	enemy_fov2_2,
	enemy_fov2_3,
	enemy_fov2_4,
	enemy_fov2_5
};

//enemy_fov3
Shape enemy_fov3_1 = factory.create_shape(Constants::ENEMY_FOV, enemy3_1.vertexes[0], enemy3_1.angle);
Shape enemy_fov3_2 = factory.create_shape(Constants::ENEMY_FOV, enemy3_2.vertexes[0], enemy3_2.angle);
Shape enemy_fov3_3 = factory.create_shape(Constants::ENEMY_FOV, enemy3_3.vertexes[0], enemy3_3.angle);
Shape enemy_fov3_4 = factory.create_shape(Constants::ENEMY_FOV, enemy3_4.vertexes[0], enemy3_4.angle);
Shape enemy_fov3_5 = factory.create_shape(Constants::ENEMY_FOV, enemy3_5.vertexes[0], enemy3_5.angle);
Shape enemy_fov3_6 = factory.create_shape(Constants::ENEMY_FOV, enemy3_6.vertexes[0], enemy3_6.angle);

vector<Shape> enemy_fov3{
	enemy_fov3_1,
	enemy_fov3_2,
	enemy_fov3_3,
	enemy_fov3_4,
	enemy_fov3_5,
	enemy_fov3_6
};

vector<Shape> enemy_fov;

//////////////////////////////////////////
//           creating powerups          //
//////////////////////////////////////////

//powerup1
Shape powerup1_1 = factory.create_shape(Constants::POWERUP, Vertex(8.0, -4.0));
Shape powerup1_2 = factory.create_shape(Constants::POWERUP, Vertex(-2.0, 3.0));

vector<Shape> power_ups1{
	powerup1_1,
	powerup1_2
};

//powerup2
Shape powerup2_1 = factory.create_shape(Constants::POWERUP, Vertex(199.0, -4.0));
Shape powerup2_2 = factory.create_shape(Constants::POWERUP, Vertex(206.0, -1.0));

vector<Shape> power_ups2{
	powerup2_1,
	powerup2_2
};

//powerup3
Shape powerup3_1 = factory.create_shape(Constants::POWERUP, Vertex(303.0, -4.0));
Shape powerup3_2 = factory.create_shape(Constants::POWERUP, Vertex(295.0, -1.0));

vector<Shape> power_ups3{
	powerup3_1,
	powerup3_2
};

vector<Shape> power_ups;

//////////////////////////////////////////
//            bullets vector            //
//////////////////////////////////////////

vector<Shape> bullets{

};

void writeOnScreen(char palavra[], float posX, float posY) {

	//Cor da fonte
	glColor3ub(255, 255, 255);
	//Posição da palavra
	glRasterPos3f(posX, posY, 0.0);

	//Uso do "for" para escrever mais de um caracter
	for (int i = 0; i < strlen(palavra); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, palavra[i]);

}



vector<float> check_hud_color() {
	switch (current_powerup) {
	case NONE: {
		vector<float> ret{ 1.0f, 1.0f, 0.5f };
		return ret;
		break;
	}
	case DRILL: {
		return DRILL_BULLET_COLOR;
		break;
	}
	case EXPANSIVE: {
		return EXPANSIVE_BULLET_COLOR;
		break;
	}
	case BLAST: {
		return BLAST_BULLET_COLOR;
		break;
	}
	}
}

void define_powerup() {

	current_powerup = (rand() % 3) + 1;

	switch (current_powerup)
	{
	case DRILL:
		powerup_bullets = 3;
		break;
	case EXPANSIVE:
		powerup_bullets = 5;
		break;
	case BLAST:
		powerup_bullets = 2;
		break;
	}
}

void draw_hud() {
	//draw elements to represent player health and magazine bullets remaining

	//float variable to define multiplicity of the position according to the map selected
	float map_addition = -7;
	if (menu_door_selected == 2) {
		map_addition = 193;
	}
	else if (menu_door_selected == 3) {
		map_addition = 293;
	}
	//draw HUD box
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(6.0 + map_addition, -8.0);
	glVertex2f(9.9 + map_addition, -8.0);
	glVertex2f(9.9 + map_addition, -9.9);
	glVertex2f(6.0 + map_addition, -9.9);
	glEnd();

	//health
	if (player.health < 1) {
		//no drawing
	}
	else if (player.health < 2) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.6);
		glVertex2f(8.5 + map_addition, -9.6);
		glEnd();
	}
	else if (player.health < 3) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.6);
		glVertex2f(8.5 + map_addition, -9.6);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -8.9);
		glVertex2f(9.5 + map_addition, -8.9);
		glVertex2f(9.5 + map_addition, -9.2);
		glVertex2f(8.5 + map_addition, -9.2);
		glEnd();
	}
	else if (player.health < 4) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.3);
		glVertex2f(9.5 + map_addition, -9.6);
		glVertex2f(8.5 + map_addition, -9.6);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -8.9);
		glVertex2f(9.5 + map_addition, -8.9);
		glVertex2f(9.5 + map_addition, -9.2);
		glVertex2f(8.5 + map_addition, -9.2);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5 + map_addition, -8.5);
		glVertex2f(9.5 + map_addition, -8.5);
		glVertex2f(9.5 + map_addition, -8.8);
		glVertex2f(8.5 + map_addition, -8.8);
		glEnd();
	}

	//player remaining bullets
	vector<float> color = check_hud_color();
	int bullets_remaining;

	//checking which magazine should be drawn
	if (current_powerup == NONE)
		bullets_remaining = magazine;
	else
		bullets_remaining = powerup_bullets;

	if (bullets_remaining == 0) {
		//no drawing
	}
	if (bullets_remaining > 0) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.2 + map_addition, -8.2);
		glVertex2f(6.5 + map_addition, -8.2);
		glVertex2f(6.5 + map_addition, -8.5);
		glVertex2f(6.2 + map_addition, -8.5);
		glEnd();
	}
	if (bullets_remaining > 1) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.6 + map_addition, -8.2);
		glVertex2f(6.9 + map_addition, -8.2);
		glVertex2f(6.9 + map_addition, -8.5);
		glVertex2f(6.6 + map_addition, -8.5);
		glEnd();
	}
	if (bullets_remaining > 2) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.0 + map_addition, -8.2);
		glVertex2f(7.3 + map_addition, -8.2);
		glVertex2f(7.3 + map_addition, -8.5);
		glVertex2f(7.0 + map_addition, -8.5);
		glEnd();
	}

	if (bullets_remaining > 3) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.4 + map_addition, -8.2);
		glVertex2f(7.7 + map_addition, -8.2);
		glVertex2f(7.7 + map_addition, -8.5);
		glVertex2f(7.4 + map_addition, -8.5);
		glEnd();
	}
	if (bullets_remaining > 4) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.8 + map_addition, -8.2);
		glVertex2f(8.1 + map_addition, -8.2);
		glVertex2f(8.1 + map_addition, -8.5);
		glVertex2f(7.8 + map_addition, -8.5);
		glEnd();
	}
	if (bullets_remaining > 5) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.2 + map_addition, -8.6);
		glVertex2f(6.5 + map_addition, -8.6);
		glVertex2f(6.5 + map_addition, -8.9);
		glVertex2f(6.2 + map_addition, -8.9);
		glEnd();
	}
	if (bullets_remaining > 6) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.6 + map_addition, -8.6);
		glVertex2f(6.9 + map_addition, -8.6);
		glVertex2f(6.9 + map_addition, -8.9);
		glVertex2f(6.6 + map_addition, -8.9);
		glEnd();
	}
	if (bullets_remaining > 7) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.0 + map_addition, -8.6);
		glVertex2f(7.3 + map_addition, -8.6);
		glVertex2f(7.3 + map_addition, -8.9);
		glVertex2f(7.0 + map_addition, -8.9);
		glEnd();
	}
	if (bullets_remaining > 8) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.4 + map_addition, -8.6);
		glVertex2f(7.7 + map_addition, -8.6);
		glVertex2f(7.7 + map_addition, -8.9);
		glVertex2f(7.4 + map_addition, -8.9);
		glEnd();
	}
	if (bullets_remaining > 9) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.8 + map_addition, -8.6);
		glVertex2f(8.1 + map_addition, -8.6);
		glVertex2f(8.1 + map_addition, -8.9);
		glVertex2f(7.8 + map_addition, -8.9);
		glEnd();
	}
	if (bullets_remaining > 10) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.2 + map_addition, -9.0);
		glVertex2f(6.5 + map_addition, -9.0);
		glVertex2f(6.5 + map_addition, -9.4);
		glVertex2f(6.2 + map_addition, -9.4);
		glEnd();
	}
	if (bullets_remaining > 11) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(6.6 + map_addition, -9.0);
		glVertex2f(6.9 + map_addition, -9.0);
		glVertex2f(6.9 + map_addition, -9.4);
		glVertex2f(6.6 + map_addition, -9.4);
		glEnd();
	}
	if (bullets_remaining > 12) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.0 + map_addition, -9.0);
		glVertex2f(7.3 + map_addition, -9.0);
		glVertex2f(7.3 + map_addition, -9.4);
		glVertex2f(7.0 + map_addition, -9.4);
		glEnd();
	}
	if (bullets_remaining > 13) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.4 + map_addition, -9.0);
		glVertex2f(7.7 + map_addition, -9.0);
		glVertex2f(7.7 + map_addition, -9.4);
		glVertex2f(7.4 + map_addition, -9.4);
		glEnd();
	}
	if (bullets_remaining > 14) {
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		glVertex2f(7.8 + map_addition, -9.0);
		glVertex2f(8.1 + map_addition, -9.0);
		glVertex2f(8.1 + map_addition, -9.4);
		glVertex2f(7.8 + map_addition, -9.4);
		glEnd();
	}
}

void draw_elements() {
	//drawing player
	player.draw();

	//drawing walls
	for (int i = 0; i < map.size(); i++) {
		map[i].draw();
	}

	//drawing enemies and their FoVs
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].health > 0) {
			enemies[i].draw();
			enemy_fov[i].draw();
		}
	}

	//drawing hostages
	for (int i = 0; i < hostages.size(); i++) {
		hostages[i].draw();
	}

	//drawing power_ups
	for (int i = 0; i < power_ups.size(); i++) {
		power_ups[i].draw();
	}

	//drawing bullets
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw();
	}

	//drawing additional bullets
	for (int i = 0; i < additional_bullets.size(); i++) {
		additional_bullets[i].draw();
	}

	draw_hud();

}


void go_to_menu() {
	gluOrtho2D(-100.0, -90.0, -100.0, -90.0);

	//write on menu
	writeOnScreen("Comandos:", -94.0, -95.0);
	writeOnScreen("W, A, S, D - Movimentação", -94.0, -95.3);
	writeOnScreen("Q, E - Rotacao", -94.0, -95.6);
	writeOnScreen("Clique mouse - Atirar", -94.0, -95.9);
	writeOnScreen("Barra de espaco - explodir (balas especiais)", -94.0, -96.2);
	writeOnScreen("Selecione a fase:", -96.5, -91.0);

	writeOnScreen("Municao cinza - Tiro penetrante", -99.0, -95.0);
	writeOnScreen("Municao verde - Tiro explosivo", -99.0, -95.3);
	writeOnScreen("Municao azul  - Tiro dividido", -99.0, -95.6);

	//move player to menu
	if (!player_in_menu) {
		player.move_shape_to(-95, -95);
		player_in_menu = true;
	}
	draw_elements();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-99.0, -92.5);
	glVertex2f(-97.0, -92.5);
	glVertex2f(-97.0, -91.5);
	glVertex2f(-99.0, -91.5);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-96.5, -92.5);
	glVertex2f(-94.5, -92.5);
	glVertex2f(-94.5, -91.5);
	glVertex2f(-96.5, -91.5);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-94.0, -92.5);
	glVertex2f(-92.0, -92.5);
	glVertex2f(-92.0, -91.5);
	glVertex2f(-94.0, -91.5);
	glEnd();
	glutSwapBuffers();

	if (menu_door_selected != 0) {
		is_in_menu = false;
		switch (menu_door_selected)
		{
		case 1:
			map = map1;
			enemies = enemies1;
			enemy_fov = enemy_fov1;
			hostages = hostages1;
			power_ups = power_ups1;
			enemy_velocity = 35;
			player.move_shape_to(8.0, -6.0);
			player.rotate(player_angle);
			break;
		case 2:
			map = map2;
			enemy_fov = enemy_fov2;
			enemies = enemies2;
			hostages = hostages2;
			power_ups = power_ups2;
			enemy_velocity = 30;
			player.move_shape_to(191.0, -8.5);
			player.rotate(player_angle);
			break;
		case 3:
			map = map3;
			enemies = enemies3;
			enemy_fov = enemy_fov3;
			hostages = hostages3;
			power_ups = power_ups3;
			enemy_velocity = 25;
			player.move_shape_to(309.0, -8.5);
			player.rotate(player_angle);
			break;
		}
	}

}

void detect_player_menu_door_collision() {

	//detecting menu option collision
	if (player.vertexes[0].pos_x >= menu_door_1[0].pos_x && player.vertexes[0].pos_x <= menu_door_1[1].pos_x) {
		if (player.vertexes[0].pos_y <= menu_door_1[2].pos_y && player.vertexes[0].pos_y >= menu_door_1[0].pos_y) {
			//player colliding with door 1
			menu_door_selected = 1;
		}
	}

	if (player.vertexes[0].pos_x >= menu_door_2[0].pos_x && player.vertexes[0].pos_x <= menu_door_2[1].pos_x) {
		if (player.vertexes[0].pos_y <= menu_door_2[2].pos_y && player.vertexes[0].pos_y >= menu_door_2[0].pos_y) {
			//player colliding with door 2
			menu_door_selected = 2;
		}
	}

	if (player.vertexes[0].pos_x >= menu_door_3[0].pos_x && player.vertexes[0].pos_x <= menu_door_3[1].pos_x) {
		if (player.vertexes[0].pos_y <= menu_door_3[2].pos_y && player.vertexes[0].pos_y >= menu_door_3[0].pos_y) {
			//player colliding with door 3
			menu_door_selected = 3;
		}
	}
}

void DesenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (is_in_menu) {
		go_to_menu();
	}
	else {

		switch (menu_door_selected)
		{
		case 1:
			gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
			break;
		case 2:
			gluOrtho2D(190.0, 210.0, -10.0, 10.0);
			break;
		case 3:
			gluOrtho2D(290.0, 310.0, -10.0, 10.0);
			break;
		}

		draw_elements();
		glutSwapBuffers();


		//testing end game conditions

		//player dead
		if (player.health <= 0) {
			MessageBox(NULL, (LPCWSTR)L"GAME OVER\nSua vida foi reduzida para 0", (LPCWSTR)L"GAME OVER", MB_OK);
			glutLeaveMainLoop();
		}

		//player reached hostage
		for (int i = 0; i < hostages.size(); i++) {
			if (player.is_colliding_with(hostages[i])) {
				MessageBox(NULL, (LPCWSTR)L"VOCÊ VENCEU!\nVocê resgatou o(s) refém(ns)", (LPCWSTR)L"GAME OVER", MB_OK);
				glutLeaveMainLoop();
			}
		}

		//all enemies are dead
		bool all_enemies_dead = true;
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].health > 0) {
				all_enemies_dead = false;
			}
		}

		if (all_enemies_dead) {
			MessageBox(NULL, (LPCWSTR)L"VOCÊ VENCEU!\nVocê eliminou todos os inimigos", (LPCWSTR)L"GAME OVER", MB_OK);
			glutLeaveMainLoop();
		}

		//hostage dead
		for (int i = 0; i < hostages.size(); i++) {
			if (hostages[i].health <= 0) {
				MessageBox(NULL, (LPCWSTR)L"GAME OVER\nUm refém foi morto", (LPCWSTR)L"GAME OVER", MB_OK);
				glutLeaveMainLoop();
			}
		}
	}

}


// Inicializa aspectos do rendering
void Inicio(void)
{
	glClearColor(0.7f, 0.5f, 0.3f, 50.0f);  // cor de fundo da janela
}

void check_bullet_collision() {

	using std::swap;

	for (int i = 0; i < bullets.size(); i++) {
		bool bullet_erased = false;
		//detecting enemy hit
		for (int j = 0; j < enemies.size(); j++) {
			if (bullets[i].is_colliding_with(enemies[j]) && enemies[j].health>0) {
				swap(bullets[i], bullets.back());
				bullets.pop_back();
				enemies[j].health -= 1;

				bullet_erased = true;
				break;
			}
		}

		//detecting wall hit only if the bullet didn't collided with enemy
		if (bullet_erased) {
			continue;
		}
		else {
			for (int j = 0; j < map.size(); j++) {
				if (bullets[i].is_colliding_with(map[j])) {
					if (bullets[i].bullet_type == DRILL) {
						break;
					}
					else {
						swap(bullets[i], bullets.back());
						bullets.pop_back();

						bullet_erased = true;
						break;
					}
				}
			}
		}

		//detecting hostage hit
		if (bullet_erased) {
			continue;
		}
		else {
			for (int j = 0; j < hostages.size(); j++) {
				if (bullets[i].is_colliding_with(hostages[j])) {
					hostages[j].health -= 1;

					bullet_erased = true;
					break;
				}
			}
		}
	}

	//additional bullets
	for (int i = 0; i < additional_bullets.size(); i++) {
		bool bullet_erased = false;
		//detecting enemy hit
		for (int j = 0; j < enemies.size(); j++) {
			if (additional_bullets[i].is_colliding_with(enemies[j]) && enemies[j].health>0) {
				swap(additional_bullets[i], additional_bullets.back());
				additional_bullets.pop_back();
				enemies[j].health -= 1;

				bullet_erased = true;
				break;
			}
		}

		//detecting wall hit only if the bullet didn't collided with enemy
		if (bullet_erased) {
			continue;
		}
		else {
			for (int j = 0; j < map.size(); j++) {
				if (additional_bullets[i].is_colliding_with(map[j])) {
					if (additional_bullets[i].bullet_type == DRILL) {
						break;
					}
					else {
						swap(additional_bullets[i], additional_bullets.back());
						additional_bullets.pop_back();

						bullet_erased = true;
						break;
					}
				}
			}
		}

		//detecting hostage hit
		if (bullet_erased) {
			continue;
		}
		else {
			for (int j = 0; j < hostages.size(); j++) {
				if (additional_bullets[i].is_colliding_with(hostages[j])) {
					hostages[j].health -= 1;

					bullet_erased = true;
					break;
				}
			}
		}
	}
}

//ja a função de tratamento de teclas normais exige um unsigned char e dois ints
void teclasNormais(unsigned char tecla, int x, int y) {

	switch (toupper(tecla))
	{
	case 'W':
		IS_UP_KEY_PRESSED = true;
		break;
	case 'S':
		IS_DOWN_KEY_PRESSED = true;
		break;
	case 'A':
		IS_LEFT_KEY_PRESSED = true;
		break;
	case 'D':
		IS_RIGHT_KEY_PRESSED = true;
		break;
	case 'Q':
		player.rotate(0.2);
		player_angle += 0.2;
		break;
	case 'E':
		player.rotate(-0.2);
		player_angle -= 0.2;
		break;
	case ' ': //case spacebar, explode all explosive or expansive bullets
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].bullet_type == BLAST) {
				bullets[i].explode_bullet();
				glutPostRedisplay();
				check_bullet_collision();
			}else if (bullets[i].bullet_type == EXPANSIVE) {
				bullets[i].bullet_type = NONE;
				additional_bullets.push_back(factory.create_shape(Constants::BULLET, bullets[i].vertexes[0], player_angle + 0.7, NONE, true));
				additional_bullets.push_back(factory.create_shape(Constants::BULLET, bullets[i].vertexes[0], player_angle - 0.7, NONE, true));
			}
		}
	}

}

void mouseMotion(int x, int y) {
	//position of the mouse related to the player pointing vertex
	int mouse_pos_x = (x - (glutGet(GLUT_WINDOW_WIDTH) / 2)) - (player.horizontal_middle * 100 / 2);
	int mouse_pos_y = (((glutGet(GLUT_WINDOW_HEIGHT) / 2) - y)) - ((player.vertical_middle + PLAYER_HEIGHT / 2) * 100 / 2);

	double angle = get_mouse_angle(mouse_pos_x, mouse_pos_y);
	//cout << "angle: " << angle << endl;

	previous_mouse_x_position = mouse_pos_x;
	previous_mouse_y_position = mouse_pos_y;

	//player.rotate(angle);
	//glutPostRedisplay();
}

void teclasNormaisUp(unsigned char tecla, int x, int y) {

	if (toupper(tecla) == 'D') {
		IS_RIGHT_KEY_PRESSED = false;
	}
	else {
		if (toupper(tecla) == 'A') {
			IS_LEFT_KEY_PRESSED = false;
		}
		else {
			if (toupper(tecla) == 'W') {
				IS_UP_KEY_PRESSED = false;
			}
			else {
				if (toupper(tecla) == 'S') {
					IS_DOWN_KEY_PRESSED = false;
				}
			}
		}
	}

}

void move_bullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].move_bullet();
		glutPostRedisplay();
	}
	//moving additional bullets from expansive bullets
	for (int i = 0; i < additional_bullets.size(); i++) {
		additional_bullets[i].move_bullet();
		glutPostRedisplay();
	}

}

void player_movement(int value) {

	using std::swap;

	if (IS_DOWN_KEY_PRESSED) {

		Shape teste = player.simulate_translation(0, PLAYER_MOVEMENT_TIC, 0, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0; i < map.size(); i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
		}

		//testing enemy and FoV collision
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
					player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
					Sleep(50);
					player.health--;
					player.translate(PLAYER_MOVEMENT_TIC * 3, 0, 0, 0);
					IS_UP_KEY_PRESSED = false;
					IS_DOWN_KEY_PRESSED = false;
					IS_LEFT_KEY_PRESSED = false;
					IS_RIGHT_KEY_PRESSED = false;
				}
			}
		}

		//detecting power up collision
		for (int i = 0; i < power_ups.size(); i++) {
			if (player.is_colliding_with(power_ups[i])) {
				swap(power_ups[i], power_ups.back());
				power_ups.pop_back();
				define_powerup();
			}
		}

		//detecting menu door collision
		detect_player_menu_door_collision();

	}

	if (IS_UP_KEY_PRESSED) {
		Shape teste = player.simulate_translation(PLAYER_MOVEMENT_TIC, 0, 0, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0; i < map.size(); i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
		}

		//testing enemy and FoV collision
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
					player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
					Sleep(50);
					player.health--;
					player.translate(0, PLAYER_MOVEMENT_TIC * 3, 0, 0);
					IS_UP_KEY_PRESSED = false;
					IS_DOWN_KEY_PRESSED = false;
					IS_LEFT_KEY_PRESSED = false;
					IS_RIGHT_KEY_PRESSED = false;
				}
			}
		}

		//detecting power up collision
		for (int i = 0; i < power_ups.size(); i++) {
			if (player.is_colliding_with(power_ups[i])) {
				swap(power_ups[i], power_ups.back());
				power_ups.pop_back();
				define_powerup();
			}
		}

		//detecting menu door collision
		detect_player_menu_door_collision();
	}

	if (IS_LEFT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, PLAYER_MOVEMENT_TIC, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0; i < map.size(); i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
		}

		//testing enemy and FoV collision
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
					player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
					Sleep(50);
					player.health--;
					player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC * 3);
					IS_UP_KEY_PRESSED = false;
					IS_DOWN_KEY_PRESSED = false;
					IS_LEFT_KEY_PRESSED = false;
					IS_RIGHT_KEY_PRESSED = false;
				}
			}
		}
		//detecting power up collision
		for (int i = 0; i < power_ups.size(); i++) {
			if (player.is_colliding_with(power_ups[i])) {
				swap(power_ups[i], power_ups.back());
				power_ups.pop_back();
				define_powerup();
			}
		}

		//detecting menu door collision
		detect_player_menu_door_collision();
	}

	if (IS_RIGHT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, 0, PLAYER_MOVEMENT_TIC);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0; i < map.size(); i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
		}

		//testing enemy and FoV collision
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
					player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
					Sleep(50);
					player.health--;
					player.translate(0, 0, PLAYER_MOVEMENT_TIC * 3, 0);
					IS_UP_KEY_PRESSED = false;
					IS_DOWN_KEY_PRESSED = false;
					IS_LEFT_KEY_PRESSED = false;
					IS_RIGHT_KEY_PRESSED = false;
				}
			}
		}

		//detecting power up collision
		for (int i = 0; i < power_ups.size(); i++) {
			if (player.is_colliding_with(power_ups[i])) {
				swap(power_ups[i], power_ups.back());
				power_ups.pop_back();
				define_powerup();
			}
		}

		//detecting menu door collision
		detect_player_menu_door_collision();
	}

	move_bullets();
	check_bullet_collision();

	glutPostRedisplay();
	glutTimerFunc(50, player_movement, 1);

}

void enimies_movement(int valor) {
	switch (menu_door_selected) {
	case 1:
		for (int i = 0; i < enemy_fov.size(); i++) {
			if (enemy_fov[i].vertexes[0].pos_x + ENEMY_MOVEMENT_TIC >= -9.8 && direction1[i] == 1) {
				enemies[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				enemy_fov[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				if (enemy_fov[i].vertexes[0].pos_x <= -9.8) {
					direction1[i] = 2;
				}
			}
			else {
				direction1[i] = 2;
			}
			if (enemy_fov[i].vertexes[1].pos_x + ENEMY_MOVEMENT_TIC <= 9.8 && direction1[i] == 2) {
				enemies[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				enemy_fov[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				if (enemy_fov[i].vertexes[1].pos_x >= 9.8) {
					direction1[i] = 1;
				}
			}
			else {
				direction1[i] = 1;
			}
		}
		break;
	case 2:
		for (int i = 0; i < enemy_fov.size(); i++) {
			if (enemy_fov[i].vertexes[0].pos_x + ENEMY_MOVEMENT_TIC >= 190.2 && direction2[i] == 1) {
				enemies[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				enemy_fov[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				if (enemy_fov[i].vertexes[0].pos_x <= 190.2) {
					direction2[i] = 2;
				}
			}
			else {
				direction2[i] = 2;
			}
			if (enemy_fov[i].vertexes[1].pos_x + ENEMY_MOVEMENT_TIC <= 209.8 && direction2[i] == 2) {
				enemies[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				enemy_fov[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				if (enemy_fov[i].vertexes[1].pos_x >= 209.8) {
					direction2[i] = 1;
				}
			}
			else {
				direction2[i] = 1;
			}
		}
		break;
	case 3:
		for (int i = 0; i < enemy_fov.size(); i++) {
			if (enemy_fov[i].vertexes[0].pos_x + ENEMY_MOVEMENT_TIC >= 290.2 && direction3[i] == 1) {
				enemies[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				enemy_fov[i].translate(0, 0, ENEMY_MOVEMENT_TIC, 0);
				if (enemy_fov[i].vertexes[0].pos_x <= 290.2) {
					direction3[i] = 2;
				}
			}
			else {
				direction3[i] = 2;
			}
			if (enemy_fov[i].vertexes[1].pos_x + ENEMY_MOVEMENT_TIC <= 309.8 && direction3[i] == 2) {
				enemies[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				enemy_fov[i].translate(0, 0, 0, ENEMY_MOVEMENT_TIC);
				if (enemy_fov[i].vertexes[1].pos_x >= 309.8) {
					direction3[i] = 1;
				}
			}
			else {
				direction3[i] = 1;
			}
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(enemy_velocity, enimies_movement, 1);
}



void mouse_click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !is_mouse_clicked) {
		is_mouse_clicked = true;
		if (!is_in_menu) {
			if (current_powerup == NONE) {
				if (magazine > 0) {
					bullets.push_back(factory.create_shape(Constants::BULLET, player.vertexes[0], player_angle, current_powerup, true));
					magazine--;
				}
			}
			else {
				if (powerup_bullets > 0) {
					bullets.push_back(factory.create_shape(Constants::BULLET, player.vertexes[0], player_angle, current_powerup, true));
					powerup_bullets--;
					if (powerup_bullets == 0)
						current_powerup = NONE;
				}
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		is_mouse_clicked = false;
	}

	glutPostRedisplay();
}

// Parte principal - ponto de início de execução
// Cria janela 
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a função de callback de desenho
int main(int argc, char **argv)
{
	srand(time(0));
	//FreeConsole();
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);

	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Cria uma janela com o titulo especificado
	glutCreateWindow("Exemplo Basico");
	SetCursorPos(0, 0); //0,0 is equal to relative -500,500 which is set as the initial values of x and y previous cursor position

						//define que vai existir um tratamento para as teclas especiais (setas, page up,etc)
	glutTimerFunc(50, player_movement, 1);
	glutKeyboardFunc(teclasNormais);
	glutKeyboardUpFunc(teclasNormaisUp);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouse_click);

	//chama a função
	glutDisplayFunc(DesenhaCena);

	glutTimerFunc(150, enimies_movement, 1);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL 
	glutMainLoop();

	return 0;
}
