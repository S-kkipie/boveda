#pragma once
#include <string>
#include <vector>
#include "Boveda.hpp"
#include "Plaza.hpp"
#include "Operacion.hpp"

class EntidadBancaria {
public:
    std::string nombre;
    std::vector<Boveda*> bovedas;
    std::vector<Plaza*> plazas;
    std::vector<Operacion*> operaciones;
};
