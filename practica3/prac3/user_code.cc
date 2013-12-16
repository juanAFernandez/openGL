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

//**************************************************************************
// Funcion para dibujar vertices
//**************************************************************************
void draw_vertices(vector<_vertex3d> &Vertices){
    //cout << "Dibujando " << Vertices.size() << " vertices " << endl;

    glPointSize(5);
    glBegin(GL_POINTS);
    for (unsigned i=0; i<Vertices.size(); i++){
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
        //cout << "Vertice: " << (i+1) << Vertices[i].x << " - " << Vertices[i].y << " - " << Vertices[i].z << endl;
        }
    glFlush();
    glEnd();

}



//**************************************************************************
// Funcion para dibujar la malla o lineas
//**************************************************************************
void draw_lineas(vector<_vertex3d> &Vertices, vector<Triangulo> &Caras, GLfloat *color){

    glColor3fv(color);

    glBegin(GL_LINES);
    for (unsigned i=0; i<Caras.size(); i++){
        glVertex3f( Vertices[Caras[i].verticeA].x, Vertices[Caras[i].verticeA].y, Vertices[Caras[i].verticeA].z);
        glVertex3f( Vertices[Caras[i].verticeB].x, Vertices[Caras[i].verticeB].y, Vertices[Caras[i].verticeB].z);

        glVertex3f( Vertices[Caras[i].verticeA].x, Vertices[Caras[i].verticeA].y, Vertices[Caras[i].verticeA].z);
        glVertex3f( Vertices[Caras[i].verticeC].x, Vertices[Caras[i].verticeC].y, Vertices[Caras[i].verticeC].z);

        glVertex3f( Vertices[Caras[i].verticeB].x, Vertices[Caras[i].verticeB].y, Vertices[Caras[i].verticeB].z);
        glVertex3f( Vertices[Caras[i].verticeC].x, Vertices[Caras[i].verticeC].y, Vertices[Caras[i].verticeC].z);
    }
    glEnd();
}
//**************************************************************************



//**************************************************************************
// Funcion para dibujar triangulos para el volumen
//**************************************************************************
void draw_triangulos(vector<_vertex3d> &Vertices, vector<Triangulo> &Caras, GLfloat *color){


    glColor3fv(color);

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<Caras.size(); i++){

        glVertex3f( Vertices[Caras[i].verticeA].x, Vertices[Caras[i].verticeA].y, Vertices[Caras[i].verticeA].z );
        glVertex3f( Vertices[Caras[i].verticeB].x, Vertices[Caras[i].verticeB].y, Vertices[Caras[i].verticeB].z );
        glVertex3f( Vertices[Caras[i].verticeC].x, Vertices[Caras[i].verticeC].y, Vertices[Caras[i].verticeC].z );

    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar triangulos de distintos colores para verlos bien.
//**************************************************************************
void draw_ajedrez(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras,bool mitad){

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<Caras.size(); i=i+3){

        if(mitad==true){

        if((Vertices[Caras[i]].x<=0) && (Vertices[Caras[i+1]].x<=0) && (Vertices[Caras[i+2]].x<=0) ){

        if(i%2==0) glColor3f(0.5,0,0.1);
        else glColor3f(0,1,0);
        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);

        }}
        else{

        if(i%2==0) glColor3f(0.5,0,0.1);
        else glColor3f(0,1,0);
        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);


        }
    }
    glEnd();
}
