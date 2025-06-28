#include "Interfaces/ElementoMonetario.hpp"
#include <iostream>

ElementoMonetario::ElementoMonetario(double valor, Tipo tipo)
    : valor(valor), tipo(tipo) {}

double ElementoMonetario::getValor() const {
    return valor;
}


Tipo ElementoMonetario::getTipo() const {
    return tipo;
}

void ElementoMonetario::setValor(double valor) {
    this->valor = valor;
}

void ElementoMonetario::setTipo(Tipo tipo) {
    this->tipo = tipo;
}

void ElementoMonetario::imprimir() const {
    std::cout << "[ElementoMonetario] Valor: " << valor
              << ", Tipo: " << static_cast<int>(tipo) << std::endl;
}
