/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <string>

using namespace std;


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define DEBOUNCE_DELAY    200ms
UnbufferedSerial serial(USBTX, USBRX, 9600);

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

DigitalIn rowPins[ROWS] = {D2, D3, D4, D5};
DigitalOut colPins[COLS] = {D6, D7, D8};

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

int main()
{

    cout << "Este programa tiene 3 funcionalidades, \nla primera es encontrar la pendiente y la interseccion dados dos puntos, \nla segunda es encontrar el promedio y la desviacion estandar dado un conjunto N de temperaturas. \nEl tercero, es para generar colores con el codigo RGB en el led. \nIngrese un numero (1, 2 o 3) dependiendo de la funcion que desea. \nIngrese * para limpiar la entrada actual y # como enter\n";
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
    
    if (opcion == "1#"){
        flag = true;
        cout << "Opcion seleccionada: Rectas \n";
        ThisThread::sleep_for(BLINKING_RATE);
        int x1=0;
        int x2=0;
        int y1=0;
        int y2=0;
        int m=0;
        int b=0;
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

        if (x1 == x2){
            cout <<"La pendiente = infinito:\n";
        }
        else if (y1 == y2){
            cout <<"La pendiente = 0:\n";
            b = y1;
            printf("El intercepto con y: %d\n", b);
        }
        else {
            m=(y2-y1)/(x2-x1);
            printf("La pendiente = %d\n", m);
            b= y1-m*x1;
            printf("El intercepto con y: %d\n", b);
        }
    }else if (opcion == "2#"){
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
    
    }else if (opcion == "3#"){
        cout << "Se ha seleccionado RGB\n";
        PwmOut ledR(LED1);
        PwmOut ledG(LED2);
        PwmOut ledB(LED3);

        float pwmR = 0.0;
        float pwmG = 0.0;
        float pwmB = 0.0;
        

        while (true){
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

            pwmR /= 255;
            pwmG /= 255;
            pwmB /= 255;

            ledR.write(1.0 - pwmR);
            ledG.write(1.0 - pwmG);
            ledB.write(1.0 - pwmB);
        }
    }else{
        cout << "Opcion no valida, reinicie la tarjeta \n";
    }
}
