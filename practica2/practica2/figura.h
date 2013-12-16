#ifndef FIGURA_H_INCLUDED
#define FIGURA_H_INCLUDED

#include "file_ply_stl.hpp"
#include "vertex.h"
#include <iostream>
#include <stdlib.h>



class Figura{

    private:

        char *nombreFigura;
        vector<_vertex3f>Vertices;
        vector<unsigned long>Caras;
        vector<_vertex3f>Normales;

        //Operaciones necesarias por las funciones.
        float convRadianes(double angulo);

    public:
        void introducirNombre(char *nombre){
            nombreFigura=nombre;
        }
        void nombraFigura(){
            cout << nombreFigura;
        }
        void rellenarVerticesManual(_vertex3f coordenada);
        int revolucionaPerfil(int numDivisiones);
        void procesaCaras(int numRevoluciones, int numVerticesPerfil, int revolucionesSesgadas);
        void procesaNormales();

        void leerFichero(char *nombre);
        void dibujarVertices();
        void dibujarLineas(int color=0, bool mitad=false);
        void dibujarTriangulos(int color, bool mitad, double porcion);
        void dibujarAjedrez(bool mitad);
};




void Figura::procesaNormales(){

cout << endl <<  "Procesando normales para " << Caras.size() << " caras." << endl << endl;

//Variables necesarias:
_vertex3f vectorP;
_vertex3f vectorQ;
// n = Vector producto vectorial.
_vertex3f n;
float modulo;


for(int i=0; i<Caras.size(); i=i+3){


    //Descomentar para ver la cara con la que estamos trabajando.
    //cout << Caras[i] << " " << Caras[i+1] << " " << Caras[i+2] << endl;

    //Cada cara implica a tres vectores: i=1, i+1=2, i+2=3

    //P relaciona el vector formado por los vertices 1 y 2 de esa cara.

    vectorP.x=Vertices[Caras[i+1]].x - Vertices[Caras[i]].x;
    vectorP.y=Vertices[Caras[i+1]].y - Vertices[Caras[i]].y;
    vectorP.z=Vertices[Caras[i+1]].z - Vertices[Caras[i]].z;
    //Para ver el vector P
    //cout << "Vector P: " << vectorP.x << " - " << vectorP.y << " - " << vectorP.z << endl;

    //Q relaciona el vector formado por los vertices 1 y 3 de esa cara.
    vectorQ.x=Vertices[Caras[i+2]].x-Vertices[Caras[i+1]].x;
    vectorQ.y=Vertices[Caras[i+2]].y-Vertices[Caras[i+1]].y;
    vectorQ.z=Vertices[Caras[i+2]].z-Vertices[Caras[i+1]].z;

    //Para ver el vector Q
    //cout << "Vector Q: " << vectorQ.x << " - " << vectorQ.y << " - " << vectorQ.z << endl;


    //Una vez obtenidos ambos vectores realizamos el producto vectorial entre ellos.
    n.x=( (vectorP.y*vectorQ.z) - (vectorP.z*vectorQ.y) );
    n.y=( (vectorP.z*vectorQ.x) - (vectorP.x*vectorQ.z) );
    n.z=( (vectorP.x*vectorQ.y) - (vectorP.y*vectorQ.x) );

    //Para ver el vector n
    //cout << "Vector n: " << n.x << " - " << n.y << " - " << n.z << endl;


    //Módulo del producto vectorial.

    modulo=sqrtf( (n.x*n.x) + (n.y*n.y) + (n.z*n.z) );
    //Para ver el módulo
    //cout << "Modulo: " << modulo << endl;


    //Normalización de n
    n.x=(n.x/modulo);
    n.y=(n.y/modulo);
    n.y=(n.y/modulo);
    //Para ver el vector n normalizado
    //cout << "Vector n \"normalizado\" :" << n.x << " - " << n.y << " - " << n.z << endl;

    //Lo introducimos en el arreglo de normales.
    Normales.push_back({n.x,n.y,n.z});


}



}
float Figura::convRadianes(double angulo){
            return (angulo*(M_PI/180));
        }
void Figura::rellenarVerticesManual(_vertex3f coordenada){
            Vertices.push_back(coordenada);
        }
