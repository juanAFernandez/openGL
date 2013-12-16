//**************************************************************************
// Práctica 1
//
// Original de: Domingo Martin Perandres 2013
// Modificación para evaluación de: Juan Antonio Fernández Sánchez
//
// GPL
//**************************************************************************

#include "user_code.h"
#include <iostream>
#include "vertex.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************
void draw_cube()
{
    //La estructura es sencilla 3uplas que representas las posciones {X, Y, Z} donde:
    //                  X es el eje ROJO (Horizontal) y sus valores positivos son hacia la derecha y negativos hacia la izquierda
    //                  Y es el eje VERDE (Vertical) y sus valores positivos son hacia arriba y negativos hacia abajo.
    //                  Z es el eje AZUL (Perpendicular a la vista) y sus val pos son hacia alante y neg hacia atras.
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},
                             {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    //GLfloat Aristas[8][3]={{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5}};
    GLfloat Aristas_a[5][3]={{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5}};
    GLfloat Aristas_b[5][3]={{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}};

    GLfloat Triangulos[12][3]={{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},
                              {0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5},
                              {-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
                              {0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}
                             };
    //glBegin especifica la primitiva o primitivas que configurar los vertices entre glBegin y glEnd
    /*              GL_POINTS,
                    GL_LINES,
                    GL_LINE_STRIP,
                    GL_LINE_LOOP,
                    GL_TRIANGLES,
                    GL_TRIANGLE_STRIP,
                    GL_TRIANGLE_FAN,
                    GL_QUADS,
                    GL_QUAD_STRIP, and
                    GL_POLYGON
    */

    glColor3f(0,1,0);
    glPointSize(9);
    glLineWidth(2);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();

    glColor3f(0,1,7);
    glLineWidth(2);

    glBegin(GL_LINE_STRIP);
    for (unsigned i=0;i<5;i++){
        glVertex3fv((GLfloat *) &Aristas_a[i]);
        }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (unsigned i=0;i<5;i++){
        glVertex3fv((GLfloat *) &Aristas_b[i]);
        }
    glEnd();

    glBegin(GL_LINES);
    for (unsigned i=0;i<5;i++){
        glVertex3fv((GLfloat *) &Aristas_a[i]);
        glVertex3fv((GLfloat *) &Aristas_b[i]);
        }
    glEnd();

    glColor3f(0.5,0.5,0.5);
    glBegin(GL_TRIANGLES);
    for (unsigned i=0;i<12;i++){
        glVertex3fv((GLfloat *) &Triangulos[i]);
        }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar vertices
//**************************************************************************
void draw_vertices(vector<_vertex3f> &Vertices){
    cout << "here";
    glPointSize(2);
    glBegin(GL_POINTS);
    for (unsigned i=0; i<Vertices.size(); i++){
        cout << Vertices.size();
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
        }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar la malla o lineas
//**************************************************************************
void draw_lineas(vector<double> &Vertices, vector<unsigned long> &Caras, int color, bool mitad){
/* Como en el ejemplo y con lo que hemos comprobado con la experiencia,que nos dieron con el cubo, los puntos que leemos del fichero
   debemos de introducirlos en tuplas para que los glVertex3 lo pueda leer bien.
*/
    if(color==1) glColor3f(0,1,0);
    if(color==2) glColor3f(0,0,1);

    glBegin(GL_LINES);
    for (unsigned i=0; i<Caras.size(); i=i+3){

        if(mitad==true){

        if((Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) && (Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+2]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) &&  (Vertices[(Caras[i+2]*3)]<=0) ){


        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3)+2]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3)+2]);

        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3)+2]);

        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3)+2]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3)+2]);

        }}
        else{

        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3)+2]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3)+2]);

        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3)+2]);

        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3)+2]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3)+2]);
        }

    }
    glEnd();
}

//**************************************************************************

//**************************************************************************
// Funcion para dibujar triangulos para el volumen
//**************************************************************************
void draw_triangulos(vector<double> &Vertices, vector<unsigned long> &Caras, int color, bool mitad){

    //Para que se vean tambien las lineas y no un solido indescifrable.
    //draw_lineas(Vertices, Caras, color, mitad);

    if(color==1) glColor3f(0,1,0);
    if(color==2) glColor3f(0,0,1);

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<Caras.size(); i=i+3){
        //Para dibujar un triángulo necesitamos tres vertices, usamos los relacionados con cada cara del vector caras.
        if(mitad==true){

        if((Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) && (Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+2]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) &&  (Vertices[(Caras[i+2]*3)]<=0) ){


        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3+2)]);

        }}
        else{

         glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3+2)]);



        }
        }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar triangulos de distintos colores para verlos bien.
//**************************************************************************
void draw_ajedrez(vector<double> &Vertices, vector<unsigned long> &Caras,bool mitad){

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<Caras.size(); i=i+3){

        if(mitad==true){

        if((Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) && (Vertices[(Caras[i]*3)]<=0) && (Vertices[(Caras[i+2]*3)]<=0) && (Vertices[(Caras[i+1]*3)]<=0) &&  (Vertices[(Caras[i+2]*3)]<=0) ){

        if(i%2==0) glColor3f(0.5,0,0.1);
        else glColor3f(0,1,0);
        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3+2)]);

        }}
        else{

        if(i%2==0) glColor3f(0.5,0,0.1);
        else glColor3f(0,1,0);
        glVertex3f( Vertices[(Caras[i]*3)], Vertices[(Caras[i]*3)+1], Vertices[(Caras[i]*3+2)]);
        glVertex3f( Vertices[(Caras[i+1]*3)], Vertices[(Caras[i+1]*3)+1], Vertices[(Caras[i+1]*3+2)]);
        glVertex3f( Vertices[(Caras[i+2]*3)], Vertices[(Caras[i+2]*3)+1], Vertices[(Caras[i+2]*3+2)]);

        }
    }
    glEnd();
}
