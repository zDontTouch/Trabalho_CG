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
using namespace Constants;
using namespace std;

double player_angle = 0;
double previous_mouse_x_position = 0.0;
double previous_mouse_y_position = 10.0;
bool is_mouse_clicked = false;
double current_mouse_angle = 0;
int magazine = 15;

//this function calculates the angle between the old and the current mouse position, in order to rotate the player object
double get_mouse_angle(int posX, int posY) {
	float normalized_previous = sqrt(pow(previous_mouse_x_position, 2) + pow(previous_mouse_y_position, 2));
	float normalized_current  = sqrt(pow(posX,2) + pow(posY,2));

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
Shape wall1 = factory.create_shape(Constants::WALL, Vertex(4.5, 4.0), 10.0, 0.5);
Shape wall2 = factory.create_shape(Constants::WALL, Vertex(-10.0, 5.0), 0.5, 5.0);
Shape wall3 = factory.create_shape(Constants::WALL, Vertex(-3.35, 10.0), 3.5, 0.5);
Shape wall4 = factory.create_shape(Constants::WALL, Vertex(-1.0, 9.0), 7.0, 0.5);
Shape wall5 = factory.create_shape(Constants::WALL, Vertex(-0.85, 9.0), 0.5, 7.0);
Shape wall6 = factory.create_shape(Constants::WALL, Vertex(-8.0, -8.0), 3.0, 0.5);
Shape wall7 = factory.create_shape(Constants::WALL, Vertex(-8.35, -6.0), 0.5, 8.35);
Shape wall9 = factory.create_shape(Constants::WALL, Vertex(-5.5, 2.0), 8.0, 0.5);
Shape wall10 = factory.create_shape(Constants::WALL, Vertex(6.5, 7.0), 7.0, 0.5);
Shape wall11 = factory.create_shape(Constants::WALL, Vertex(6.5, 0.0), 0.5, 6.5);
Shape wall12 = factory.create_shape(Constants::WALL, Vertex(0.0, 0.0), 6.5, 0.5);
Shape wall13 = factory.create_shape(Constants::WALL, Vertex(0.5, 0.0), 0.5, 4.0);

vector<Shape> map{
	wall1,
	wall2,
	wall3,
	wall4,
	wall5,
	wall6,
	wall7,
	wall9,
	wall10,
	wall11,
	wall12,
	wall13
};

//////////////////////////////////////////
//           creating enemies           //
//////////////////////////////////////////
Shape enemy_1 = factory.create_shape(Constants::ENEMY, Vertex(-9.0, 8.5), 35);
//Shape enemy_2 = factory.create_shape(Constants::ENEMY, Vertex(-2.0, -4.0));

vector<Shape> enemies{
	enemy_1
	//enemy_2
};

//////////////////////////////////////////
//           creating hostages          //
//////////////////////////////////////////
Shape hostage_1 = factory.create_shape(Constants::HOSTAGE, Vertex(-9.3, 6.0));
Shape hostage_2 = factory.create_shape(Constants::HOSTAGE, Vertex(-8.8, 6.0));

vector<Shape> hostages{
	hostage_1,
	hostage_2
};

//////////////////////////////////////////
//         creating enemy's FoV         //
// ps: the enemy FoVs must be created   //
//   in the same sequence as enemies    //
//////////////////////////////////////////
//Shape enemy_fov_1 = factory.create_shape(Constants::ENEMY_FOV, enemy_1.vertexes[0]);
//Shape enemy_fov_2 = factory.create_shape(Constants::ENEMY_FOV, enemy_2.vertexes[0]);

vector<Shape> enemy_fov{
	//enemy_fov_1
	//enemy_fov_2
};

//////////////////////////////////////////
//           creating powerups          //
//////////////////////////////////////////
Shape powerup_1 = factory.create_shape(Constants::POWERUP, Vertex(-3.0, -6.0));

vector<Shape> power_ups{
	powerup_1
};


//////////////////////////////////////////
//            bullets vector            //
//////////////////////////////////////////

vector<Shape> bullets{

};

void draw_hud() {
	//draw elements to represent player health and magazine bullets remaining

	//draw HUD box
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(6.0, -8.0);
	glVertex2f(9.9, -8.0);
	glVertex2f(9.9, -9.9);
	glVertex2f(6.0, -9.9);
	glEnd();

	//health
	if (player.health < 1) {
		//no drawing
	}
	else if (player.health < 2) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -9.3);
		glVertex2f(9.5, -9.3);
		glVertex2f(9.5, -9.6);
		glVertex2f(8.5, -9.6);
		glEnd();
	}
	else if (player.health < 3) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -9.3);
		glVertex2f(9.5, -9.3);
		glVertex2f(9.5, -9.6);
		glVertex2f(8.5, -9.6);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -8.9);
		glVertex2f(9.5, -8.9);
		glVertex2f(9.5, -9.2);
		glVertex2f(8.5, -9.2);
		glEnd();
	}
	else if (player.health < 4) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -9.3);
		glVertex2f(9.5, -9.3);
		glVertex2f(9.5, -9.6);
		glVertex2f(8.5, -9.6);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -8.9);
		glVertex2f(9.5, -8.9);
		glVertex2f(9.5, -9.2);
		glVertex2f(8.5, -9.2);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex2f(8.5, -8.5);
		glVertex2f(9.5, -8.5);
		glVertex2f(9.5, -8.8);
		glVertex2f(8.5, -8.8);
		glEnd();
	}
	
}