int Figura::revolucionaPerfil(int numDivisiones){
            cout << "### Revolucionado del perfil. Figura: "; nombraFigura(); cout << "  ###" << endl << endl;
            /*
              Para dividir el circulo de la rotación completa en el número de divisiones que especifica
              usaremos la ecuación del círculo.
              X=R·cos(alfa)
              Z=R·sen(alfa)
              Sabiendo que alfa es el ángulo de cada par de perfiles y R es el radio de cada X en cada caso.
              En el caso del triángulo esta información nos la da el segundo vertice pues el primero está en el eje (0,0,0).
            */
            float gradosPorcion=360/numDivisiones;
            float sumatoriaGrados=0.0;

            cout << "Dividiendo el circulo en porciones de " << gradosPorcion << " grados. " << endl;

            float x=0.0,y=0.0,z=0.0;

            float limiteGrados=180.0;
            bool hayLimite=false;

            if (limiteGrados>0.0)
                hayLimite=true;

            if(hayLimite)
            cout << "Límite establecido a " << limiteGrados << " grados. " << endl;

            //Ahora almacenamos en otra variable el número de puntos que conforman el perfil original.
            int numPuntosPerfil=Vertices.size();


//            cout << numPuntosPerfil;

            //  Proceso de adicción de los perfiles. Cuando indicamos que queremos hacer cuatro revoluciones
            //debemos de contar con la que ya tenemos.
            int check=0;
            int valorAbsoluto=0;

            cout << "Vertices: " << endl;
            //Las operaciones siempre se van a realizar sobre el perfil original y sobre cada uno de los puntos.
            for(int i=1; i<numDivisiones; i++){
                //Por cada perfil en la revolución deben crearse todos los puntos nuevos.
                for(int j=0; j<numPuntosPerfil; j++){

                    x=(fabs(Vertices[j].x)*cos(convRadianes(gradosPorcion*i)));
                    y=(Vertices[j].y);
                    z=(fabs(Vertices[j].x)*sin(convRadianes(gradosPorcion*i)));

                    if(z<0.0)
                        z=z+(2*fabs(z));
                    else if(z>0.0)
                        z=z-(2*fabs(z));
                    /*
                    cout << "Perfil " << i << "Grados " << gradosPorcion*i << endl;
                    cout << "Punto " << j << " " ;
                    cout << "Radio: " << fabs(Vertices[j].x) << " ";
                    cout << "x: " << x << " ";
                    cout << "y: " << y << " ";
                    cout << "z: " << z << endl;
                    */

                    //Tenemos que comprobar que no esté repetido para incluirlo.
                    //Si está repetido, será porque es el primero o el último del perfil.
                    //Por tanto comprobaremos que no es el primero del perfil ni el último del perfil.

                    if( ((Vertices[0].x==x) && (Vertices[0].y==y) && (Vertices[0].z==z)) || ((Vertices[numPuntosPerfil-1].x==x) && (Vertices[numPuntosPerfil-1].y==y) && (Vertices[numPuntosPerfil-1].z==z) )){
                       //cout << "Premio, punto repetido!!! " << endl;
                    }else{

                        check++;

                        if(hayLimite){
                        if(sumatoriaGrados<limiteGrados){
                            Vertices.push_back({x,y,z});


                            //cout << "hasta " << sumatoriaGrados << endl;
                        }}
                        else{
                            Vertices.push_back({x,y,z});

                        }

                    }//Fin del for interno.
                }
                sumatoriaGrados+=gradosPorcion;
                //cout << "Calculados: " << sumatoriaGrados << endl;
            }//Fin del for externo

        cout << "Numero total de vertices procesados: " << check+numPuntosPerfil << endl << endl << endl;
        cout << "Numero total de vertices almacenados: "<< Vertices.size() << endl;
        if(hayLimite)
            cout << "N. Perfiles total: " << (limiteGrados/gradosPorcion) << endl;
        else
            cout << "N. Perfiles total: " << numDivisiones << endl;



        for(int i=0; i<Vertices.size(); i++)
            cout << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << " " << endl;










        if(hayLimite)
            return ((limiteGrados/gradosPorcion)+1);
        else{
            return 99;
                cout << "999999999999999";
        }

        }
