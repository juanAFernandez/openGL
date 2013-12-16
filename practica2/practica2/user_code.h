//**************************************************************************
// Práctica 1
//
// Original de: Domingo Martin Perandres 2013
// Modificación para evaluación de: Juan Antonio Fernández Sánchez
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"



using namespace std;

void draw_cube();
void draw_vertices(vector<_vertex3f> &Vertices); //No acepta parámetros especiales.
void draw_lineas(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);
void draw_triangulos(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras,int color=0, bool mitad=false, double porcion=1.0);
void draw_ajedrez(vector<_vertex3f> &Vertices, vector<unsigned long> &Caras,bool mitad=false);


