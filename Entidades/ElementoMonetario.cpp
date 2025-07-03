#include "Interfaces/ElementoMonetario.hpp"
#include <iostream>


std::string to_string(Tipo tipo) {
    switch (tipo) {
        case Tipo::Billete: return "Billete";
        case Tipo::Moneda:  return "Moneda";
        case Tipo::Joya:    return "Joya";
        case Tipo::Bono:    return "Bono";
        case Tipo::Otro:    return "Otro";
        default:            return "Desconocido";
    }
}

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
    std::cout << " Valor: " << valor
              << ", Tipo: " << to_string(tipo) << std::endl;
}
