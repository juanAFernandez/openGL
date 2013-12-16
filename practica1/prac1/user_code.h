//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>

using namespace std;

void draw_cube();
void draw_vertices(vector<double> &Vertices, vector<unsigned long> &Caras);
void draw_lineas(vector<double> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);
void draw_triangulos(vector<double> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);
void draw_ajedrez(vector<double> &Vertices, vector<unsigned long> &Caras, int color=0, bool mitad=false);


