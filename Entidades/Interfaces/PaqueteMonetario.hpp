#pragma once
#include <map>
#include <iostream>
#include "ElementoMonetario.hpp"

enum class Estado {
    Bueno,
    Dañado,
    Falso
};


class PaqueteMonetario {
private:
    ElementoMonetario* elemento;
    int cantidad;
    Estado estado;
public:
    PaqueteMonetario(ElementoMonetario* elemento, Estado estado, int cantidad);
    ElementoMonetario* getElemento() const;
    int getCantidad() const;
    void setCantidad(int cantidad);
    Estado getEstado() const;
    void setEstado(Estado estado);
    void imprimir() const;
};
