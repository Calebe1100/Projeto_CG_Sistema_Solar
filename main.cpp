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
#include<stdio.h>

// Vari�veis que guardam a transla��o que ser� aplicada
// sobre a casinha
GLfloat Tx;
GLfloat Ty;

GLfloat angulo;

GLfloat tempTerraOrbSol = 0;

GLfloat contaVolta = 1;

GLfloat velTransMercurio;
GLfloat velTransVenus;
GLfloat velTransTerra;
GLfloat velTransMarte;
GLfloat velTransJupter;
GLfloat velTransSaturno;
GLfloat velTransUrano;
GLfloat velTransNetuno;


GLfloat velRotMercurio;
GLfloat velRotVenus;
GLfloat velRotTerra;
GLfloat velRotMarte;
GLfloat velRotJupter;
GLfloat velRotSaturno;
GLfloat velRotUrano;
GLfloat velRotNetuno;

// Vari�veis que guardam os valores dos diâmetros dos planetas
GLfloat diametroSol = 5, diametroMercurio = 0.5, diametroVenus = 0.6, diametroTerra = 0.8, diametroMarte = 0.5, diametroJupiter = 1.5, diametroSaturno = 1.4, diametroUrano = 1.3, diametroNeturno = 1.3;

// Variavel que gerencia o estado de exibir na tela ou não
GLboolean exibirSol= true, exibirSaturno = true, exibirVenus = true, exibirMercurio = true, exibirTerra = true, exibirMarte = true, exibirJupter = true, exibirUrano = true, exibirNeturno = true;

// Variavel que gerencia o estado de exibir na tela ou não as orbitas
GLboolean exibirOrb1= true, exibirOrb2 = true, exibirOrb3 = true, exibirOrb4 = true, exibirOrb5 = true, exibirOrb6 = true, exibirOrb7 = true, exibirOrb8 = true;

// Variavel que gerencia o estado de exibir a animação
GLboolean executarAnima = true;

// Variavel que gerencia o estado de exibir informações da terra
GLboolean exibirInfoTerra = true;


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

void desenhaOrbita(double raio)
{

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glBegin(GL_LINE_LOOP);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
    }
    glEnd();
}

void escrevaTexto()
{
    char mybuff1[100];
    sprintf (mybuff1, "%.0f", tempTerraOrbSol);
    char *tempOrb [] = {mybuff1};
    char text [] = "Anos decorridos: ";
    char str[80];

    strcat( text, *tempOrb);
    strcpy(str, text);


     char *c;
     glRasterPos3f(0,0,0);
     for(c=str;*c!='\0';c++)
     {  glColor3f(1.0,0.0,0.0);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);
     }
}


void desenhaSatelite(double raio)
{

    float angulo, incremento;

    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(raio, 0.0f, 0.0f);
    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glBegin(GL_POLYGON);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(0.3f*cos(angulo),0.3f*sin(angulo));
    }
    glEnd();
}

void desenhaPlaneta(double raio, double color[], int qntOrbitas, int qntSatelites)
{


    float angulo, incremento;

    glColor3f(color[0], color[1], color[2]);

    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glBegin(GL_POLYGON);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
    }
    glEnd();

    //Desenha orbitas
    for(double i =1; i <= qntOrbitas; i++)
    {
        double raioOrbita = raio + (i/3);
        desenhaOrbita(raioOrbita);
    }

    for(double i =1; i <= qntSatelites; i++)
    {
        glPushMatrix();
        desenhaSatelite((raio + (0.6f)) * pow(-1,i));
        glPopMatrix();
    }

}
void desenhaPlanetaTerra(double raio, double color[], int qntOrbitas, int qntSatelites, int posicao)
{


    float angulo, incremento;

    glColor3f(color[0], color[1], color[2]);

    glPointSize(4.0f);

    incremento = (2 * M_PI) / 200;

    glBegin(GL_POLYGON);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
    }
    glEnd();

    //Desenha orbitas
    for(double i =1; i <= qntOrbitas; i++)
    {
        double raioOrbita = raio + (i/3);
        desenhaOrbita(raioOrbita);
    }

    for(double i =1; i <= qntSatelites; i++)
    {
        glPushMatrix();
        desenhaSatelite((raio + (0.6f)) * pow(-1,i));
        glPopMatrix();
    }

}


