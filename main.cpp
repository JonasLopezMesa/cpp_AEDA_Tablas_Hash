//
//  main.cpp
//  Tabla_Hash
//
//  Created by jonas on 02/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include <iostream>
#include <time.h>
using namespace std;
#include "Tabla.h"
#include <string>
#include <iomanip>
#include <stdio.h>


void crear_banco_pruebas(vector<int> &banco, int sz){
    srand(time(NULL));
    banco.resize(sz);
    for (int i = 0; i<banco.size(); i++) {
        banco[i] = 25000001+rand()%(75000001-25000001);
    }
}
void menu(int &n_celdas, int &sz_bloques, int &m_exploracion, float &factor_carga, int &n_pruebas){
    cout << "Introduce el número de CELDAS: ";
    cin >> n_celdas;
    bool primo = true;
    for (int divisor=2; divisor<=sqrt(n_celdas); divisor++) {
        if (n_celdas%divisor==0) {
            primo = false;
        }
    }
    if (primo==false) {
        int a = 0; int primo1;
        while (a == 0) {
            n_celdas = n_celdas+1;
            primo = true;
            for (int divisor=2; divisor<=sqrt(n_celdas); divisor++) {
                if (n_celdas%divisor==0) {
                    primo = false;
                }
            }
            if (primo == true) {
                a = 1;
            }
        }
        cout << "No se ha introducido un número primo." << endl;
        cout << "Se ha cambiado el tamaño de la tabla a " << n_celdas << " celdas." << endl;
    }
    cout << "Introduce el tamaño de los BLOQUES: ";
    cin >> sz_bloques;
    cout << "Elige el método de exploración:" << endl;
    cout << "       1. Exploración Lineal." << endl;
    cout << "       2. Exploración Cuadrática." << endl;
    cout << "       3. Dispersión doble." << endl;
    cout << "       4. Re-dispersión." << endl;
    cin >> m_exploracion;
    cout << "Introduce el factor de carga: ";
    cin >> factor_carga;
    cout << "Introduce el número de pruebas (búsquedas e inserciones) a realizar: ";
    cin >> n_pruebas;
}
int calculo_n_inserciones(float factor_carga, int n_celdas, int sz_bloques){
    return factor_carga*(n_celdas*sz_bloques);
}
void presentacion(int n_celdas, int sz_bloques, int m_exploracion, float factor_carga, int n_pruebas, int minimo_b, float media_b, int maximo_b, int minimo_i, float media_i, int maximo_i){
    cout << setfill('0');
    string exploracion;
    if (m_exploracion == 1) {
        exploracion = "Exploración Lineal";
    }
    if (m_exploracion == 2) {
        exploracion = "Exploración Cuadrática";
    }
    if (m_exploracion == 3) {
        exploracion = "Exploración de Dispersión Doble";
    }
    if (m_exploracion == 4) {
        exploracion = "Exploración con Re-Dispersión";
    }
    cout << "RESULTADOS: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Celdas: " << '\t' << '\t' << n_celdas << endl;
    cout << "Bloques: " << '\t' << '\t' << sz_bloques << endl;
    cout << "Exploración: " << '\t' << exploracion << endl;
    cout << "Carga: " << '\t' << '\t' << '\t' << factor_carga << endl;
    cout << "Pruebas: " << '\t' << '\t' << n_pruebas << endl;
    cout << endl << endl << endl;
    cout << "Número de comparaciones: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << '\t' << '\t' << '\t' << '\t' << "Mínimo" << '\t' << '\t' << "Media" << '\t' << '\t' << "Máximo" << endl;
    cout << "Búsquedas: " << '\t' << '\t' << setw(5) << minimo_b << '\t' << '\t' << setw(5) << media_b << '\t' << '\t' << setw(5) << maximo_b << endl;
    cout << "Inserciones: " << '\t' << setw(5) << minimo_i << '\t' << '\t' << setw(5) << media_i << '\t' << '\t' << setw(5) << maximo_i << endl;
}
int calculo_minimo(int a, int min){
    if (a < min) {
        return a;
    } else {
        return min;
    }
}
int calculo_maximo(int a, int max){
    if (a > max) {
        return a;
    } else {
        return max;
    }
}
float calculo_media(int* valores){
    int x = 0; float media = 0; int div= 0;
    while (valores[x] != 0) {
        media = media + valores[x];
        div = div+1;
        x = x+1;
    }
    media = ((float)media)/div;
    return media;
}
float calculo_factor_C(int almacenados, int sz){
    return ((float)almacenados)/sz;
}
bool mayor(float a, float b, float precision){
    if ((a-b) > precision) {
        return true;
    } else
    {
        return false;
    }
}



