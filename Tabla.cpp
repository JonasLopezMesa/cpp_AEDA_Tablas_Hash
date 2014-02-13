//
//  Tabla.cpp
//  Tabla_Hash
//
//  Created by jonas on 02/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include "Tabla.h"



int semilla_impar(int semilla){
    if (semilla%2 != 0) {
        return semilla;
    } else {
        return semilla+1;
    }
}
void TABLA::inicializar_busqueda(){
    BUSQUEDA._clave = 0;
    BUSQUEDA._comparaciones = 0;
    BUSQUEDA._x = -1;
    BUSQUEDA._y = -1;
}
void TABLA::inicializar_insert(){
    INSERT._clave = 0;
    INSERT._comparaciones = 0;
    INSERT._x = -1;
    INSERT._y = -1;
}

int TABLA::calcular_elementos(){
    int a = 0;
    for (int i = 0; i < hash_.size(); i++) {
        for (int j = 0; j < sz_blq_; j++) {
            if (hash_[i].get_bloque(j)!=0) {
                a = a+1;
            }
        }
    }
    return a;
}

TABLA::TABLA(int n_celdas, int sz_bloques){
    sz_=n_celdas;
    sz_blq_=sz_bloques;
    hash_.resize(n_celdas);
    for (int i = 0; i < n_celdas; i++) {
        hash_[i].set_size(sz_bloques);
    }
}
void TABLA::insert_p(int clave, int opc){
    srand(clave);
    inicializar_insert();
    INSERT._clave = clave;
    int rando = rand()%sz_-1;
    if (hash_[rando].get_lleno()==false) {
        INSERT._comparaciones = INSERT._comparaciones+1;
        hash_[rando].set_bloque(clave);
        //cout << "Elemento " << clave << " introducido en la posición [" << rando << "][" << hash_[rando].get_actual() << "]" << endl;
    } else {
        if (opc == 1 || opc == 4) {
            int x = exp_lineal(rando+1);
            hash_[x].set_bloque(clave);
            //cout << "Elemento " << clave << " introducido en la posición [" << x << "][" << hash_[x].get_actual() << "]" << endl;
        }
        if (opc == 2) {
            int x = exp_cuadratica(rando+1);
            hash_[x].set_bloque(clave);
            //cout << "Elemento " << clave << " introducido en la posición [" << x << "][" << hash_[x].get_actual() << "]" << endl;
        }
        if (opc == 3) {
            int x = exp_d_doble(rando, clave);
            hash_[x].set_bloque(clave);
            //cout << "Elemento " << clave << " introducido en la posición [" << x << "][" << hash_[x].get_actual() << "]" << endl;
        }
        //calcular fc
        int introducidos = calcular_elementos();
        float fc = ((float)introducidos)/(sz_*sz_blq_);
        if (opc == 4 && fc >= 0.5) {
            redispersion();
            //cout << "REDISPERSIÓN" << endl;
        }
    }
    
    
}
int TABLA::search(int clave, int opc){
    inicializar_busqueda();
    BUSQUEDA._clave = clave;
    srand(semilla_impar(clave));
    int loc = rand()%(sz_-1);
    //cout << "Debería encontrarse en la posición: " << loc << endl;
    for (int i = 0; i < sz_blq_; i++) {
        if (clave == hash_[loc].get_bloque(i)) {
            BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
            BUSQUEDA._x = loc; BUSQUEDA._y = i;
            //cout << "Se ha encontrado el elemento: " << BUSQUEDA._clave << " en la posición: [" << BUSQUEDA._x << "][" << BUSQUEDA._y << "] Tras " << BUSQUEDA._comparaciones << " Comparaciones."<<  endl;
        } else if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1){
            //contador de comparaciones
            BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
        }
    }
    if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1) {
        //cout << "Si no está en la posición: " << loc << "Buscamos de forma ";
        if (opc == 1 || opc == 4) {
            //cout << "LINEAL para encontrar la solución" << endl;
            int p = b_exp_lineal(loc+1, clave);
            if (p != -1) {
                for (int j = 0; j < hash_[p].get_actual(); j++) {
                    if (clave == hash_[p].get_bloque(j)) {
                        BUSQUEDA._x = p; BUSQUEDA._y = j;
                        //cout << "Se ha encontrado el elemento: " << BUSQUEDA._clave << " en la posición: [" << BUSQUEDA._x << "][" << BUSQUEDA._y << "] Tras " << BUSQUEDA._comparaciones << " Comparaciones."<<  endl;
                    } 
                }
            }
        }
        if (opc == 2) {
            //cout << "CUADRÁTICA para encontrar la solución" << endl;
            int p = b_exp_cuadratica(loc+1, clave);
            if (p != -1) {
                for (int j = 0; j < hash_[p].get_actual(); j++) {
                    if (clave == hash_[p].get_bloque(j)) {
                        BUSQUEDA._x = p; BUSQUEDA._y = j;
                        //cout << "Se ha encontrado el elemento: " << BUSQUEDA._clave << " en la posición: [" << BUSQUEDA._x << "][" << BUSQUEDA._y << "] Tras " << BUSQUEDA._comparaciones << " Comparaciones."<<  endl;
                    }
                }
            }
        }
        if (opc == 3) {
            //cout << "de DISPERSIÓN DOBLE para encontrar la solución" << endl;
            int p = b_exp_d_doble(loc+1, clave);
            if (p != -1) {
                for (int j = 0; j < hash_[p].get_actual(); j++) {
                    if (clave == hash_[p].get_bloque(j)) {
                        BUSQUEDA._x = p; BUSQUEDA._y = j;
                        cout << "Se ha encontrado el elemento: " << BUSQUEDA._clave << " en la posición: [" << BUSQUEDA._x << "][" << BUSQUEDA._y << "] Tras " << BUSQUEDA._comparaciones << " Comparaciones."<<  endl;
                    }
                }
            }
        }
    }
    if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1) {
        cout << "NO se ha encontrado el elemento: " << BUSQUEDA._clave <<  " tras " << BUSQUEDA._comparaciones << " comparaciones."<<  endl;
    }
    return 0;
}

