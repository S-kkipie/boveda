#include "Interfaces/PaqueteMonetario.hpp"
#include <iostream>

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

    std::cout << "Cantidad: " << cantidad << ", Estado: " << static_cast<int>(estado) << ", Elemento: ";
    if (elemento) elemento->imprimir();
    else std::cout << "(null)" << std::endl;
}
