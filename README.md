# **Explicación trabajo**
El archivo en GitHub contiene la solución al parcial correspondiente a Arquitectura de Hardware en el periodo de 2023-2.

En el parcial pedian solucionar 3 problemas haciendo uso de una FRDM-KL25Z y de un teclado matricial, los cuales eran:

1. Pasar las coordenadas en X y en Y de dos puntos y con estos puntos calcular la pendiente de la recta que se genera al unir los dos puntos y el intercepto de esta recta con el eje Y.
2. Pedir una cantidad N de temperaturas y con ellas calcular el promedio de temperaturas y la desviación estándar
3. Encender un led RGB del color deseado usando el código RGB correspondiente al color

## **Explicación del código**

```c++
#include "mbed.h"
#include <iostream>
#include <string>

using namespace std;


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define DEBOUNCE_DELAY    200ms
UnbufferedSerial serial(USBTX, USBRX, 9600);
```
En este fragmento del código, se hace el llamado a diversas librerias que se necesitan para el desarrollo del código. Además de hacer llamado al objeto serial para la comunicación con la tarjeta.

```c++
const char NO_KEY = '\0';
int c = 0;
string opcion;
string aux = "";
bool flag = true;
string input = "";

// USAR # COMO ENTER Y * COMO CLEAR
const int ROWS = 4;
const int COLS = 3;
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
```
En este fragmento se crean las variables y constantes que se usan más de una vez en toda la ejecución del código. La matriz que se crea es donde se establece la estructura del teclado matricial para al momento de leer la entrada de este teclado traducir la tecla presionada con el valor para trabajar en el sistema.

```c++
DigitalIn rowPins[ROWS] = {PTC9, PTC8, PTC7, PTC6};
DigitalOut colPins[COLS] = {PTC5, PTC4, PTC3};
```
Con esas lineas se define los pines de entrada y salida digitales para la conexión del teclado matricial.

```c++
char readKeypad() {
    // Loop through each column, set it as output, and scan rows
    for (int col = 0; col < COLS; col++) {
        colPins[col] = 0;  // Set the current column low

        for (int row = 0; row < ROWS; row++) {
            if (rowPins[row] == 0) {  // Check if the key is pressed
                ThisThread::sleep_for(DEBOUNCE_DELAY);  // Debounce delay
                if (rowPins[row] == 0) {
                    colPins[col] = 1;  // Release the current column
                    return keys[row][col];  // Return the pressed key
                }
            }
        }

        colPins[col] = 1;  // Release the current column
    }

    return NO_KEY;  // Return if no key is pressed
}
```
Este método se usa para leer cual tecla es presionada para mandar los indices correspondientes a la matriz y obtener el valor correspondiente. Este funciona suponiendo cada columna en estado de 1 o 0 de forma alternada, es decir 0 para tomar que hay información saliente y 1 para expresar que no hay información saliente. A su vez se debe de ir alternando las filas que son las entradas dígitales buscando cual fila se encuentra en 0, ya que esa es la tecla presionada. De este modo la tecla presiona tendria la fila y la columna correspondiente en 0.

```c++
double calcularDesviacionEstandar(const int datos[], int n, double promedio) {
    if (n == 0) {
        return 0.0; // Devuelve 0 si no hay datos.
    }

    double sumaDeCuadrados = 0.0;

    for (int i = 0; i < n; ++i) {
        sumaDeCuadrados += (datos[i] - promedio) * (datos[i] - promedio);
    }

    double varianza = sumaDeCuadrados / n;
    double desviacionEstandar = std::sqrt(varianza);

    return desviacionEstandar;
}
```
Este método se usa para calcular la desviación estándar, para realizar este método buscamos ayuda de internet ya que para calcular la desviación estándar se hace uso de una fórmula. Lo que busca hacer este método es ir haciendo la fórmula paso a paso.

```c++
while(flag){
    char key = readKeypad();
        if (key != NO_KEY) {
            opcion += key;
            c++;
            printf("Current input: %s\n", opcion.c_str());
            if (key == '#') {
                flag = false; 
                c = 0; 
            }  
            if (key == '*') {
                opcion = "";
                c = 0;
            }
        }
}
```
Este fragmento que se repite varias veces durante el desarrollo del código se necesita para estar leyendo constantemente la entrada del teclado matricial e ir guardando el valor que se ingresa. Acá es donde se hace la validación de cuando se presiona * y # para establecer las funciones de estas teclas, es decir limpiar la entrada y enter, respectivamente. Dentro de la parte de ``` if(key == '#'){``` en ciertas ocasiones se hace un procedimiento de validación necesarias para cada parte en especifico.  

### Dentro del main:

