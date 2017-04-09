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

double previous_mouse_x_position = -500;
double previous_mouse_y_position = 500;

double get_mouse_angle(int posX, int posY) {

	float deltaY = posY - previous_mouse_y_position; //hardcoded y coordinate of the tip of the spaceship
	float deltaX = posX - previous_mouse_x_position; //hardcoded x coordinate of the tip of the spaceship

	//calculate how much the delta affects as rotation angle
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
Shape player = factory.create_shape(Constants::PLAYER, Vertex(0.0, 0.0));

void DesenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
	player.draw();
	glutSwapBuffers();

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

	if (IS_DOWN_KEY_PRESSED)
		player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);

	if (IS_UP_KEY_PRESSED)
		player.translate(PLAYER_MOVEMENT_TIC,0, 0, 0);

	if (IS_LEFT_KEY_PRESSED)
		player.translate(0,0, PLAYER_MOVEMENT_TIC, 0);

	if (IS_RIGHT_KEY_PRESSED)
		player.translate(0,0,0, PLAYER_MOVEMENT_TIC);

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
