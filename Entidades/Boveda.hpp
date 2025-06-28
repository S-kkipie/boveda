#pragma once
#include <string>
#include <vector>
#include "Plaza.hpp"
#include "Operacion.hpp"

class Boveda {
public:
    std::string nombre;
    Plaza* plaza;
    std::vector<Operacion*> operaciones;
};