void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    float rOrb1 = 8.0f, rOrb2 = 12.0f, rOrb3 = 16.0f, rOrb4 = 20.0f, rOrb5 = 24.0f, rOrb6 = 28.0f, rOrb7 = 32.0f, rOrb8 = 36.0f;

    if(exibirOrb1){
        desenhaOrbita(rOrb1);
    }
    if(exibirOrb2){
       desenhaOrbita(rOrb2);
    }
    if(exibirOrb3){
       desenhaOrbita(rOrb3);
    }
    if(exibirOrb4){
       desenhaOrbita(rOrb4);
    }
    if(exibirOrb5){
       desenhaOrbita(rOrb5);
    }
    if(exibirOrb6){
       desenhaOrbita(rOrb6);
    }
    if(exibirOrb7){
       desenhaOrbita(rOrb7);
    }
    if(exibirOrb8){
       desenhaOrbita(rOrb8);
    }

// Desenha Sol
    double corSol[] = {1.0f, 1.0f, 0.0f};
    int qntOrbitas = 0;
    int qntSatelites = 0;
    int posicao = 0;
    if(exibirSol){
        desenhaPlaneta(diametroSol, corSol, qntOrbitas, qntSatelites);
    }

// Mercurio
    glPushMatrix();
    glRotatef(velTransMercurio, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb1, 0.0f, 0.0f);
    glRotatef(velRotMercurio, 0.0f, 0.0f, 1.0f);


    double corPlanMercurio[] = {0.929f, 0.49f, 0.192f};
    if(exibirMercurio){
        desenhaPlaneta(diametroMercurio, corPlanMercurio, 0, 0);
    }

    glPopMatrix();

// Vênus
    glPushMatrix();
    glRotatef(velTransVenus, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb2, 0.0f, 0.0f);
    glRotatef(velRotVenus, 0.0f, 0.0f, 1.0f);


    double corPlanVenus[] = {133.0/255.0f, 60.0/255.0f, 12.0/255.0f};
    if(exibirVenus){
        desenhaPlaneta(diametroVenus, corPlanVenus, 0, 0);
    }

    glPopMatrix();

// Terra
    glPushMatrix();
    glRotatef(velTransTerra, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb3, 0.0f, 0.0f);
    glRotatef(velRotTerra, 0.0f, 0.0f, 1.0f);


    double corPlanTerra[] = {0.0f, 112.0/255.0f, 192.0/255.0f};
    if(exibirTerra){
        desenhaPlaneta(diametroTerra, corPlanTerra, 0, 1);
        glPushMatrix();
        escrevaTexto();
        glPopMatrix();

    }

    glPopMatrix();

// Marte
    glPushMatrix();
    glRotatef(velTransMarte, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb4, 0.0f, 0.0f);
    glRotatef(velRotMarte, 0.0f, 0.0f, 1.0f);


    double corPlanMarte[] = {1.0f, 0.0f, 0.0f};
    if(exibirMarte){
         desenhaPlaneta(0.5, corPlanMarte, 0, 2);
    }

    glPopMatrix();

// Júpter
    glPushMatrix();
    glRotatef(velTransJupter, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb5, 0.0f, 0.0f);
    glRotatef(velRotJupter, 0.0f, 0.0f, 1.0f);


    double corPlanJupter[] = {1.0f, 192.0/255.0f, 0.0f};
    if(exibirJupter){
        desenhaPlaneta(diametroJupiter, corPlanJupter, 1, 1);
    }

    glPopMatrix();

// Saturno
    glPushMatrix();
    glRotatef(velTransSaturno, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb6, 0.0f, 0.0f);
    glRotatef(velRotSaturno, 0.0f, 0.0f, 1.0f);


    double corPlanSaturno[] = {191.0/255.0f, 144.0/255.0f, 0.0f};
    if(exibirSaturno){
        desenhaPlaneta(diametroSaturno, corPlanSaturno, 4, 1);
    }
    glPopMatrix();


