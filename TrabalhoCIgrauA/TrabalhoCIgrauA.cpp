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

Shape_factory factory;
Shape player = factory.create_shape(Constants::PLAYER, Vertex(0.0, 0.0));;

void DesenhaCena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	player.draw();
	glutSwapBuffers();

}


// Inicializa aspectos do rendering
void Inicio(void)
{
	glClearColor(50.0f, 50.0f, 50.0f, 50.0f);  // cor de fundo da janela
}

//a função de tratamento de teclas sempre exige 3 inteiros como parâmetro (vai dar erro se não estiver pelo menos declarado
void teclasEspeciais(int tecla, int x, int y) {

	if (tecla == GLUT_KEY_RIGHT) {
		player.translate(0, 0, 0, PLAYER_MOVEMENT_TIC);
	}
	else {
		if (tecla == GLUT_KEY_LEFT) {
			player.translate(0, 0, PLAYER_MOVEMENT_TIC, 0);
		}
		else {
			if (tecla == GLUT_KEY_UP) {
				player.translate(PLAYER_MOVEMENT_TIC, 0, 0, 0);
			}
			else {
				if (tecla == GLUT_KEY_DOWN) {
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


// Parte principal - ponto de início de execução
// Cria janela 
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a função de callback de desenho
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Cria uma janela com o titulo especificado
	glutCreateWindow("Exemplo Basico");

	//define que vai existir um tratamento para as teclas especiais (setas, page up,etc)
	glutSpecialFunc(teclasEspeciais);
	//glutKeyboardFunc(teclasNormais);

	//chama a função
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL 
	glutMainLoop();

	return 0;
}