void draw_elements() {
	//drawing player
	player.draw();

	//drawing walls
	for (int i = 0;i < map.size();i++) {
		map[i].draw();
	}

	//drawing enemies and their FoVs
	//wenemy_fov_1.rotate(35, enemy_1.vertexes[0]);
	for (int i = 0;i < enemies.size();i++) {
		if (enemies[i].health > 0) {
			enemies[i].draw();
			//enemy_fov[i].draw();
		}
	}

	//drawing hostages
	for (int i = 0;i < hostages.size();i++) {
		hostages[i].draw();
	}

	//drawing power_ups
	for (int i = 0;i < power_ups.size();i++) {
		hostages[i].draw();
	}

	//drawing bullets
	for (int i = 0;i < bullets.size();i++) {
		bullets[i].draw();
	}

	draw_hud();

}

void DesenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
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


// Inicializa aspectos do rendering
void Inicio(void)
{
	glClearColor(0.7f, 0.5f, 0.3f, 50.0f);  // cor de fundo da janela
}

void check_bullet_collision() {


	for (int i = 0;i < bullets.size();i++) {
		bool bullet_erased = false;
		//detecting enemy hit
		for (int j = 0;j < enemies.size();j++) {
			if (bullets[i].is_colliding_with(enemies[j]) && enemies[j].health>0) {
				MessageBox(NULL, (LPCWSTR)L"GAME OVER\nIS COLLIDING", (LPCWSTR)L"GAME OVER", MB_OK);
				using std::swap;
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
			for (int j = 0; j < map.size();j++) {
				if (bullets[i].is_colliding_with(map[j])) {
					swap(bullets[i], bullets.back());
					bullets.pop_back();

					bullet_erased = true;
					break;
				}
			}
		}

		//detecting hostage hit
		if (bullet_erased) {
			continue;
		}
		else {
			for (int j = 0; j < hostages.size();j++) {
				if (bullets[i].is_colliding_with(hostages[j])) {
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
	case 'I':
		cout << enemy_1.vertexes[0].pos_x << "-" << enemy_1.vertexes[0].pos_y << endl;
		break;
	}

}

void mouseMotion(int x, int y) {
	//position of the mouse related to the player pointing vertex
	int mouse_pos_x = (x - (glutGet(GLUT_WINDOW_WIDTH) / 2)) - (player.horizontal_middle * 100 /2); 
	int mouse_pos_y = (((glutGet(GLUT_WINDOW_HEIGHT) / 2) - y)) - ((player.vertical_middle + PLAYER_HEIGHT/2) * 100 / 2);

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
	for (int i = 0;i < bullets.size();i++) {
		//cout << "bullet #" << i << endl;
		bullets[i].move_bullet();
		glutPostRedisplay();
	}

}

void player_movement(int value) {

	if (IS_DOWN_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, PLAYER_MOVEMENT_TIC, 0, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0;i < map.size();i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i])/* || player.is_colliding_with(enemy_fov[i])*/) {
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
	}

	if (IS_UP_KEY_PRESSED) {
		Shape teste = player.simulate_translation(PLAYER_MOVEMENT_TIC, 0, 0, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0;i < map.size();i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i]) /*|| player.is_colliding_with(enemy_fov[i])*/) {
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
	}

	if (IS_LEFT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, PLAYER_MOVEMENT_TIC, 0);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0;i < map.size();i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0,0,PLAYER_MOVEMENT_TIC,0);
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i])/* || player.is_colliding_with(enemy_fov[i])*/) {
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
	}

	if (IS_RIGHT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, 0, PLAYER_MOVEMENT_TIC);
		//testing wall collision
		bool no_wall_collision = true;
		for (int i = 0;i < map.size();i++) {
			if (teste.is_colliding_with(map[i])) {
				no_wall_collision = false;
			}
		}
		if (no_wall_collision) {
			player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (enemies[i].health > 0) {
				if (player.is_colliding_with(enemies[i])/* || player.is_colliding_with(enemy_fov[i])*/) {
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
	}

	move_bullets();
	check_bullet_collision();

	glutPostRedisplay();
	glutTimerFunc(50, player_movement, 1);

}



void mouse_click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !is_mouse_clicked) {
		is_mouse_clicked = true;
		bullets.push_back(factory.create_shape(Constants::BULLET, player.vertexes[0],player_angle));
		//bullets[bullets.size() - 1].rotate(player_angle,bullets[bullets.size()-1].reference);
		//cout << "created bullet reference: " << bullets[bullets.size() - 1].reference->pos_x << "," << bullets[bullets.size() - 1].reference->pos_y << endl;
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

	FreeConsole();
	glutInit(&argc, argv);
	glutInitWindowSize(1000,1000);

	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Cria uma janela com o titulo especificado
	glutCreateWindow("Exemplo Basico");
	SetCursorPos(0, 0); //0,0 is equal to relative -500,500 which is set as the initial values of x and y previous cursor position

	//define que vai existir um tratamento para as teclas especiais (setas, page up,etc)
	glutTimerFunc(50,player_movement,1);
	glutKeyboardFunc(teclasNormais);
	glutKeyboardUpFunc(teclasNormaisUp);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouse_click);

	//chama a função
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL 
	glutMainLoop();

	return 0;
}
