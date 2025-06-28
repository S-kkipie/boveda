#include "Interfaces/ElementoMonetario.hpp"
#include <iostream>

ElementoMonetario::ElementoMonetario(double valor, Estado estado, Tipo tipo)
    : valor(valor), estado(estado), tipo(tipo) {}

double ElementoMonetario::getValor() const {
    return valor;
}

Estado ElementoMonetario::getEstado() const {
    return estado;
}

Tipo ElementoMonetario::getTipo() const {
    return tipo;
}

void ElementoMonetario::setValor(double valor) {
    this->valor = valor;
}

void ElementoMonetario::setEstado(Estado estado) {
    this->estado = estado;
}

void ElementoMonetario::setTipo(Tipo tipo) {
    this->tipo = tipo;
}

void ElementoMonetario::imprimir() const {
    std::cout << "[ElementoMonetario] Valor: " << valor
              << ", Estado: " << static_cast<int>(estado)
              << ", Tipo: " << static_cast<int>(tipo) << std::endl;
}
