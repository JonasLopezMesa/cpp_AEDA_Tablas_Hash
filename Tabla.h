//
//  Tabla.h
//  Tabla_Hash
//
//  Created by jonas on 02/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#ifndef __Tabla_Hash__Tabla__
#define __Tabla_Hash__Tabla__

#include <iostream>
using namespace std;
#include "Celda.h"
#include <vector>
#include <math.h>

struct t_busqueda {
    int _x;
    int _y;
    int _clave;
    int _comparaciones;
};

struct t_insert {
    int _x;
    int _y;
    int _clave;
    int _comparaciones;
};

class TABLA {
    vector<CELDA> hash_;
    int sz_;
    int sz_blq_;
    t_busqueda BUSQUEDA;
    t_insert INSERT;
public:
    TABLA(int n_celdas, int sz_bloques);
    void insert_p(int clave, int opc);
    int search(int clave, int opc);
    void mostrar_lista();
    void cargar_tabla(vector<int> banco, int registros_a_almacenar, int opc);
    
    int exp_lineal(int i);
    int exp_cuadratica(int i);
    int exp_d_doble(int i, int k);
    void redispersion();
    int get_sz();
    
    int b_exp_lineal(int i, int clave);
    int b_exp_cuadratica(int i, int clave);
    int b_exp_d_doble(int i, int clave);
    
    int calcular_elementos();
    void inicializar_busqueda();
    void inicializar_insert();
    
    t_busqueda& get_B();
    t_insert& get_I();
};

#endif /* defined(__Tabla_Hash__Tabla__) */
