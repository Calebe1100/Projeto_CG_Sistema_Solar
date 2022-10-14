/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#define PI 3.1415926535

#include <math.h>
#include <vector>

// Vari�veis que guardam a transla��o que ser� aplicada
// sobre a casinha
GLfloat Tx;
GLfloat Ty;
GLfloat angulo;

// Vari�veis que guardam os valores m�nimos de x e y da
// casinha
GLfloat minX, maxX;
GLfloat minY, maxY;

// Vari�veis que guardam o tamanho do incremento nas
// dire��es x e y (n�mero de pixels para se mover a
// cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Vari�veis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Fun��o callback de redesenho da janela de visualiza��o

void desenhaOrbita(double raio){

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

	 glPointSize(4.0f);

     incremento = (2 * M_PI) / 200;

     glBegin(GL_LINE_LOOP);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
     }
     glEnd();
}

void desenhaSatelite(double raio){

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(raio, 0.0f, 0.0f);
    glPointSize(4.0f);

     incremento = (2 * M_PI) / 200;

     glBegin(GL_POLYGON);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(0.3f*cos(angulo),0.3f*sin(angulo));
     }
     glEnd();
}

void desenhaPlaneta(double raio, double color[], int qntOrbitas, int qntSatelites, int posicao){


    float angulo, incremento;

    glColor3f(color[0], color[1], color[2]);

	 glPointSize(4.0f);

     incremento = (2 * M_PI) / 200;

     glBegin(GL_POLYGON);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
     }
     glEnd();

     //Desenha orbitas
     for(double i =1; i <= qntOrbitas; i++){
        double raioOrbita = raio + (i/3);
        desenhaOrbita(raioOrbita);
        glPushMatrix();
            desenhaSatelite(raioOrbita);
        glPopMatrix();
     }

}

void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);


	desenhaOrbita(4);
	desenhaOrbita(8);
	desenhaOrbita(12);
	desenhaOrbita(16);
    desenhaOrbita(20);
	desenhaOrbita(24);
	desenhaOrbita(28);
	desenhaOrbita(32);

	double x[] = {1.0f, 1.0f, 0.0f};
	int qntOrbitas = 0;
	int qntSatelites = 0;
    int posicao = 0;
	desenhaPlaneta(2, x, qntOrbitas, qntSatelites, posicao);

    glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glPushMatrix();

        glTranslatef(4.0f, 0.0f, 0.0f);
        	   glRotatef(angulo, 0.0f, 0.0f, 1.0f);

                double x2[] = {1.0f, 1.0f, 0.0f};
                int qntOrbitas2 = 1;
                int qntSatelites2 = 0;
                int posicao2 = 0;
                desenhaPlaneta(0.5, x2, qntOrbitas2, qntSatelites2, posicao2);
	glPopMatrix();



	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
	{
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
		windowXmin = -40.0f;
		windowXmax =  40.0f;
		windowYmin = -40.0f*altura/largura;
		windowYmax = 40.0f*altura/largura;
	}
	else
	{
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
		windowXmin = -40.0f*largura/altura;
		windowXmax =  40.0f*largura/altura;
		windowYmin = -40.0f;
		windowYmax =  40.0f;
	}
}

// Fun��o callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda a dire��o quando chega na borda esquerda ou direita
	if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
		xStep = -xStep;

	// Muda a dire��o quando chega na borda superior ou inferior
	if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
		yStep = -yStep;

	// Move a casinha
	Tx += xStep;
	Ty += yStep;
	angulo = angulo + 10;

	// Redesenha a casinha em outra posi��o
	glutPostRedisplay();
	glutTimerFunc(150,Anima, 1);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Inicializa��o das vari�veis globais
	xStep = yStep = 1.0f;
	Tx = Ty = 0.0f;
	minX = -15.0f;
	maxX =  15.0f;
	minY = -15.0f;
	maxY =  17.0f;
	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = 40.0f;
}


// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(700,700);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Sistema Solar");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback que ser� chamada a cada intervalo de tempo
	glutTimerFunc(150, Anima, 1);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