void TABLA::mostrar_lista(){
    for (int i = 0; i<hash_.size(); i++) {
        cout << "[" << i << "] ----> | ";
        for (int j=0; j<hash_[i].get_sz_bloque(); j++) {
            cout << "{" << hash_[i].get_bloque(j) << "} | ";
        }
        cout << endl;
    }
}

void TABLA::cargar_tabla(vector<int> banco, int registros_a_almacenar, int opc){
    int introducidos = 0, rando;
    for (int i = 0; introducidos <registros_a_almacenar; i++) {
        srand(semilla_impar(banco[i]));
        //cout << "SZ_" << sz_ << endl;
        rando = rand()%(sz_-1);
        if (hash_[rando].get_lleno()==false) {
            hash_[rando].set_bloque(banco[i]);
            //cout << "a" << endl;
            if (hash_[rando].get_bloque(hash_[rando].get_actual()-1)!=0) {
                //cout << "ELEMENTO INTRODUCIDO!!! " << "--- I: " << i << ", RANDO: " << rando << ", ID: " << banco[i] << endl;
                introducidos = introducidos+1;
            } else {
                i = i-1;
            }
        } else if (hash_[rando].get_lleno()==true){
            if (opc == 1 || opc == 4) {
                int x = exp_lineal(rando+1);
                if (x != -1) {
                    //cout << "X: " << x << endl;
                    hash_[x].set_bloque(banco[i]);
                    //cout << "b" << endl;
                    if (hash_[x].get_bloque(hash_[x].get_actual()-1)!=0) {
                        //cout << "ELEMENTO INTRODUCIDO!!! " << "--- I: " << i << ", X: " << x << ", ID: " << banco[i] << endl;
                        introducidos = introducidos+1;
                    } else {
                        i = i-1;
                    }
                }
            }
            if (opc == 2) {
                int x = exp_cuadratica(rando+1);
                if (x != -1) {
                    hash_[x].set_bloque(banco[i]);
                    if (hash_[x].get_bloque(hash_[x].get_actual()-1)!=0) {
                        introducidos = introducidos+1;
                    } else {
                        i = i-1;
                    }
                }
            }
            if (opc == 3) {
                int x = exp_d_doble(rando, banco[i]);
                if (x != -1) {
                    hash_[x].set_bloque(banco[i]);
                    if (hash_[x].get_bloque(hash_[x].get_actual()-1)!=0) {
                        introducidos = introducidos+1;
                    } else {
                        i = i-1;
                    }
                }
            }
        }
        float fc = ((float)introducidos)/(sz_*sz_blq_);
        //cout << "INTroducidos= " << introducidos << "/( " << sz_ << " * " << sz_blq_ << " )" << endl;
        //cout << fc << endl;
            if (opc == 4 && fc >= 0.5) {
                //cout << "RE-DISPERSIÓN" << endl;
                redispersion();
            }
        //}
    }
    //cout << "Elementos introducidos: " << introducidos << endl;
}

