#ifndef TRIANGULO_H_INCLUDED
#define TRIANGULO_H_INCLUDED

#include "vertex.h"

struct Triangulo{

    //Valores que relacionan la cara con los vertices que la forman del array Vertices.
    int verticeA;
    int verticeB;
    int verticeC;

    //La normal para usarla en la iluminación de cada triángulo.
    _vertex3f normal;
};


#endif // TRIANGULO_H_INCLUDED