// Urano
    glPushMatrix();
    glRotatef(velTransUrano, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb7, 0.0f, 0.0f);
    glRotatef(velRotUrano, 0.0f, 0.0f, 1.0f);


    double corPlanUrano[] = {84.0/255.0f, 130.0/255.0f, 53.0/255.0f};
    if(exibirUrano){
        desenhaPlaneta(diametroUrano, corPlanUrano, 2, 1);
    }

    glPopMatrix();

// Netuno
    glPushMatrix();
    glRotatef(velTransNetuno, 0.0f, 0.0f, 1.0f);
    glTranslatef(rOrb8, 0.0f, 0.0f);
    glRotatef(velRotNetuno, 0.0f, 0.0f, 1.0f);


    double corPlanNetuno[] = {180.0/255.0f, 199.0/255.0f, 231.0/255.0f};
    if(exibirNeturno){
        desenhaPlaneta(diametroNeturno, corPlanNetuno, 1, 2);
    }

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
    if(executarAnima){
        //Tempo que a terra está orbitando o sol

        // Muda a dire��o quando chega na borda esquerda ou direita
        if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
            xStep = -xStep;

        // Muda a dire��o quando chega na borda superior ou inferior
        if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
            yStep = -yStep;

        // Move a casinha
        Tx += xStep;
        Ty += yStep;

        velTransMercurio += 0.45;
        velTransVenus += 0.35;
        velTransTerra += 0.3;
		if(velTransTerra > contaVolta * 360){
			tempTerraOrbSol++;
			contaVolta++;
		}
        velTransMarte += 0.2;
        velTransJupter += 0.12;
        velTransSaturno += 0.06;
        velTransUrano += 0.03;
        velTransNetuno += 0.01;

        velRotMercurio += 0.43;
        velRotVenus += 0.36;
        velRotTerra += 0.65;
        velRotMarte += 0.65;
        velRotJupter += 0.85;
        velRotSaturno += 0.85;
        velRotUrano += 0.75;
        velRotNetuno += 0.75;

        angulo = angulo + 0.2;

        // Redesenha a casinha em outra posi��o
        glutPostRedisplay();
        glutTimerFunc(11,Anima, 1);

    }
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    switch (key)
    {

    case 's':
        exibirSol = !exibirSol;
        break;
    case 'm':
        exibirMercurio = !exibirMercurio;
        break;
    case 'v':
        exibirVenus = !exibirVenus;
        break;
    case 't':
        exibirTerra = !exibirTerra;
        break;
    case 'M':
        exibirMarte = !exibirMarte;
        break;
    case 'j':
        exibirJupter = !exibirJupter;
        break;
    case 'S':
        exibirSaturno = !exibirSaturno;
        break;
    case 'u':
        exibirUrano = !exibirUrano;
        break;
    case 'n':
        exibirNeturno = !exibirNeturno;
        break;


    case '1':
        exibirOrb1 = !exibirOrb1;
        break;
    case '2':
        exibirOrb2 = !exibirOrb2;
        break;
    case '3':
        exibirOrb3 = !exibirOrb3;
        break;
    case '4':
        exibirOrb4 = !exibirOrb4;
        break;
    case '5':
        exibirOrb5 = !exibirOrb5;
        break;
    case '6':
        exibirOrb6 = !exibirOrb6;
        break;
    case '7':
        exibirOrb7 = !exibirOrb7;
        break;
    case '8':
        exibirOrb8 = !exibirOrb8;
        break;

    case 'e':
        executarAnima = !executarAnima;
        Anima(1);
        break;

    case 'z':
        exibirInfoTerra = !exibirInfoTerra;
        break;

    }
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
    glutInitWindowPosition(300,0);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(900,700);

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Sistema Solar");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc (GerenciaTeclado);

    // Registra a fun��o callback que ser� chamada a cada intervalo de tempo
    glutTimerFunc(150, Anima, 1);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}