int main()
{
    int n_celdas,sz_bloques,m_exploracion,n_pruebas;
    int registros_a_almacenar;
    float factor_carga, media_b, media_i;
    int minimo_b, maximo_b, minimo_i, maximo_i;
    menu(n_celdas,sz_bloques,m_exploracion,factor_carga,n_pruebas);
    for (int i= 0; i < 60; i++) {
        cout << endl;
    }
    //Crear banco de pruebas
    vector<int> BANCO;
    crear_banco_pruebas(BANCO, (n_celdas*sz_bloques)+10+n_pruebas);
    //Crear la tabla
    TABLA tabla(n_celdas,sz_bloques);
    
    registros_a_almacenar = calculo_n_inserciones(factor_carga, n_celdas, sz_bloques);
    //cout << "REGISTROS A ALMACENAR: " << registros_a_almacenar << endl << endl;
    tabla.cargar_tabla(BANCO, registros_a_almacenar, m_exploracion);
    
    int z =n_celdas*sz_bloques;
    srand(time(NULL));
    int j;
    minimo_b = minimo_i = 50000;
    maximo_b = maximo_i = 0;
    
    int valores[n_pruebas];
    int valores_i[n_pruebas];
    for (int i = 0; i < n_pruebas; i++) {
        valores[i] = 0;
        valores_i[i]=0;
    }
    int np = n_pruebas;
    float f = 0.01;
    float nf = calculo_factor_C(registros_a_almacenar, n_celdas*sz_bloques);
    while (mayor(calculo_factor_C(registros_a_almacenar+np, n_celdas*sz_bloques), nf, f)==true) {
        //cout << "FACTOR malo: " << calculo_factor_C(registros_a_almacenar+np, n_celdas*sz_bloques) << endl;
        //cout << "FACTOR bueno: " << nf << endl;
        
        np = np-1;
    }
    
    if (np != n_pruebas) {
        cout << "Para no alterar el factor de carga, se ha reducido el número de inserciones a: " << np << endl;
    }
    
    for (int i = 0; i < n_pruebas; i++) {
        j = rand()%z;
        //cout << "J: " << j << " ID: " << BANCO[j] << endl;
        tabla.search(BANCO[j], m_exploracion);
        valores[i] = tabla.get_B()._comparaciones;
        minimo_b = calculo_minimo(tabla.get_B()._comparaciones, minimo_b);
        maximo_b = calculo_maximo(tabla.get_B()._comparaciones, maximo_b);
        media_b = calculo_media(valores);
    }
    for (int i = 0; i < np; i++) {
        //cout << i << endl;
        tabla.insert_p(BANCO[z], m_exploracion);
        valores_i[i] = tabla.get_I()._comparaciones;
        minimo_i = calculo_minimo(tabla.get_I()._comparaciones, minimo_i);
        maximo_i = calculo_maximo(tabla.get_I()._comparaciones, maximo_i);
        media_i = calculo_media(valores_i);
        z = z+1;
    }
    
    tabla.mostrar_lista();
    nf = calculo_factor_C(registros_a_almacenar, n_celdas*sz_bloques);
    presentacion(tabla.get_sz(), sz_bloques, m_exploracion, nf, n_pruebas, minimo_b, media_b, maximo_b, minimo_i, media_i, maximo_i);
    
    
    
    
    return 0;
}

