#include "Interfaces/EntidadBancaria.hpp"
#include "Interfaces/Operacion.hpp"

EntidadBancaria::EntidadBancaria(const std::string& nombre) : nombre(nombre) {}

std::string EntidadBancaria::getNombre() const {
    return nombre;
}

void EntidadBancaria::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void EntidadBancaria::agregarBoveda(Boveda* boveda) {
    bovedas.push_back(boveda);
}

void EntidadBancaria::agregarPlaza(Plaza* plaza) {
    plazas.push_back(plaza);
}

const std::vector<Boveda*>& EntidadBancaria::getBovedas() const {
    return bovedas;
}

const std::vector<Plaza*>& EntidadBancaria::getPlazas() const {
    return plazas;
}

void EntidadBancaria::registrarOperacion(Operacion* op) {
    operaciones.push_back(op);
}

const std::vector<Operacion*>& EntidadBancaria::getOperaciones() const {
    return operaciones;
}

void EntidadBancaria::imprimir() const {
    std::cout << "--- Detalles de la Entidad Bancaria ---" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Cantidad de bóvedas: " << bovedas.size() << std::endl;
    for (size_t i = 0; i < bovedas.size(); ++i) {
        std::cout << "  Bóveda " << i+1 << ": ";
        if (bovedas[i]) bovedas[i]->imprimirDetalles();
        else std::cout << "(null)" << std::endl;
    }
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
    std::cout << "----------------------------------------" << std::endl;
}
