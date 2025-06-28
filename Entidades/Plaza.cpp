#include "Interfaces/Plaza.hpp"
#include "Interfaces/Operacion.hpp"

Plaza::Plaza(const std::string& nombre) : nombre(nombre) {}

std::string Plaza::getNombre() const {
    return nombre;
}

void Plaza::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Plaza::registrarOperacion(Operacion* op) {
    operaciones.push_back(op);
}

const std::vector<Operacion*>& Plaza::getOperaciones() const {
    return operaciones;
}

void Plaza::imprimir() const {
    std::cout << "--- Detalles de la Plaza ---" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Cantidad de operaciones: " << operaciones.size() << std::endl;
    for (size_t i = 0; i < operaciones.size(); ++i) {
        std::cout << "  Operacion " << i+1 << ": ";
        if (operaciones[i]) operaciones[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}