int TABLA::exp_lineal(int i){
    int a = 0; int b = 0;
    for (;a==0;i++) {
        //cout << i << endl;
        if (hash_[i%sz_].get_lleno()==false) {
            INSERT._comparaciones = INSERT._comparaciones+1;
            return i;
            a = 1;
        } else{
            INSERT._comparaciones = INSERT._comparaciones+1;
        }
        /*if (i == hash_.size()-1) {
            i = -1;
        }*/
        if (b == hash_.size()) {
            a=1;
        }
        b=b+1;
    }
    return -1;
}
int TABLA::exp_cuadratica(int i){
    //cout << "EXPLORACIÓN CUADRÁTICA" << endl;
    int a = 0; int b = 0; int j = i;
    for (; a==0; j++) {
        int x = i+pow(j, 2);
        if (hash_[x%hash_.size()-1].get_lleno()==false) {
            INSERT._comparaciones = INSERT._comparaciones+1;
            return x%hash_.size()-1;
            a = 1;
        } else {
            INSERT._comparaciones = INSERT._comparaciones+1;
        }
        if (b == hash_.size()) {
            a=1;
        }
        b=b+1;
    }
    return -1;
}
int TABLA::exp_d_doble(int i, int k){
    //cout << "EXPLORACIÓN DOBLE" << endl;
    int a = 0; int b = 0;
    if (hash_[k%hash_.size()].get_lleno()==false) { 
        return k%hash_.size();
    } else {
        int x = k%hash_.size();
        int d = k/hash_.size();
        if (d%2==0) {
            d = d+1;
        }
        for (;a == 0;x=x+d) {
            if (hash_[x%hash_.size()].get_lleno()==false) {
                INSERT._comparaciones = INSERT._comparaciones+1;
                return x%hash_.size();
                a = 1;
            } else{
                INSERT._comparaciones = INSERT._comparaciones+1;
            }
            if (b == hash_.size()) {
                a = 1;
            }
            b = b+1;
        }
    }
    return -1;
}
void TABLA::redispersion(){
    int sz=hash_.size()*2;
    bool primo = true;
    for (int divisor=2; divisor<=sqrt(sz); divisor++) {
        if (sz%divisor==0) {
            primo = false;
        }
    }
    if (primo==false) {
        int a = 0; int primo1;
        while (a == 0) {
            sz = sz+1;
            primo = true;
            for (int divisor=2; divisor<=sqrt(sz); divisor++) {
                if (sz%divisor==0) {
                    primo = false;
                }
            }
            if (primo == true) {
                a = 1;
            }
        }
    }
    int tm = hash_.size();
    //cout << "TM = " << tm << " Tamaño del bloque = " << hash_[0].get_sz_bloque() << endl;
    TABLA red(tm,hash_[0].get_sz_bloque());
    for (int i = 0; i < hash_.size(); i++) {
        for (int j = 0; j < hash_[i].get_actual(); j++) {
            red.hash_[i].set_bloque(hash_[i].get_bloque(j));
        }
    }
    int bloq = hash_[0].get_sz_bloque();
    hash_.resize(sz);
    for (int i = 0; i < hash_.size(); i++) {
        hash_[i].set_size(bloq);
        sz_=sz;
        hash_[i].set_lleno(false);
        hash_[i].set_vacio(true);
        hash_[i].set_actual(0);
        for (int x = 0; x < bloq; x++) {
            hash_[i].set_bloque2_0(x);
        }
    }
    //mostrar_lista();
    
    //cout << "SZ = " << sz << " Tamaño del bloque = " << hash_[0].get_sz_bloque() << endl;
    for (int i = 0; i < red.hash_.size(); i++) {
        
        /*cout << "I: " << i << " - VACÍO: " << hash_[i].get_vacio() << endl;
        if (hash_[i].get_vacio() == false) {
            cout << "BÓRRALO " << endl;
            for (int x = 0;x < sz_blq_; x++) {
                hash_[i].set_bloque2_0(x);
            }
        }*/
        for (int j = 0; j < red.hash_[i].get_actual(); j++) {
            //cout << j << "Z" << endl;
            //cout << "I: " << i << endl;
            srand(semilla_impar(red.hash_[i].get_bloque(j)));
            //cout << j << "a"<< endl;
            int rando = rand()%(sz_-1);
            if (hash_[rando].get_lleno()==false) {
                hash_[rando].set_bloque(red.hash_[i].get_bloque(j));
                //cout << j << "b"<< endl;
            } else if (hash_[rando].get_lleno()==true){
                int x = exp_lineal(rando);
                //cout << j << "b1"<< endl;
                if (x != -1) {
                    hash_[x].set_bloque(red.hash_[i].get_bloque(j));
                    //cout << j << "c"<< endl;
                }
            }
        }
    }
}