```c++
cout << "Este programa tiene 3 funcionalidades, \nla primera es encontrar la pendiente y la intersección dados dos puntos, \nla segunda es encontrar el promedio y la desviación estándar dado un conjunto N de temperaturas. \nEl tercero, es para generar colores con el código RGB en el led. \nIngrese un número (1, 2 o 3) dependiendo de la función que desea.\n";
    ThisThread::sleep_for(BLINKING_RATE);
    flag = true;
    while(flag){
        char key = readKeypad();
        if (key != NO_KEY) {
            opcion += key;
            c++;
            printf("Current input: %s\n", opcion.c_str());
            if (key == '#') {
                flag = false; 
                c = 0; 
            }  
            if (key == '*') {
                opcion = "";
                c = 0;
                }
            }
        }
```
Con este fragmento, se muestra al usuario por medio de la consola una explicación del proyecto y las opciones que debe de ingresar según lo que desee. Además del bloque ```while(flag)``` explicado anteriormente para el ingreso de datos al programa por medio del teclado matricial.

```c++
if (opcion == "1#"){
    ...
}else if (opcion == "2#"){
    ...
}else if (opcion == "3#"){
    ...
}else{
    cout << "Opcion no valida, reinicie la tarjeta \n";
}
```
Con estos condicionales se valida cual es la opción que el usuario decidió acceder por medio del fragmento explicado anteriormente. Si no ingresa una opción valida indica que la opción no es valida y que se debe de reiniciar la tarjeta para volver al menú anterior.

### **Opción 1 (Punto 1 del parcial)**
```c++
flag = true;
cout << "Opcion seleccionada: Rectas \n";
ThisThread::sleep_for(BLINKING_RATE);
int x1=0;
int x2=0;
int y1=0;
int y2=0;
int m=0;
int b=0;
```
En estas lineas se inicializa las variables que se van a usar para almacenar los puntos que el usuario va a ingresar, la pendiente y el intercepto con el eje y. Además se cambia el estado de flag a true, para que ingrese al bloque de while() en el cual se piden los datos al usuario. se usa la función ```ThisThread::sleep_for(BLINKING_RATE);``` para establecer un tiempo entre mensajes de consola.

```c++
cout <<"Ingrese la x del primer punto:\n";
ThisThread::sleep_for(BLINKING_RATE);
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
            if (key == '#') {
                for (int i = 0; i < input.length(); i++){
                    aux += input[i];
                }
                x1 = stoi(aux);
                aux = "";
                input = "";
                flag = false;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            if (key == '*') {
                input = "";
                c = 0;
            }
        }
}

cout <<"Ingrese la y del primer punto:\n";
ThisThread::sleep_for(BLINKING_RATE);
flag=true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            y1 = stoi(aux);
            aux = "";
            input = "";
            flag = false;
            ThisThread::sleep_for(BLINKING_RATE);
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}

cout <<"Ingrese la x del segundo punto:\n";
ThisThread::sleep_for(BLINKING_RATE);
flag =true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
        x2 = stoi(aux);
        aux = "";
        input = "";
        flag = false;
        ThisThread::sleep_for(BLINKING_RATE);
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}

cout <<"Ingrese la y del segundo punto:\n";
ThisThread::sleep_for(BLINKING_RATE);
flag = true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            y2 = stoi(aux);
            aux = "";
            input = "";
            flag = false;
            ThisThread::sleep_for(BLINKING_RATE);
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}     
```
Estos 4 bloques ```while(flag)``` explicados anteriormente se usan para pedir las coordenadas X y Y de cada punto con los cuales se quiere saber la pendiente de la recta que forman y el intercepto de dicha recta con el eje Y.

```c++
if (x1 == x2){
    cout <<"La pendiente = infinito:\n";
}
else if (y1 == y2){
    cout <<"La pendiente = 0:\n";
    b = y1;
    printf("El intercepto con y: %d\n", b);
}else {
    m=(y2-y1)/(x2-x1);
    printf("La pendiente = %d\n", m);
    b= y1-m*x1;
    printf("El intercepto con y: %d\n", b);
}
```
Esta estructura de condicionales lo que hace es validar que si sean operaciones válidas y casos partículares según la pendiente y los puntos, y muestra en consola el valor de la pendiente y el intercepto con el eje Y

### **Opción 2 (Punto 2 del parcial)**
```c++
cout << "Opcion seleccionada promedio de temperaturas\n";
int cantidad = 0;
cout << "Ingrese la cantidad de temperaturas\n";
ThisThread::sleep_for(BLINKING_RATE);
flag = true;
while(flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            cantidad = stoi(aux);
            aux = "";
            input = "";
            flag = false;
            ThisThread::sleep_for(BLINKING_RATE);
            }
        if (key == '*') {
                input = "";
                c = 0;
        }
    }
}

int temperaturas [cantidad];
double promedio = 0;
```
Se crea la variable cantidad que es la cantidad de temperaturas con las que el usuario desea calcular el promedio y la desviación estándar. En el bloque del ```while(flag)``` en el cual se piden los datos, lo que se hace es guardar la cantidad que el usuario quiere en la variable creada. Luesgo se crea un array para almacenar las temperaturas de la cantidad ingresada previamente por el usuario, además de la variable promedio, que será usada más adelante.

