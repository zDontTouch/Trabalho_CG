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

double previous_mouse_x_position;
double previous_mouse_y_position;
float current_player_health = PLAYER_HEALTH;

double get_mouse_angle(int posX, int posY) {

	float deltaY = posY - previous_mouse_y_position; //hardcoded y coordinate of the tip of the spaceship
	float deltaX = posX - previous_mouse_x_position; //hardcoded x coordinate of the tip of the spaceship

	/*
		cos 0 = <u,v>
			   |u|.|v|
	*/
	return 0;
}

//setting some game constants
float PLAYER_MOVEMENT_TIC = 0.1;
float ENEMY_MOVEMENT_TIC = 0.1;

bool IS_RIGHT_KEY_PRESSED = false;
bool IS_LEFT_KEY_PRESSED = false;
bool IS_UP_KEY_PRESSED = false;
bool IS_DOWN_KEY_PRESSED = false;

Shape_factory factory;
//////////////////////////////////////////
//           creating map walls         //
//////////////////////////////////////////
Shape wall1 = factory.create_shape(Constants::WALL, Vertex(-5.0, 4.0), 2.0, 3.0);

vector<Shape> map{
	wall1
};

//////////////////////////////////////////
//           creating enemies           //
//////////////////////////////////////////
Shape enemy_1 = factory.create_shape(Constants::ENEMY, Vertex(3.0, 4.0));

vector<Shape> enemies{
	enemy_1
};

//////////////////////////////////////////
//           creating hostages          //
//////////////////////////////////////////
Shape hostage_1 = factory.create_shape(Constants::HOSTAGE, Vertex(-3.0, -4.0));

vector<Shape> hostages{
	hostage_1
};

//////////////////////////////////////////
//         creating enemy's FoV         //
// ps: the enemy FoVs must be created   //
//   in the same sequence as enemies    //
//////////////////////////////////////////
Shape enemy_fov_1 = factory.create_shape(Constants::ENEMY_FOV, enemy_1.vertexes[0]);

vector<Shape> enemy_fov{
	enemy_fov_1
};

//////////////////////////////////////////
//           creating powerups          //
//////////////////////////////////////////
Shape powerup_1 = factory.create_shape(Constants::POWERUP, Vertex(-3.0, -6.0));

vector<Shape> power_ups{
	powerup_1
};

//creating player
Shape player = factory.create_shape(Constants::PLAYER, Vertex(0.0, 0.0));

void draw_elements() {
	//drawing player
	player.draw();

	//drawing walls
	for (int i = 0;i < map.size();i++) {
		map[i].draw();
	}

	//drawing enemies and their FoVs
	for (int i = 0;i < enemies.size();i++) {
		if (enemies[i].health != 0) {
			enemies[i].draw();
			enemy_fov[i].draw();
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
}

void DesenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
	draw_elements();
	glutSwapBuffers();

	if (current_player_health <= 0) {
		cout << "GAME OVER" << endl << endl;
		system("pause");
	}
}


// Inicializa aspectos do rendering
void Inicio(void)
{
	glClearColor(0.7f, 0.5f, 0.3f, 50.0f);  // cor de fundo da janela
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
	}

}

void mouseMotion(int x, int y) {
	int mouse_pos_x = x - (glutGet(GLUT_WINDOW_WIDTH) / 2);
	int mouse_pos_y = (glutGet(GLUT_WINDOW_HEIGHT) / 2) - y;
	double angle = get_mouse_angle(mouse_pos_x, mouse_pos_y);


	previous_mouse_x_position = mouse_pos_x;
	previous_mouse_y_position = mouse_pos_y;

	//player.rotate(angle);
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

void player_movement(int value) {

	

	if (IS_DOWN_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, PLAYER_MOVEMENT_TIC, 0, 0);
		//testing wall collision
		for (int i = 0;i < map.size();i++) {
			if (!teste.is_colliding_with(map[i])) {
				player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
			}
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
				player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
				Sleep(50);
				current_player_health--;
				player.translate(PLAYER_MOVEMENT_TIC*3, 0, 0, 0);
				IS_UP_KEY_PRESSED = false;
				IS_DOWN_KEY_PRESSED = false;
				IS_LEFT_KEY_PRESSED = false;
				IS_RIGHT_KEY_PRESSED = false;
			}
		}
	}

	if (IS_UP_KEY_PRESSED) {
		Shape teste = player.simulate_translation(PLAYER_MOVEMENT_TIC, 0, 0, 0);
		//testing wall collision
		for (int i = 0;i < map.size();i++) {
			if (!teste.is_colliding_with(map[i])) {
				player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
			}
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
				player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
				Sleep(50);
				current_player_health--;
				player.translate(0, PLAYER_MOVEMENT_TIC*3, 0, 0);
				IS_UP_KEY_PRESSED = false;
				IS_DOWN_KEY_PRESSED = false;
				IS_LEFT_KEY_PRESSED = false;
				IS_RIGHT_KEY_PRESSED = false;
			}
		}
	}

	if (IS_LEFT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, PLAYER_MOVEMENT_TIC, 0);
		//testing wall collision
		for (int i = 0;i < map.size();i++) {
			if (!teste.is_colliding_with(map[i])) {
				player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
			}
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
				player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
				Sleep(50);
				current_player_health--;
				player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC*3);
				IS_UP_KEY_PRESSED = false;
				IS_DOWN_KEY_PRESSED = false;
				IS_LEFT_KEY_PRESSED = false;
				IS_RIGHT_KEY_PRESSED = false;
			}
		}
	}

	if (IS_RIGHT_KEY_PRESSED) {
		Shape teste = player.simulate_translation(0, 0, 0, PLAYER_MOVEMENT_TIC);
		//testing wall collision
		for (int i = 0;i < map.size();i++) {
			if (!teste.is_colliding_with(map[i])) {
				player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
			}
		}

		//testing enemy and FoV collision
		for (int i = 0;i < enemies.size();i++) {
			if (player.is_colliding_with(enemies[i]) || player.is_colliding_with(enemy_fov[i])) {
				player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
				Sleep(50);
				current_player_health--;
				player.translate(0, 0, PLAYER_MOVEMENT_TIC*3, 0);
				IS_UP_KEY_PRESSED = false;
				IS_DOWN_KEY_PRESSED = false;
				IS_LEFT_KEY_PRESSED = false;
				IS_RIGHT_KEY_PRESSED = false;
			}
		}
	}

	for (int i = 0;i < hostages.size();i++) {
		if (player.is_colliding_with(hostages[i])) {
			cout << "VOCÊ VENCEU!" << endl << endl;
			system("pause");
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, player_movement, 1);

}

// Parte principal - ponto de início de execução
// Cria janela 
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a função de callback de desenho
int main(int argc, char **argv)
{
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

	//chama a função
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL 
	glutMainLoop();

	return 0;
}
