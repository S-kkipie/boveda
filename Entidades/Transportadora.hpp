#pragma once
#include <string>
#include <vector>
#include "Operacion.hpp"

class Transportadora {
public:
    std::string nombre;
    std::vector<Plaza*> plazas;
    
    std::vector<Operacion*> operaciones;
};
