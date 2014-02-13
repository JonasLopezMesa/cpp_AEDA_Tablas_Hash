//
//  Celda.h
//  Tabla_Hash
//
//  Created by jonas on 02/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#ifndef __Tabla_Hash__Celda__
#define __Tabla_Hash__Celda__

#include <iostream>
using namespace std;
#include <vector>

class CELDA {
    vector<int> bloque_;
    int actual_;
    bool lleno_;
    bool vacio_;
public:
    CELDA(int sz=3);
    void set_bloque(int valor);
    void set_size(int sz);
    int get_bloque(int i);
    int get_sz_bloque();
    bool get_lleno();
    bool get_vacio();
    int get_actual();
    void set_bloque2_0(int i);
    
    void set_lleno(bool ll);
    void set_vacio(bool v);
    void set_actual(int a);
};

#endif /* defined(__Tabla_Hash__Celda__) */
