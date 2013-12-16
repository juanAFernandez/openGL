#ifndef FIGURA_H_INCLUDED
#define FIGURA_H_INCLUDED

#include "file_ply_stl.hpp"
#include "vertex.h"
#include <iostream>
#include <stdlib.h>
#include "triangulo.h"




class Figura{

    private:

        char *nombreFigura;

        vector<_vertex3d> Vertices;
        vector<Triangulo> Caras;
        //vector<_vertex3f>Normales;

        //Operaciones necesarias por las funciones.


    public:
        void introducirNombre(char *nombre){
            nombreFigura=nombre;
        }


        void nombraFigura(){
            cout << nombreFigura;
        }
        void rellenarVerticesManual(_vertex3d coordenada);
        void informacionVertices();

        void leerFichero(char *nombre);

    //    int revolucionaPerfil(int numDivisiones);
    //    void procesaCaras(int numRevoluciones, int numVerticesPerfil, int revolucionesSesgadas);

        void dibujarVertices();
        void dibujarLineas (GLfloat *color);
        void dibujarTriangulos(GLfloat *color);
    //    void dibujarAjedrez(bool mitad);

};

void Figura::leerFichero(char *nombre){

              vector<double>Vertices2;
              vector<unsigned long> Caras2;
              _file_ply::read(nombre,Vertices2,Caras2);

              //Preprocesamiento de los vertices.
              cout << "Vertices leidos:  ";
              for(int i=0; i<Vertices2.size(); i+=3){
                rellenarVerticesManual({Vertices2[i], Vertices2[i+1], Vertices2[i+2]});
              }
              cout << Vertices.size() << endl;

              //Preprocesamiento de las caras.
              cout << "Caras leidas: ";
              Triangulo tmp;
              for(int i=0; i<Caras2.size(); i+=3){
                    tmp.verticeA=Caras2[i];
                    tmp.verticeB=Caras2[i+1];
                    tmp.verticeC=Caras2[i+2];
                    Caras.push_back(tmp);
              }
              cout << Caras.size() << endl;

}

void Figura::informacionVertices(){
        cout << "Vertices de la figura "; nombraFigura(); cout << endl;
        for(int i=0; i<Vertices.size(); i++){
            cout << "Vertice n." << i << ": " << "  ";
            cout << "x: " << Vertices[i].x << " ";
            cout << "y: " << Vertices[i].y << " ";
            cout << "z: " << Vertices[i].z << endl << endl;
        }
}


void Figura::rellenarVerticesManual(_vertex3d coordenada){
            Vertices.push_back(coordenada);
        }

void Figura::dibujarVertices(){
            draw_vertices(Vertices);
        }

void Figura::dibujarLineas(GLfloat *color){
            draw_lineas(Vertices,Caras,color);
        }
void Figura::dibujarTriangulos(GLfloat *color){
            draw_triangulos(Vertices, Caras, color);
        }/*
void Figura::dibujarAjedrez(bool mitad){
            draw_ajedrez(Vertices,Caras, mitad);
}
*/
#endif // FIGURA_H_INCLUDED
