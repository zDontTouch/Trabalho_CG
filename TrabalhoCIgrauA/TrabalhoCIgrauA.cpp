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

//a função de tratamento de teclas sempre exige 3 inteiros como parâmetro (vai dar erro se não estiver pelo menos declarado
void teclasEspeciais(int tecla, int x, int y) {

	if (IS_RIGHT_KEY_PRESSED) {
		if(tecla != GLUT_KEY_RIGHT)
			player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
	}
	if (IS_LEFT_KEY_PRESSED) {
		if (tecla != GLUT_KEY_LEFT)
			player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
	}
	if (IS_UP_KEY_PRESSED) {
		if (tecla != GLUT_KEY_UP)
			player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
	}
	if (IS_DOWN_KEY_PRESSED) {
		if (tecla != GLUT_KEY_DOWN)
			player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
	}
			

	if (tecla == GLUT_KEY_RIGHT) {
		IS_RIGHT_KEY_PRESSED = true;
		player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
	}
	else {
		if (tecla == GLUT_KEY_LEFT) {
			IS_LEFT_KEY_PRESSED = true;
			player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
		}
		else {
			if (tecla == GLUT_KEY_UP) {
				IS_UP_KEY_PRESSED = true;
				player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
			}
			else {
				if (tecla == GLUT_KEY_DOWN) {
					IS_DOWN_KEY_PRESSED = true;
					player.translate(0, PLAYER_MOVEMENT_TIC, 0, 0);
				}
			}
		}
	}

	glutPostRedisplay();

}

//ja a função de tratamento de teclas normais exige um unsigned char e dois ints
void teclasNormais(unsigned char tecla, int x, int y) {
	if (tecla == 'r' || tecla == 'R') {
		//transX_square = 0;
		//transY_square = 0;
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	int mouse_pos_x = x - (glutGet(GLUT_WINDOW_WIDTH) / 2);
	int mouse_pos_y = (glutGet(GLUT_WINDOW_HEIGHT) / 2) - y;


}

void teclasEspeciaisUp(int tecla, int x, int y) {
	
	if (tecla == GLUT_KEY_RIGHT) {
		IS_RIGHT_KEY_PRESSED = false;
	}
	else {
		if (tecla == GLUT_KEY_LEFT) {
			IS_LEFT_KEY_PRESSED = false;
		}
		else {
			if (tecla == GLUT_KEY_UP) {
				IS_UP_KEY_PRESSED = false;
			}
			else {
				if (tecla == GLUT_KEY_DOWN) {
					IS_DOWN_KEY_PRESSED = false;
				}
			}
		}
	}

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

	//define que vai existir um tratamento para as teclas especiais (setas, page up,etc)
	glutSpecialFunc(teclasEspeciais);
	glutSpecialUpFunc(teclasEspeciaisUp);
	//glutKeyboardFunc(teclasNormais);
	glutPassiveMotionFunc(mouseMotion);

	//chama a função
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL 
	glutMainLoop();

	return 0;
}
