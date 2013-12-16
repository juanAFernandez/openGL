//**************************************************************************
// Práctica 1
//
// Original de: Domingo Martin Perandres 2013
// Modificación para evaluación de: Juan Antonio Fernández Sánchez
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"
#include <iostream>
#include "file_ply_stl.hpp"
#include "vertex.h"
#include "figura.h"
#include "Robot.h"
#include <math.h>
#include "variablesGenerales.h"
#include <conio.h>


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

//Para elegir la fomra de visualizar el objeto, vertices, aristas, sólido, etc...
int MODO=9;
//Para seleccionar el fichero a leer, la hormiga, el coche o bethoven dentro del vector de Figuras.
int FIGURA=0;
bool MITAD=false;
int ESPECIAL=0;
int ESPECIAL2=0;
double PORCION=1.0;

//Figuras de prueba en el desarrollo.
Figura prueba, peon;

//  ### Declaración del objeto robot. ### //
Robot robot;
//  ### --------------------------------------  ### //



// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=750,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


void draw_objects()
{
    robot.dibujarRobot();
}

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}
//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}
//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (toupper(Tecla1)=='P') {MODO=0; draw_scene();};
if (toupper(Tecla1)=='L') {MODO=1; draw_scene();};


//if (toupper(Tecla1)=='S') {MITAD=true; draw_scene();};//Especial solo un lado.
//if (toupper(Tecla1)=='D') {MITAD=false; draw_scene();};//Especial dos lados, lo deja como estaba.


if (toupper(Tecla1)=='1') {gradosBrazo1+=add; gradosBrazo2-=add; draw_scene();};
if (toupper(Tecla1)=='2') {gradosBrazo1-=add; gradosBrazo2+=add; draw_scene();};

if (toupper(Tecla1)=='3') {gradosBrazo2+=add; draw_scene();};
if (toupper(Tecla1)=='4') {gradosBrazo2-=add; draw_scene();};

if (toupper(Tecla1)=='5') {gradosBrazo3+=add; draw_scene();};
if (toupper(Tecla1)=='6') {gradosBrazo3-=add; draw_scene();};

if (toupper(Tecla1)=='7') {gradosSoldador+=add; draw_scene();};
if (toupper(Tecla1)=='8') {gradosSoldador-=add; draw_scene();};

if (toupper(Tecla1)=='A') {traslacion+=0.1; draw_scene();};
if (toupper(Tecla1)=='S') {traslacion-=0.1; draw_scene();};

if (toupper(Tecla1)=='0') {soldar=0.5; cout << "soldando"; draw_scene(); Sleep(150); soldar=0.0; draw_scene();}

if (toupper(Tecla1)=='Z') {visu=1; draw_scene();};
if (toupper(Tecla1)=='X') {visu=2; draw_scene();};
if (toupper(Tecla1)=='C') {visu=3; draw_scene();};



//Teclas especiales para controlar la visión de dos objetos:

if (toupper(Tecla1)=='9') {animacion=false; draw_scene();};

if (toupper(Tecla1)=='V') {ESPECIAL2=4; draw_scene();};
if (toupper(Tecla1)=='B') {ESPECIAL2=5; draw_scene();};
if (toupper(Tecla1)=='N') {ESPECIAL2=6; draw_scene();};



}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break; //Acercar la cámara.
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break; //Alejar la cámara.
	}
glutPostRedisplay();
}
//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=60*Front_plane;
Observer_angle_x=60;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
//Color de fondo
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}
int cont=0;
//Animación.
void idle(void){


if(animacion){
        Sleep(50);

        if(cont>100){
        gradosBrazo1-=add; gradosBrazo2+=add;
        gradosBrazo3-=add; gradosSoldador-=add;
        }else{

        gradosBrazo1+=add; gradosBrazo2-=add;
        gradosBrazo3+=add; gradosSoldador+=add;

        }

        cont++;
        //cout << cont;

        glutPostRedisplay();

}

}





//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

    // ############################################################################################




    // #############################################################################################




    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 1");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);

    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
