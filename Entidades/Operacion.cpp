#include "Interfaces/Operacion.hpp"
#include <iomanip>
#include "Interfaces/Transportadora.hpp"
#include "Interfaces/EntidadBancaria.hpp"
#include "Interfaces/PaqueteMonetario.hpp"


#include "Interfaces/Plaza.hpp"
#include <algorithm>
#include <random>

inline std::string to_string(TipoOperacion op) {
    switch (op) {
        case TipoOperacion::Deposito:      return "Depósito";
        case TipoOperacion::Retiro:        return "Retiro";
        case TipoOperacion::Transferencia: return "Transferencia";
        case TipoOperacion::Canje:         return "Canje";
        case TipoOperacion::Otro:          return "Otro";
        default:                           return "Desconocido";
    }
}

Operacion::Operacion(std::time_t fecha, TipoOperacion tipoOperacion,
                     Transportadora* transportadora, Plaza* plazaOrigen, Plaza* plazaDestino,
                     EntidadBancaria* entidadOrigen, EntidadBancaria* entidadDestino)
    : fecha(fecha), tipoOperacion(tipoOperacion), transportadora(transportadora),
      plazaOrigen(plazaOrigen), plazaDestino(plazaDestino),
      entidadOrigen(entidadOrigen), entidadDestino(entidadDestino) {}

std::time_t Operacion::getFecha() const {
    return fecha;
}

TipoOperacion Operacion::getTipoOperacion() const {
    return tipoOperacion;
}

void Operacion::agregarPaqueteMonetario(PaqueteMonetario* paquete) {
    paquetesMonetarios.push_back(paquete);
}

const std::vector<PaqueteMonetario*>& Operacion::getPaquetesMonetarios() const {
    return paquetesMonetarios;
}

Transportadora* Operacion::getTransportadora() const {
    return transportadora;
}

Plaza* Operacion::getPlazaOrigen() const {
    return plazaOrigen;
}

Plaza* Operacion::getPlazaDestino() const {
    return plazaDestino;
}

EntidadBancaria* Operacion::getEntidadOrigen() const {
    return entidadOrigen;
}

EntidadBancaria* Operacion::getEntidadDestino() const {
    return entidadDestino;
}

void Operacion::imprimir() const {
    std::tm* tm_local = std::localtime(&fecha);
    std::cout << "--- Detalles de la Operacion ---" << std::endl;
    std::cout << "Fecha: " << std::put_time(tm_local, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "Tipo de operacion: " << to_string(tipoOperacion) << std::endl;
    std::cout << "Transportadora: " << (transportadora ? transportadora->getNombre() : "(null)") << std::endl;
    std::cout << "Plaza Origen: " << (plazaOrigen ? plazaOrigen->getNombre() : "(null)") << std::endl;
    std::cout << "Plaza Destino: " << (plazaDestino ? plazaDestino->getNombre() : "(null)") << std::endl;
    std::cout << "Entidad Origen: " << (entidadOrigen ? entidadOrigen->getNombre() : "(null)") << std::endl;
    std::cout << "Entidad Destino: " << (entidadDestino ? entidadDestino->getNombre() : "(null)") << std::endl;
    std::cout << "Cantidad de paquetes monetarios: " << paquetesMonetarios.size() << std::endl;
    for (size_t i = 0; i < paquetesMonetarios.size(); ++i) {
        std::cout << "  Paquete " << i+1 << ": ";
        if (paquetesMonetarios[i]) paquetesMonetarios[i]->imprimir();
        else std::cout << "(null)" << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

