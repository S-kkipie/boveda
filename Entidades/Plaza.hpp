#pragma once
#include <string>
#include <vector>
#include "Operacion.hpp"

class Plaza {
public:
    std::string nombre;
    std::vector<Operacion*> operaciones;
    // Métodos para registrar y consultar operaciones pueden agregarse aquí
};
