#include "Interfaces/Boveda.hpp"
#include <iostream>
#include "Interfaces/Operacion.hpp"
#include "Interfaces/PaqueteMonetario.hpp"
#include "Interfaces/Plaza.hpp"

Boveda::Boveda(const std::string& nombre, Plaza* plaza) : nombre(nombre), plaza(plaza) {}

std::string Boveda::getNombre() const {
    return nombre;
}

void Boveda::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

Plaza* Boveda::getPlaza() const {
    return plaza;
}

std::vector<PaqueteMonetario*> Boveda::getPaquetesMonetarios() const {
    return paquetesMonetarios;
}

void Boveda::setPlaza(Plaza* plaza) {
    this->plaza = plaza;
}

void Boveda::registrarOperacion(Operacion* op) {
    operaciones.push_back(op);
}

const std::vector<Operacion*>& Boveda::getOperaciones() const {
    return operaciones;
}

void Boveda::imprimir() const {
    std::cout << "--- Detalles de la Bóveda ---" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Plaza: " << (plaza ? plaza->getNombre() : "(null)") << std::endl;
    std::cout << "Cantidad de paquetes monetarios: " << paquetesMonetarios.size() << std::endl;
    for (size_t i = 0; i < paquetesMonetarios.size(); ++i) {
        std::cout << "  Paquete " << i+1 << ": ";
        if (paquetesMonetarios[i]) paquetesMonetarios[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "Cantidad de operaciones: " << operaciones.size() << std::endl;
    for (size_t i = 0; i < operaciones.size(); ++i) {
        std::cout << "  Operacion " << i+1 << ": ";
        if (operaciones[i]) operaciones[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}
