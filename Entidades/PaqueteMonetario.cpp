#include "Interfaces/PaqueteMonetario.hpp"
#include <iostream>

PaqueteMonetario::PaqueteMonetario(ElementoMonetario* elemento, int cantidad)
    : elemento(elemento), cantidad(cantidad) {}

ElementoMonetario* PaqueteMonetario::getElemento() const {
    return elemento;
}

int PaqueteMonetario::getCantidad() const {
    return cantidad;
}

void PaqueteMonetario::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void PaqueteMonetario::imprimir() const {
    std::cout << "Cantidad: " << cantidad << ", Elemento: ";
    if (elemento) elemento->imprimir();
    else std::cout << "(null)" << std::endl;
}
