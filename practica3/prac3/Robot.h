#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED
#include "figura.h"
#include "variablesGenerales.h"

class Robot{

    //Como atributos privados contaremos con las figuras más primitivas.
    private:
        Figura cubo;
        Figura semiCilindro;

        void inicializarPrimitivas();
        void dibujarCubo(GLfloat *color);
        void dibujarSemiCilindro(GLfloat *color);

    public:

        //Constructor, sin trabajo.
        Robot();
        void dibujarSoporte();
        void dibujarBrazo(double medida);
        void dibujarArticulacion();
        void dibujarSoldador();
        void dibujarRobot();

};

Robot::Robot(){
    inicializarPrimitivas();
}
void Robot::inicializarPrimitivas(){
    cubo.introducirNombre("cubo");
    cubo.leerFichero("cubo");

    semiCilindro.introducirNombre("semiCilindro");
    semiCilindro.leerFichero("semiCilindro");
}
void Robot::dibujarCubo(GLfloat *color){
    if(visu==1)
        cubo.dibujarVertices();
    if(visu==2)
        cubo.dibujarLineas(colorNegro);
    if(visu==3){
        cubo.dibujarLineas(colorNegro);
        cubo.dibujarTriangulos(color);
    }
}
void Robot::dibujarSemiCilindro(GLfloat *color){
    if(visu==1)
        semiCilindro.dibujarVertices();
    if(visu==2)
        semiCilindro.dibujarLineas(colorNegro);
    if(visu==3){
        semiCilindro.dibujarLineas(colorNegro);
        semiCilindro.dibujarTriangulos(color);
    }
}

void Robot::dibujarSoporte(){
    //La base del suelo
    glPushMatrix();
        glScaled(10,1,10);
        dibujarCubo(colorNegro);
    glPopMatrix();

    //El pilar
    glPushMatrix();
        glTranslated(0,10,0);
        glScaled(2,19,2);
        dibujarCubo(colorGris);
    glPopMatrix();


    //El conector
    glPushMatrix();
        glTranslated(0,20,0);
        glScaled(2,2,2);
        dibujarCubo(colorNaranja);
    glPopMatrix();


}

void Robot::dibujarBrazo(double medida){

    int razon=6.0;
    if(medida!=1.0)
        razon=4.0;

    glPushMatrix();
        glRotated(90,0,1,0);
        dibujarSemiCilindro(colorNegro);
    glPopMatrix();

    glPushMatrix();
        glTranslated(razon/2,0,0);
        glScaled(razon,1,1);
        dibujarCubo(colorAmarillo);
    glPopMatrix();

    glPushMatrix();
        glRotated(270,0,1,0);
        glTranslated(0,0,-razon);
        dibujarSemiCilindro(colorNegro);
    glPopMatrix();
}

void Robot::dibujarArticulacion(){
    //La rotación de la articulación se configura antes de llamar a dibujarArcitulación


    //Primer brazo.
    glPushMatrix();
        glRotated(gradosBrazo1,0,0,1); //Esta rotación rota todo lo que haya detrás.
        glRotated(90,1,0,0); //Rotación que nos servirá para todos los brazos ya que se hereda dentro del PushMatrix();
        dibujarBrazo(1.0);

        /*
        //Un cubo en un extremo del primer brazo. (P.E.EXAMEN)
        glPushMatrix();
            //glTranslated(-1,0,0); //En el extremo interior.
            glTranslated(7,0,0); //En el extremo exterior
            dibujarCubo(colorVioleta);
        glPopMatrix();
        */

        //Segundo brazo.
        glPushMatrix();
            glTranslated(6,1,0);
            glRotated(gradosBrazo2,0,1,0);
            dibujarBrazo(1.0);


            //Un cubo en un extremo del segundo brazo. (P.E.EXAMEN)
            glPushMatrix();
                //glTranslated(-1,0,0); //En el extremo interior.
                glTranslated(3,0,-1); //En el extremo exterior
                dibujarCubo(colorVioleta);
            glPopMatrix();



            //Tercer brazo. (Dento del push anterior porque depende de el.
            glPushMatrix();
                glTranslated(6,1,0);
                glRotated(gradosBrazo3,0,1,0);
                dibujarBrazo(0.5); //Tiene otro tamaño.

                /*
                //Un cubo en un extremo del tercer brazo. (P.E.EXAMEN)
                glPushMatrix();
                    //glTranslated(-1,0,0); //En el extremo interior.
                    glTranslated(5,0,0); //En el extremo exterior
                    dibujarCubo(colorVioleta);
                glPopMatrix();
                */

                //Soldador
                glPushMatrix();
                    glScaled(0.6,0.2,0.6);
                    glTranslated(7,3,0);
                    glRotated(gradosSoldador,0,1,0);
                    dibujarSoldador();

                    /*
                    //Un cubo en el extremo del soldador. (P.E. EXAMEN)
                    glPushMatrix();
                        //Hacemos una reescalación y retraslación para contrarestar las de antes.
                        glTranslated(1,0,0);
                        glScaled(1,1,10);
                        dibujarCubo(colorVioleta);
                    glPopMatrix();
                    */

                glPopMatrix();//Del soldador.

            glPopMatrix();//Del tercer brazo.

        glPopMatrix();//Del segundo brazo.

    glPopMatrix();//Del primer brazo.
}

void Robot::dibujarSoldador(){

    //Primer semicirculo.
    glPushMatrix();
        glTranslated(0,0,-0.25);
        dibujarSemiCilindro(colorRojo);
    glPopMatrix();

    //Segundo semicirculo.
    glPushMatrix();
        glTranslated(0,0,0.25);
        glRotated(180,0,1,0);
        dibujarSemiCilindro(colorRojo);
    glPopMatrix();

    //Soldador.
    glPushMatrix();
        glScaled(1,1,0.5);
        glTranslated(soldar,0,0);
        dibujarCubo(colorNaranja);
    glPopMatrix();

}


void Robot::dibujarRobot(){

    glTranslated(traslacion,0,0);
    dibujarSoporte();

    glTranslated(0,20,1.5);
    dibujarArticulacion();
}

#endif // ROBOT_H_INCLUDED
