/**********************************************************************/
/* Autor: Palacios José Emanuel docente de la EETPN°602               */
/* Programa: Sumo Arduino Básico                                      */
/* año:2018                                                           */
/**********************************************************************/

// Conexiones y librerias
#include <AFMotor.h> //incluye la librería de AdaFruit en nuestro programa
AF_DCMotor Motor1(1);// crea una instancia de un motor conectado a la puerta M1 izquierdo
AF_DCMotor Motor2(2);// crea una instancia de un motor conectado a la puerta M2 derecho

// sensor de línea izquierdo conectado en A0
// sensor de línea derecho conectado en A1 
// sensor de distancia izquierdo conectado en A2
// sensor de distancia derecho conectado en A3

// Variables
int li_izq_dela =0;// variable del sensor de linea izquierdo delantero
int li_der_dela =0;// variable del sensor de linea derecho delantero
int dis_izq = 0;// variable de distancia izquierdo
int dis_der = 0;// variable de distancia derecho

// **************************** Inicialización **********************************************
void setup() {
         Serial.begin(9600);
         Serial.println("Iniciando lectura de sensor");
         delay(5000); // cuando se active el robot esperamos los 5 segundos antes de iniciar el programa  por única vez.
         //este tiempo se debe cronometrar para asegurarnos de que sea el correcto
}
 
//***************************** programa principal *******************************************
void loop() { 
  sensores();//llamo a la función sensores
  //**********  sensores de proximidad Sharp **************************************************
  // Estos valores de 250 pueden cambiar dependiendo de cada sensor,
  // cuando es menor a 250 se refiere a que no detecta nada
  // y mayor a 250 es que el sensor esta detectando algo
  // sin embargo eso lo debes comprobar tu mismo con tus sensores.
  //********** sensores de linea blanca o negra ***********************************************
  // Para los sensores de linea blanca o negra los valores mayores a 200 indican que detecto la liena blanca,
  // por lo que si cualquiera de los 2 sensores detecta la linea blanca el robot debe regresar
  // sin embargo eso lo debes comprobar tu mismo con tus sensores.
  // Tu decides si quieres que solo regrese o tambien quieres que gire a la derecha o izquierda
  //************************** TOMA DE DECISIONES ************************************************************
  if((li_izq_dela < 200) && (li_der_dela < 200)&&(dis_izq >= 250)&&(dis_der >= 250)){
    // si ambos sensores leen zona negra y ambos sensores de distancia encuentren al enemigo
       adelante_f();//llamo a la función adelante fuerte    
        }
  if((li_izq_dela < 200) && (li_der_dela < 200)&&(dis_izq < 250)&&(dis_der >= 250)){
    // si ambos sensores leen zona negra y encuentre al enemigo con el sensor derecho
       derecha_f();//llamo a la funcion derecha fuerte
        }           
  if((li_izq_dela < 200) && (li_der_dela < 200)&&(dis_izq >= 250)&&(dis_der < 250)){
    // si ambos sensores leen zona negra y encuentre al enemigo con el sensor izquierdo
       adelante_d();//llamo a la función izquierda fuerte
        }    
  if((li_izq_dela < 200) && (li_der_dela < 200)&&(dis_izq < 250)&&(dis_der < 250)){
    // si ambos sensores leen zona negra y no encuentro al enemigo con los sensores
       izquierda_d();//llamo a la función izquierda despacio
        }
  if((li_izq_dela >= 200) || (li_der_dela >= 200)){
    // si leo línea blanca con sensor derecho 0 izquierdo
       reversa_f();//llamo a la función reversa fuerte
       delay(800); //la demora dependera de la velocidad del robot 
        } 
//************************** FIN TOMA DE DECISIONES **************************************        
// ¿y si me atacan por atras, o por algun lateral?

} 
//************************** fin programa principal  *************************************

// funciones creadas por mi para simplificar el programa principal
//**********  definir velocidad de motor **************************************************
// Estos valores de 255 o 125 pueden cambiar dependiendo de cada motor ,
// cuando 255 se refiere a que se le envia toda la potencia, y 125 la mitad de la potencia
// sin embargo eso lo debes comprobar tu mismo con tus motores y elegir la velocidad adecuada.
//*****************************************************************************************
void sensores() // lectura de sensores
{
  li_izq_dela = analogRead(A0); // Lectura del sensor de línea delantero izquierdo
  li_der_dela = analogRead(A1); // Lectura del sensor de línea delantero derecho
  dis_izq= analogRead(A2) ; // Lectura del sensor SHARP izquierdo
  dis_der= analogRead(A3) ; // Lectura del sensor SHARP derecho
}
void adelante_d() // muevo el robot hacia adelante despacio
{
    Motor1.setSpeed(125); //definimos la velocidad
    Motor2.setSpeed(125); //definimos la velocidad
    Motor1.run(FORWARD);// avanzo 
    Motor2.run(FORWARD);// avanzo
}
void adelante_f() // muevo el robot hacia adelante fuerte
{
    Motor1.setSpeed(255); //definimos la velocidad
    Motor2.setSpeed(255); //definimos la velocidad
    Motor1.run(FORWARD);// avanzo 
    Motor2.run(FORWARD);// avanzo
}
 void reversa_f() // muevo el robot en reversa fuerte
 {
    Motor1.setSpeed(255); //definimos la velocidad
    Motor2.setSpeed(255);//definimos la velocidad
    Motor1.run(BACKWARD);// retrocedo
    Motor2.run(BACKWARD);// retrocedo 
 }
 void derecha_d() // muevo el robot hacia la derecha despacio
 {
    Motor1.setSpeed(125); //definimos la velocidad
    Motor2.setSpeed(125); //definimos la velocidad
    Motor1.run(FORWARD);// avanzo
    Motor2.run(BACKWARD);// retrocedo
 }
 void derecha_f() // muevo el robot hacia la derecha fuerte
 {
    Motor1.setSpeed(255); //definimos la velocidad
    Motor2.setSpeed(255); //definimos la velocidad
    Motor1.run(FORWARD);// avanzo
    Motor2.run(BACKWARD);// retrocedo
 }
 void izquierda_d() // muevo el robot hacia la izquierda despacio
 {
    Motor1.setSpeed(125); //definimos la velocidad
    Motor2.setSpeed(125); //definimos la velocidad
    Motor1.run(BACKWARD);// retrocedo
    Motor2.run(FORWARD);// avanzo
 }
 void izquierda_f() // muevo el robot hacia la izquierda fuerte
 {
    Motor1.setSpeed(255); //definimos la velocidad
    Motor2.setSpeed(255); //definimos la velocidad
    Motor1.run(BACKWARD);// retrocedo
    Motor2.run(FORWARD);// avanzo
 }
 void detengo() // detengo el robot 
 {
     Motor1.run(RELEASE);// detengo motor
     Motor2.run(RELEASE);// detengo motor
 }
 /************* TABLA DE VERDAD DE TOMA DE DECISIONES *********************************
  * LINEA IZQUIERDA* LINEA DERECHA* SHARP DERECHO* SHARP IZQUIERDO*      ACCIÓN        *
  *         0      *       0      *       1      *        1       * ADELANTE FUERTE    *
  *         0      *       0      *       1      *        0       * DERECHA FUERTE     *
  *         0      *       0      *       0      *        1       * IZQUIERDA FUERTE   *
  *         0      *       0      *       0      *        0       * IZQUIERDA DESPACIO * 
  *         1      *       1      *       -      *        -       * ATRAS FUERTE       *
  **************************************************************************************/        
