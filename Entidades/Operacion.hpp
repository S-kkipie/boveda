#pragma once
#include <string>
#include <ctime>
#include <map>
#include "Transportadora.hpp"
#include "Plaza.hpp"
#include "EntidadBancaria.hpp"
#include "PaqueteMonetario.hpp"

enum class TipoOperacion {
    Deposito,
    Retiro,
    Transferencia,
    Canje,
    Otro
};


class Operacion {
public:
    std::time_t fecha;
    std::vector<PaqueteMonetario*> paquetesMonetarios;
    TipoOperacion tipoOperacion;
    Transportadora* transportadora;
    Plaza* plazaOrigen;
    Plaza* plazaDestino;
    EntidadBancaria* entidadOrigen;
    EntidadBancaria* entidadDestino;
};