void Figura::procesaCaras(int numRevoluciones, int numVerticesPerfil, int revolucionesaProcesar){

        cout << "### Procesamiento de Caras. Figura: "; nombraFigura(); cout << "  ###" << endl << endl;


        /////// ojooooooooooooooooooooooooooooo!!!!!!
        bool hayLimite=false;
        //99=No hay sesgo.
        if(revolucionesaProcesar!=99){
        numRevoluciones=revolucionesaProcesar; hayLimite=true;
        }

        //Comprobación de la existencia de tapas inferior y superior.
        bool tapaArriba=true;
        bool tapaAbajo=true;

        if(Vertices[numVerticesPerfil-1].x!=0){tapaArriba=false;}

        cout << "Tapa de arriba: " ;
        if(tapaArriba) cout<< "SI" << endl; else cout << "NO" << endl;

        if(Vertices[0].x!=0){tapaAbajo=false;}
        cout << "Tapa de abajo: ";
        if(tapaAbajo) cout<< "SI" << endl; else cout << "NO" << endl;

        cout << endl;

        bool on=true;
        int numCaras;
        if(!tapaAbajo && !tapaArriba)
        numCaras=numRevoluciones*(numVerticesPerfil-1);
        else //Que estén las dos tapas.
        numCaras=numRevoluciones*(numVerticesPerfil-3);

        int numVerticesPerfilSinEje;
        if(!tapaAbajo && !tapaArriba) numVerticesPerfilSinEje=numVerticesPerfil;
        else if(tapaAbajo || tapaArriba) numVerticesPerfilSinEje=numVerticesPerfil-1;
        if(tapaAbajo && tapaArriba) numVerticesPerfilSinEje=numVerticesPerfil-2;

        cout << "Numero de puntos del perfil: " << numVerticesPerfil << endl;
        cout << "Numero de vertices: " << Vertices.size() << endl;
        cout << "Numero de revoluciones: " << numRevoluciones << endl;
        cout << "Numero de puntos del perfil (sin contar los del eje Y si los tuviera): " <<  numVerticesPerfilSinEje << endl;

        // *** Procesamiento de las caras que forman la TAPA DE ARRIBA.
        //Necesitamos el número de revoluciones y el número de vertices del Perfil.

        if(tapaArriba){//Control de tapas, solo se generará si existe.

        int numCaras_en_TapaArriba=0;

        int matrizCaras[numRevoluciones][3];
        for(int i=0; i<numRevoluciones; i++){
        if(i==0){ //La primera cara.
        matrizCaras[i][0]=numVerticesPerfil-1;
        matrizCaras[i][1]=numVerticesPerfil-2;
        matrizCaras[i][2]=numVerticesPerfil-2+numVerticesPerfil;

        if(tapaAbajo){matrizCaras[i][2]--;}

        //cout << matrizCaras[i][0] << matrizCaras[i][1] << matrizCaras[i][2] << endl;
        }else{

        if(i==1){//La segunda cara
        matrizCaras[i][0]=matrizCaras[i-1][0];
        matrizCaras[i][1]=matrizCaras[i-1][1]+numVerticesPerfil;
        matrizCaras[i][2]=matrizCaras[i-1][2]+numVerticesPerfil-1;

        if(tapaAbajo){
        matrizCaras[i][1]--;
        matrizCaras[i][2]--;
        }

        }
        else
        if(i==(numRevoluciones-1)){//La última cara
        if(!hayLimite){
        matrizCaras[i][0]=matrizCaras[i-1][0];
        matrizCaras[i][1]=matrizCaras[i-1][1]+numVerticesPerfil-1;
        matrizCaras[i][2]=matrizCaras[0][1];

        if(tapaAbajo){
        matrizCaras[i][1]--;
        }
        }
        }
        else{//El resto de caras
        matrizCaras[i][0]=matrizCaras[i-1][0];
        matrizCaras[i][1]=matrizCaras[i-1][1]+numVerticesPerfil-1;
        matrizCaras[i][2]=matrizCaras[i-1][2]+numVerticesPerfil-1;

                if(tapaAbajo){
        matrizCaras[i][1]--;
        matrizCaras[i][2]--;
        }

        }
        }
        }


        if(hayLimite)
            numRevoluciones--;

        for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                numCaras_en_TapaArriba++;
                Caras.push_back(matrizCaras[i][j]);
            }
            //cout << endl;
        }
        if(hayLimite)
        numRevoluciones++;

        /* Por si queremos ver las caras de la tapa de arriba.
        for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                cout << matrizCaras[i][j] << " " ;
            }
            cout << endl;
        }*/

        //La división entre 3 es obvia ya que cada cara son tres elementos (puntos/vertices) dentro del vector "Caras".
        cout << "Numero de caras en Tapa de Arriba: " << numCaras_en_TapaArriba/3 << endl;

        }
        // *** FIN del procesamiento de las caras que forman la TAPA DE ARRIBA.
        // *** Procesamiento de las caras que forman la TAPA DE ABAJO.

        if(tapaAbajo){ //Si hay tapa de abajo se procesan sus caras.

        int numeroCarasTapaAbajo=0;

        int matrizCarasTapaAbajo[numRevoluciones][3];
        for(int i=0; i<numRevoluciones; i++){
        if(i==0){ //La primera cara.
        matrizCarasTapaAbajo[i][0]=0;
        matrizCarasTapaAbajo[i][1]=1;
        matrizCarasTapaAbajo[i][2]=1+numVerticesPerfilSinEje;

        if(tapaArriba){
        matrizCarasTapaAbajo[i][2]++;

        }


        //cout << matrizCaras[i][0] << matrizCaras[i][1] << matrizCaras[i][2] << endl;
        }else{


        if(i==1){//La segunda cara
        matrizCarasTapaAbajo[i][0]=matrizCarasTapaAbajo[i-1][0];
        matrizCarasTapaAbajo[i][1]=matrizCarasTapaAbajo[i-1][1]+numVerticesPerfilSinEje;
        matrizCarasTapaAbajo[i][2]=matrizCarasTapaAbajo[i-1][2]+numVerticesPerfilSinEje;

        if(tapaArriba){matrizCarasTapaAbajo[i][1]++;}

        }
        else //La última cara
        if(i==(numRevoluciones-1)){

        if(!hayLimite){
        matrizCarasTapaAbajo[i][0]=matrizCarasTapaAbajo[i-1][0];
        matrizCarasTapaAbajo[i][1]=matrizCarasTapaAbajo[i-1][1]+numVerticesPerfilSinEje;
        matrizCarasTapaAbajo[i][2]=matrizCarasTapaAbajo[0][1];
        }

        }
        else{//El resto de caras
        matrizCarasTapaAbajo[i][0]=matrizCarasTapaAbajo[i-1][0];
        matrizCarasTapaAbajo[i][1]=matrizCarasTapaAbajo[i-1][1]+numVerticesPerfilSinEje;
        matrizCarasTapaAbajo[i][2]=matrizCarasTapaAbajo[i-1][2]+numVerticesPerfilSinEje;
        }



        }
        }


        for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                //cout << matrizCarasTapaAbajo[i][j] << " " ;
                Caras.push_back(matrizCarasTapaAbajo[i][j]);
            }
            //cout << endl;
        }



        }

         /* Por si queremos ver las caras de la tapa de abajo.
        for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                cout << matrizCarasTapaAbajo[i][j] << " " ;
            }
            cout << endl;
        }*/

        // *** FIN del procesamiento de las caras que forman la TABA DE ABAJO.


