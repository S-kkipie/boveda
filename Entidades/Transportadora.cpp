#include "Interfaces/Transportadora.hpp"
#include "Interfaces/Plaza.hpp"
#include "Interfaces/Operacion.hpp"
Transportadora::Transportadora(const std::string& nombre) : nombre(nombre) {}

std::string Transportadora::getNombre() const {
    return nombre;
}

void Transportadora::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Transportadora::agregarPlaza(Plaza* plaza) {
    plazas.push_back(plaza);
}

const std::vector<Plaza*>& Transportadora::getPlazas() const {
    return plazas;
}

void Transportadora::registrarOperacion(Operacion* op) {
    operaciones.push_back(op);
}

const std::vector<Operacion*>& Transportadora::getOperaciones() const {
    return operaciones;
}

void Transportadora::imprimir() const {
    std::cout << "--- Detalles de la Transportadora ---" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Cantidad de plazas: " << plazas.size() << std::endl;
    for (size_t i = 0; i < plazas.size(); ++i) {
        std::cout << "  Plaza " << i+1 << ": ";
        if (plazas[i]) plazas[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "Cantidad de operaciones: " << operaciones.size() << std::endl;
    for (size_t i = 0; i < operaciones.size(); ++i) {
        std::cout << "  Operacion " << i+1 << ": ";
        if (operaciones[i]) operaciones[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}
