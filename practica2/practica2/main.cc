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
#include <math.h>

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

//  ### Vector de figuras pedidas en el examen. ### //
Figura examen[5];
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
switch(MODO){
    case 0: //Pulsando tecla 1
        examen[FIGURA].dibujarVertices();
        break;
    case 1: //Pulsando tecla 2
        examen[FIGURA].dibujarLineas(1,false);
        break;
    case 2: //Pulsando tecla 3
        examen[FIGURA].dibujarLineas(0,false);
        examen[FIGURA].dibujarTriangulos(1,false,PORCION);
        break;
    case 3: //Pulsando tecla 4
        examen[FIGURA].dibujarLineas(0,false);
        examen[FIGURA].dibujarAjedrez(false);
        break;


//Pruebas con el peon del guión:
/*  peon.dibujarVertices();
    peon.dibujarLineas(0, false);
    peon.dibujarAjedrez(false);
*/

};
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
if (toupper(Tecla1)=='S') {MODO=2; draw_scene();};
if (toupper(Tecla1)=='A') {MODO=3; draw_scene();};

//if (toupper(Tecla1)=='S') {MITAD=true; draw_scene();};//Especial solo un lado.
//if (toupper(Tecla1)=='D') {MITAD=false; draw_scene();};//Especial dos lados, lo deja como estaba.


if (toupper(Tecla1)=='1') {FIGURA=0; draw_scene();};
if (toupper(Tecla1)=='2') {FIGURA=1; draw_scene();};
if (toupper(Tecla1)=='3') {FIGURA=2; draw_scene();};
if (toupper(Tecla1)=='4') {FIGURA=3; draw_scene();};
if (toupper(Tecla1)=='5') {FIGURA=4; draw_scene();};

//Teclas especiales para controlar la visión de dos objetos:
if (toupper(Tecla1)=='7') {PORCION=1.0; draw_scene();};
if (toupper(Tecla1)=='8') {PORCION=0.5; draw_scene();};
if (toupper(Tecla1)=='9') {PORCION=0.25; draw_scene();};

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
Observer_distance=20*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    //Especificamos el modelo el triángulo.
    _vertex3f VerticesFiguraEjemplo[]= {{0,0,0},{5,0,0},{7.5,2.5,0},{5,5,0},{0,5,0}};

    int numVertices=5;
    //Una vez declarado el objeto triángulo global le introducimos los vértices.
    for(int i=0; i<numVertices; i++){prueba.rellenarVerticesManual(VerticesFiguraEjemplo[i]);}

    int numRevo=3;
   // prueba.revolucionaPerfil(numRevo);
    //La función procesaCaras necesita dos parámetros: 1.Num.Revoluciones  2.Num Puntos Perfil


    //prueba.procesaCaras(numRevo,numVertices);
    //prueba.procesaNormales();

    _vertex3f verticesPeon[]={{1.0 ,-1.4, 0.0},{1.0, -1.1, 0.0},{0.5, -0.7, 0.0},
                              {0.4, -0.4, 0.0},{0.4, 0.5, 0.0},{0.5, 0.6, 0.0},{0.3, 0.6, 0.0,},{0.5, 0.8, 0.0},
                              {0.55, 1.0, 0.0},{0.5, 1.2, 0.0},{0.3, 1.4, 0.0}};



    for(int i=0; i<11; i++){peon.rellenarVerticesManual(verticesPeon[i]);}

    //peon.leerFichero("peon");
    //peon.revolucionaPerfil(8);
    //peon.procesaCaras(8,11);
    //peon.procesaNormales();


    //Introducción de los datos del modelo a los objetos para el examen.  ##########################
    int numRevoluciones=24;

    examen[0].introducirNombre("examenA");
    _vertex3f vertices_examenA[]={{0,-0.5,0},{0.5,-0.5,0},{0.5,0.5,0},{0,0.5,0}};
    for(int i=0; i<4; i++){examen[0].rellenarVerticesManual(vertices_examenA[i]);}
    int valorA=examen[0].revolucionaPerfil(numRevoluciones);
    examen[0].procesaCaras(numRevoluciones,4,valorA);
    //examen[0].procesaNormales();

    examen[1].introducirNombre("examenB");
    _vertex3f vertices_examenB[]={{0,-5,0},{5,-7.5,0},{5,7.5,0},{0,5,0}};
    for(int i=0; i<4; i++){examen[1].rellenarVerticesManual(vertices_examenB[i]);}
    int valorB=examen[1].revolucionaPerfil(numRevoluciones);
   //examen[1].procesaCaras(numRevoluciones,4,valorB);
    //examen[1].procesaNormales();



    examen[2].introducirNombre("examenC");
    _vertex3f vertices_examenC[]={{0,5,0},{5,5,0},{7.5,-5,0}};
    for(int i=0; i<3; i++){examen[2].rellenarVerticesManual(vertices_examenC[i]);}
    int valorC=examen[2].revolucionaPerfil(16);
   // examen[2].procesaCaras(16,3, valorC);
   // examen[2].procesaNormales();


    examen[3].introducirNombre("examenD");
    _vertex3f vertices_examenD[]={{0,-5,0},{5,-5,0},{10,5,0}};
    for(int i=0; i<3; i++){examen[3].rellenarVerticesManual(vertices_examenD[i]);}
    int valorD=examen[3].revolucionaPerfil(16);
   //examen[3].procesaCaras(16,3,valorD);
    //examen[3].procesaNormales();

    examen[4].introducirNombre("examenE");
    _vertex3f vertices_examenE[]={{5,-5,0},{5,5,0}};
    for(int i=0; i<2; i++){examen[4].rellenarVerticesManual(vertices_examenE[i]);}
    int valorE=examen[4].revolucionaPerfil(numRevoluciones);
   // examen[4].procesaCaras(numRevoluciones,2,valorE);
    //examen[4].procesaNormales();




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
    glutMainLoop();
    return 0;
}
