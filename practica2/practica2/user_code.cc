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
    //cout << "Dibujando " << Vertices.size() << " vertices " << endl;

  //  double valor=100; //valor=porcentaje
  //  valor=valor*0.01;

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


//void draw_perfil(vector<_vertex3f> &Vertices,)





void draw_lineas(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras, int color, bool mitad){
/*
    En este caso para dibujar la linea del contorno usaremos el vector de Vertices en vez de el de caras.
*/
    if(color==1) glColor3f(0,1,0);
    if(color==2) glColor3f(0,0,1);

    glBegin(GL_LINES);
    for (unsigned i=0; i<Caras.size(); i=i+3){

        if(mitad==true){

        if((Vertices[Caras[i]].x<=0) && (Vertices[Caras[i+1]].y<=0) &&  (Vertices[Caras[i+2]].z<=0) ){


        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);

        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);

        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);

        }}
        else{

        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);

        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);

        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z);
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z);
        }

    }
    glEnd();


/*

Para que nos dibuje los perfiles, pero esta función no está bien, añadir una función más que lo haga.

        glColor3f(0,0,0);
        glBegin(GL_LINES);
        for (unsigned i=0; i<Vertices.size(); i=i++){
            if(i>0 && i<Vertices.size()){
                glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
                glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
            }
            else
                glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
        }
        glEnd();
*/



}

//**************************************************************************

//**************************************************************************
// Funcion para dibujar triangulos para el volumen
//**************************************************************************
void draw_triangulos(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras,int color, bool mitad, double porcion){

    //Para que se vean tambien las lineas y no un solido indescifrable.
    //draw_lineas(Vertices, Caras, color, mitad);

    /*
    cout << "N. Vertices: " << Vertices.size() << endl;
    cout << "N. Caras: " << Caras.size() << endl;
    for(int i=0; i<Caras.size(); i++){
                cout << Caras[i] << " ";
            }
    */
    //cout << porcion;

    if(color==1) glColor3f(0,1,0);
    if(color==2) glColor3f(0,0,1);

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<Caras.size(); i=i+3){
        //Para dibujar un triángulo necesitamos tres vertices, usamos los relacionados con cada cara del vector caras.
        //glNormal3f( Normales[j].x, Normales[j].y, Normales[j].z );

        if(porcion==0.5){
        if( Vertices[Caras[i]].x>=0 && Vertices[Caras[i+1]].x>=0 && Vertices[Caras[i+2]].x>=0 ){
        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z );
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z );
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z );
        }
        }else
        if(porcion==0.25){
        if( Vertices[Caras[i]].x>=0 && Vertices[Caras[i+1]].x>=0 && Vertices[Caras[i+2]].x>=0
        &&  Vertices[Caras[i]].z>=0 && Vertices[Caras[i+1]].z>=0 && Vertices[Caras[i+2]].z>=0){
        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z );
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z );
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z );
        }
        }else{
        glVertex3f( Vertices[Caras[i]].x, Vertices[Caras[i]].y, Vertices[Caras[i]].z );
        glVertex3f( Vertices[Caras[i+1]].x, Vertices[Caras[i+1]].y, Vertices[Caras[i+1]].z );
        glVertex3f( Vertices[Caras[i+2]].x, Vertices[Caras[i+2]].y, Vertices[Caras[i+2]].z );
        }

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
