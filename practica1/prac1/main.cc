/** @file main.cpp
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Domingo Martin Perandres
 *  @author Fred Hacker (fhacker)
 *  @bug No known bugs.
 *
*/

//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
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


// tamaño de los ejes
const int AXIS_SIZE=5000; ///< Tamaño de los ejes.

/// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

//Para elegir la fomra de visualizar el objeto, vertices, aristas, sólido, etc...
int ESTILO=0;

//Para seleccionar el fichero a leer, la hormiga, el coche o bethoven.
int FICHERO=0;

bool MITAD=false;

int ESPECIAL=0;
int ESPECIAL2=0;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()  ///<Este método hace algo super chulo.
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


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    vector<double>Vertices;
    vector<unsigned long>Caras;

    vector<double>Vertices2;
    vector<unsigned long>Caras2;

    switch(FICHERO){
    case 1: //Tecla 7
        _file_ply::read("ant",Vertices,Caras);
        break;
    case 2: //Tecla 8
        _file_ply::read("big_dodge",Vertices,Caras);
        break;
    case 3: //Tecla 9
        _file_ply::read("bethoven",Vertices,Caras);
        break;
    case 4: //Tecla 0
        _file_ply::read("bethoven",Vertices,Caras);
        _file_ply::read("big_dodge",Vertices2,Caras2);
        //draw_lineas(Vertices, Caras);
        //draw_lineas(Vertices2, Caras2);
        break;
    }

    switch(ESTILO){
    case 0: //Tecla 1
        draw_vertices(Vertices, Caras);
        break;
    case 1: //Tecla 2
        draw_lineas(Vertices, Caras, 0, MITAD);
        break;
    case 2: //Tecla 3
        draw_triangulos(Vertices, Caras, MITAD);
        break;
    case 3: //Tecla 4
        draw_ajedrez(Vertices, Caras, MITAD);
        break;
    case 4: //Tecla 5

    //draw_lineas(Vertices2, Caras2, 2); //Color b

        if(ESPECIAL==1)draw_lineas(Vertices, Caras, 1, false); //Color a
        if(ESPECIAL==2)draw_triangulos(Vertices, Caras, MITAD); //Color a
        if(ESPECIAL==3)draw_ajedrez(Vertices, Caras, MITAD); //Color a

        if(ESPECIAL2==4)draw_lineas(Vertices2, Caras2, 2, false); //Color a
        if(ESPECIAL2==5)draw_triangulos(Vertices2, Caras2, 2, MITAD); //Color a
        if(ESPECIAL2==6)draw_ajedrez(Vertices2, Caras2, 2, MITAD); //Color a

        //draw_lineas(Vertices2, Caras2, 2); //Color b
        break;
    //case 5:
      //  draw_lineas2(Vertices, Caras);

    //default:
     //   draw_cube();

    };

}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



/**
 Funcion llamada cuando se produce un cambio en el tamaño
de la ventana. El evento manda a la funcion: nuevo ancho y nuevo alto
*/
void change_window_size(int nuevoAncho,int nuevoAlto){
change_projection();
glViewport(0,0,nuevoAncho,nuevoAlto);
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
if (toupper(Tecla1)=='1') {ESTILO=0; draw_scene();};
if (toupper(Tecla1)=='2') {ESTILO=1; draw_scene();};
if (toupper(Tecla1)=='3') {ESTILO=2; draw_scene();};
if (toupper(Tecla1)=='4') {ESTILO=3; draw_scene();};
if (toupper(Tecla1)=='5') {ESTILO=4; draw_scene();};

if (toupper(Tecla1)=='S') {MITAD=true; draw_scene();};//Especial solo un lado.
if (toupper(Tecla1)=='D') {MITAD=false; draw_scene();};//Especial dos lados, lo deja como estaba.


if (toupper(Tecla1)=='7') {FICHERO=1; draw_scene();};
if (toupper(Tecla1)=='8') {FICHERO=2; draw_scene();};
if (toupper(Tecla1)=='9') {FICHERO=3; draw_scene();};
if (toupper(Tecla1)=='0') {FICHERO=4; draw_scene();};

//Especial:
if (toupper(Tecla1)=='Z') {ESPECIAL=1; draw_scene();};
if (toupper(Tecla1)=='X') {ESPECIAL=2; draw_scene();};
if (toupper(Tecla1)=='C') {ESPECIAL=3; draw_scene();};

if (toupper(Tecla1)=='V') {ESPECIAL2=4; draw_scene();};
if (toupper(Tecla1)=='B') {ESPECIAL2=5; draw_scene();};
if (toupper(Tecla1)=='N') {ESPECIAL2=6; draw_scene();};



}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
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
Observer_distance=40*Front_plane;
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
