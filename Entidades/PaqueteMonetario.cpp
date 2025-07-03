#include "Interfaces/PaqueteMonetario.hpp"
#include <iostream>

std::string to_string(Estado estado) {
    switch (estado) {
        case Estado::Bueno:   return "Bueno";
        case Estado::Dañado:  return "Dañado";
        case Estado::Falso:   return "Falso";
        default:              return "Desconocido";
    }
}


PaqueteMonetario::PaqueteMonetario(ElementoMonetario* elemento, Estado estado, int cantidad)
    : elemento(elemento), estado(estado), cantidad(cantidad) {}

ElementoMonetario* PaqueteMonetario::getElemento() const {
    return elemento;
}

int PaqueteMonetario::getCantidad() const {
    return cantidad;
}

Estado PaqueteMonetario::getEstado() const {
    return estado;
}

void PaqueteMonetario::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void PaqueteMonetario::setEstado(Estado estado) {
    this->estado = estado;
}

void PaqueteMonetario::imprimir() const {

    std::cout << "Cantidad: " << cantidad << ", Estado: " << to_string(estado) << ", Elemento: ";
    if (elemento) elemento->imprimir();
    else std::cout << "(null)" << std::endl;
}