int TABLA::b_exp_lineal(int i, int clave){
    //cout << "BÚSQUEDA LINEAL... " << endl;
    int a = 0;
    for (; a==0; i++) {
        for (int j = 0 ; j < hash_[i].get_actual(); j++) {
            if (hash_[i].get_bloque(j) == clave) {
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
                return i;
            } else if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1){
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
            }
        }
        if (hash_[i].get_lleno()==false) {
            return -1;
        }
    }
    return -1;
}
int TABLA::b_exp_cuadratica(int i, int clave){
    int a = 0; int j = i;
    for (; a==0; j++) {
        int x = i+pow(j, 2);
        for (int l = 0; l < hash_[x].get_actual(); l++) {
            if (hash_[x].get_bloque(l)==clave) {
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
                return i;
            } else if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1){
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
            }
        }
        if (hash_[i].get_lleno()==false) {
            return -1;
        }
    }
    return -1;
}
int TABLA::b_exp_d_doble(int i, int clave){
    int a = 0;
    int x = clave%hash_.size();
    int d = clave/hash_.size();
    ////////////////////////////////////////////////////////////
    d = d%hash_.size(); //CORRECCIÓN: ajustarlo al tamaño de la tabla antes de meterlo en el for.
    ////////////////////////////////////////////////////////////
    cout << d << endl;
    if (d%2==0) {
        d = d+1;
    }
    for (; a == 0; x=x+d) {
        for (int j = 0; j < hash_[x%hash_.size()].get_actual(); j++) {
            if (hash_[x%hash_.size()].get_bloque(j) == clave) {
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
                return x%hash_.size();
            } else if (BUSQUEDA._x == -1 && BUSQUEDA._y == -1){
                BUSQUEDA._comparaciones = BUSQUEDA._comparaciones+1;
            }
        }
        if (hash_[x%hash_.size()].get_lleno()==false) {
            return -1;
        }
    }
}


t_busqueda& TABLA::get_B(){
    return BUSQUEDA;
}
t_insert& TABLA::get_I(){
    return INSERT;
}
int TABLA::get_sz(){
    return sz_;
}