```c++
for (int i = 0; i < cantidad; i ++){
    ThisThread::sleep_for(BLINKING_RATE);
    flag = true;
    int temp = 0;
    printf("Temperatura a ingresar: %d \n", i+1);
    while(flag){
        char key = readKeypad();
        if (key != NO_KEY) {
            input += key;
            c++;
            printf("Current input: %s\n", input.c_str());
            if (key == '#') {
                for (int i = 0; i < input.length(); i++){
                    aux += input[i];
                }
                temp = stoi(aux);
                aux = "";
                input = "";
                flag = false;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            if (key == '*') {
                    input = "";
                    c = 0;
            }
        }
    }
    temperaturas[i] = temp;
    promedio += temp;
}
promedio /= cantidad;
printf("El promedio de temperaturas ingresadas es de: %.4f\n", promedio);

double des = calcularDesviacionEstandar(temperaturas, cantidad, promedio);
printf("La desviación estándar es: %.4f\n", des);
```
En el ciclo ```for()``` lo que se hace es recorrer el array creado previamente y llenarlo con las temperaturas que el usuario va ingresando en el bloque ```while(flag)``` que es el encargado de ir pidiendo las temperaturas y asignarlas en el momento en el que se presiona la tecla '#'. Además en el mismo ciclo ```for()``` se va sumando las temperaturas en la variable promedio para luego apenas se termina el ciclo dividirla por la cantidad de temperaturas y de este modo obtener el promedio. Además se manda el array de temperaturas, la cantidad y el promedio al método para calcular la desviación estandar. 

### **Opción 3 (Punto 3 del parcial)**
```c++
cout << "Se ha seleccionado RGB\n";
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

float pwmR = 0.0;
float pwmG = 0.0;
float pwmB = 0.0;
```
Se crean objetos leds de la clase PWM (Pulso de ancho modulado), que son los que permiten establecer el nivel de intensidad de encendido de cada color para dar un estimado del color deseado. Además se crean las variables en las cuales se guardaran el nivel de intensidad que cada led debe de tener para lograr acercarse al color que el usuario ingresa.

```c++
cout << "Ingresa el codigo RGB del led rojo (Presiona # como enter y * para limpiar toda la entrada): \n";
flag = true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            pwmR = stoi(aux);
            aux = "";
            input = "";
            flag = false;
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}
                
cout << "Ingresa el codigo RGB del led verde (Presiona # como enter y * para limpiar toda la entrada): \n";
flag = true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            pwmG = stoi(aux);
            aux = "";
            input = "";
            flag = false;
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}

cout << "Ingresa el codigo RGB del led azul (Presiona # como enter y * para limpiar toda la entrada): \n";
flag = true;
while (flag){
    char key = readKeypad();
    if (key != NO_KEY) {
        input += key;
        c++;
        printf("Current input: %s\n", input.c_str());
        if (key == '#') {
            for (int i = 0; i < input.length(); i++){
                aux += input[i];
            }
            pwmB = stoi(aux);
            aux = "";
            input = "";
            flag = false;
        }
        if (key == '*') {
            input = "";
            c = 0;
        }
    }
}
```
Se repite el bloque de código ```while(flag)``` 3 veces, para pedir el código RGB de cada color, es decir el valor entre 0 y 255 de cada led. En cada bloque se almacena este valor en la variable creada previamente del led correspondiente.

```c++
pwmR /= 255;
pwmG /= 255;
pwmB /= 255;

ledR.write(1.0 - pwmR);
ledG.write(1.0 - pwmG);
ledB.write(1.0 - pwmB);
```
Como PWM solo funciona con valores de 0 a 1 es necesario dividir entre 255 (Mayor intensidad de cada led en RGB) cada valor del código RGB ingresado, esta división se determinó luego de aplicar una regla de 3. Por último, Se le manda a cada led el porcentaje de intensidad que debe de tener, en este caso, toca hacer el complemento por como lo determina c++ de que 1 es apagado y 0 encendido

## **Pruebas del código día martes**

#### **Punto 1**
Este punto no alcanzamos a realizar prueba para saber como era el funcionamiento, en el momento en el que ibamos a realizar la prueba ya no contabamos con la tarjeta. Motivo por el cuál no sabemos si puede tener algún bug o si este código funciona sin problemas

#### **Punto 2**
Solo logramos realizar una prueba, en esta prueba se alcanzaba a pedir la cantidad de temperaturas con las que se deseaba trabajar, pero en la parte donde se tenía que pedir cada temperatura se saltaba esa parte y arrojaba directamente el promedio y la desviación estándar, dando como resultado 0, que es el valor en el cuál se inicializa las variables.

#### **Punto 3**
La prueba de este punto fue exitosa, funcionaba tal cual se esperaba, no se presentaron problemas con respecto al punto pero en su momento si con la forma de acceder al condicional para ejecutar esta solución. Al final se logró corregir el problema y quedó la solución completa

## **Pruebas del código día jueves**
Se hizo las pruebas correspondientes a los 3 puntos y todas dieron el resaltado que se esperaba. 
Cuando hablamos especificamente del problema del punto 2, el problema estaba en que teniamos la flag que se usa en el ```while(flag)``` en el cual se lee la entrada del teclado matricial llegaba en ```false``` y para entrar al ```while(flag)``` se necesitaba que la flag fuera ```true```.

# **Parcial presentado por:**
Susana Uribe y Daniel Duque
