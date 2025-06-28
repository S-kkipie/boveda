#pragma once
#include <map>
#include <iostream>
#include "ElementoMonetario.hpp"

class PaqueteMonetario {
private:
    ElementoMonetario* elemento;
    int cantidad;
public:
    PaqueteMonetario(ElementoMonetario* elemento, int cantidad);
    ElementoMonetario* getElemento() const;
    int getCantidad() const;
    void setCantidad(int cantidad);
    void imprimir() const;
};
