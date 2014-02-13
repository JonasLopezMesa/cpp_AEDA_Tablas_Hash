//
//  Celda.cpp
//  Tabla_Hash
//
//  Created by jonas on 02/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include "Celda.h"

CELDA::CELDA(int sz){
    bloque_.resize(sz);
    actual_ = 0;
    lleno_ = false;
    vacio_ = true;
}
void CELDA::set_bloque(int valor){
    if (lleno_ == false) {
        vacio_ = false;
        //cout << bloque_.size() << endl;
        bloque_[actual_] = valor;
        if (bloque_[actual_]!=0) {
            actual_=actual_+1;
        }
    }
    if (actual_ == bloque_.size()) {
        lleno_ = true;
    }
}
void CELDA::set_bloque2_0(int i){
    bloque_[i] = 0;
}
void CELDA::set_size(int sz){
    bloque_.resize(sz);
}
int CELDA::get_actual(){
    return actual_;
}
int CELDA::get_bloque(int i){
    return bloque_[i];
}

void CELDA::set_lleno(bool ll){
    lleno_ = ll;
}
void CELDA::set_vacio(bool v){
    vacio_ = v;
}
void CELDA::set_actual(int a){
    actual_ = a;
}
bool CELDA::get_vacio(){
    return vacio_;
}



int CELDA::get_sz_bloque(){
    return bloque_.size();
}
bool CELDA::get_lleno(){
    return lleno_;
}