// *** Procesamiento de las caras PAR que forma los laterales.
//Caras par

int matrizCarasPAR[numCaras][3];

for(int j=0; j<numVerticesPerfilSinEje-1; j++){
//cout << "CARA PAR"<< endl;
for(int i=0; i<numRevoluciones; i++){ //tantas como revoluciones

    if(i==0){ //La primera cara.

    if(j==0){//De la primera revolucion.

    //Sin ninguna tapa:
    matrizCarasPAR[i][0]=0;
    matrizCarasPAR[i][1]=1;
    matrizCarasPAR[i][2]=numVerticesPerfilSinEje;

    if(tapaAbajo && !tapaArriba){
    matrizCarasPAR[i][0]++;
    matrizCarasPAR[i][1]++;
    matrizCarasPAR[i][2]++;
    }

    if(tapaArriba && !tapaAbajo){
    matrizCarasPAR[i][2]++;
    }

    if(tapaArriba && tapaAbajo){
    matrizCarasPAR[i][0]++;
    matrizCarasPAR[i][1]++;
    matrizCarasPAR[i][2]=matrizCarasPAR[i][2]+2;


    }


    }else{//La primera del resto de subcaras/subperfiles.
    matrizCarasPAR[i][0]=matrizCarasPAR[i][0]+1;
    matrizCarasPAR[i][1]=matrizCarasPAR[i][1]+1;
    matrizCarasPAR[i][2]=matrizCarasPAR[i][2]+1;

    }
    }else{
    if(i==1){//La segunda cara
    matrizCarasPAR[i][0]=matrizCarasPAR[i-1][0]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][1]=matrizCarasPAR[i-1][1]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][2]=matrizCarasPAR[i-1][2]+numVerticesPerfilSinEje;

    if(tapaArriba){
    matrizCarasPAR[i][0]++;
    matrizCarasPAR[i][1]++;
    }


    }
    else //La última cara
    if(i==(numRevoluciones-1)){

    if(!hayLimite){
    matrizCarasPAR[i][0]=matrizCarasPAR[i-1][0]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][1]=matrizCarasPAR[i-1][1]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][2]=matrizCarasPAR[0][0];
    }

    }
    else{//El resto de caras
    matrizCarasPAR[i][0]=matrizCarasPAR[i-1][0]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][1]=matrizCarasPAR[i-1][1]+numVerticesPerfilSinEje;
    matrizCarasPAR[i][2]=matrizCarasPAR[i-1][2]+numVerticesPerfilSinEje;
    }
    }
}


