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

using namespace std;

void draw_cube();
void draw_vertices(vector<double> &Vertices); //No acepta parámetros especiales.
void draw_lineas(vector<double> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);
void draw_triangulos(vector<double> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);
void draw_ajedrez(vector<double> &Vertices, vector<unsigned long> &Caras,bool mitad=false);