for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                //cout << matrizCarasPAR[i][j] << " " ;
                Caras.push_back(matrizCarasPAR[i][j]);
            }
            //cout << endl;

        }

}
// *** FIN del procesamiento de las caras PAR que forman los laterales .
// *** Inicio del procesamiento de las caras IMPAR que forman los laterales.
//Caras impar

int matrizCarasIMPAR[numCaras][3];

for(int j=0; j<numVerticesPerfilSinEje-1; j++){
//cout << "CARA IMPAR"<< endl;

for(int i=0; i<numRevoluciones; i++){ //tantas como revoluciones

    if(i==0){ //La primera cara.

    if(j==0){

    //Sin ninguna tapa
    matrizCarasIMPAR[i][0]=numVerticesPerfilSinEje;
    matrizCarasIMPAR[i][1]=numVerticesPerfilSinEje+1;
    matrizCarasIMPAR[i][2]=1;

    if(tapaAbajo){

    matrizCarasIMPAR[i][0]++;
    matrizCarasIMPAR[i][1]++;
    matrizCarasIMPAR[i][2]++;

    }

    if(tapaArriba){
    matrizCarasIMPAR[i][0]++;
    matrizCarasIMPAR[i][1]++;

    }



    }else{ //La primera del resto de subcaras/subperfiles
    matrizCarasIMPAR[i][0]=matrizCarasIMPAR[i][0]+1;
    matrizCarasIMPAR[i][1]=matrizCarasIMPAR[i][1]+1;
    matrizCarasIMPAR[i][2]=matrizCarasIMPAR[i][2]+1;

    }
    }else{
    if(i==1){//La segunda cara
    matrizCarasIMPAR[i][0]=matrizCarasIMPAR[i-1][0]+numVerticesPerfilSinEje;
    matrizCarasIMPAR[i][1]=matrizCarasIMPAR[i-1][1]+numVerticesPerfilSinEje;
    matrizCarasIMPAR[i][2]=matrizCarasIMPAR[i-1][2]+numVerticesPerfilSinEje;

    if(tapaArriba){
    matrizCarasIMPAR[i][2]++;
    }


    }
    else //La última cara
    if(i==(numRevoluciones-1)){

    if(!hayLimite){
    matrizCarasIMPAR[i][0]=j;
    matrizCarasIMPAR[i][1]=j+1;
    matrizCarasIMPAR[i][2]=matrizCarasIMPAR[i-1][2]+numVerticesPerfilSinEje;
    if(tapaAbajo){
    matrizCarasIMPAR[i][0]++;
    matrizCarasIMPAR[i][1]++;
    }

    }
    }
    else{//El resto de caras
    matrizCarasIMPAR[i][0]=matrizCarasIMPAR[i-1][0]+numVerticesPerfilSinEje;
    matrizCarasIMPAR[i][1]=matrizCarasIMPAR[i-1][1]+numVerticesPerfilSinEje;
    matrizCarasIMPAR[i][2]=matrizCarasIMPAR[i-1][2]+numVerticesPerfilSinEje;
    }
    }
}

for(int i=0; i<numRevoluciones; i++){
            for(int j=0; j<3; j++){
                //cout << matrizCarasIMPAR[i][j] << " " ;
                Caras.push_back(matrizCarasIMPAR[i][j]);
            }
            //cout << endl;
        }

}


// *** FIN del procesamiento de las caras IMPAR que forman los laterales.


cout << "Numero Caras: " << Caras.size()/3 << endl;
cout << "---------------------------------------" << endl;
       cout << endl << endl;

       cout << "Carasssssssss:" << endl;
       for(int i=0; i<Caras.size(); i=i+3){

        cout <<"3 "<< Caras[i] << " " << Caras[i+1] << " " << Caras[i+2] << endl;

       }




}//Fin de procesa caras.
void Figura::leerFichero(char *nombre){
              vector<double>Vertices2;
              _file_ply::read(nombre,Vertices2,Caras);
              for(int i=0; i<Vertices2.size(); i+3){
//                  rellenarVerticesManual({Vertices2[i], Vertices2[i+1], Vertices2[i+2]});
              }

        }
void Figura::dibujarVertices(){
            draw_vertices(Vertices);
        }
void Figura::dibujarLineas(int color, bool mitad){
            draw_lineas(Vertices,Caras,color, mitad);
        }
void Figura::dibujarTriangulos(int color, bool mitad, double porcion){
            draw_triangulos(Vertices, Caras,color, mitad, porcion);
        }
void Figura::dibujarAjedrez(bool mitad){
            draw_ajedrez(Vertices,Caras, mitad);
}

#endif // FIGURA_H_INCLUDED
