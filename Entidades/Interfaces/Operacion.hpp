#pragma once
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>


class Transportadora;
class Plaza;
class EntidadBancaria;
class PaqueteMonetario;


enum class TipoOperacion {
    Deposito,
    Retiro,
    Transferencia,
    Canje,
    Otro
};


class Operacion {
private:
    std::time_t fecha;
    std::vector<PaqueteMonetario*> paquetesMonetarios;
    TipoOperacion tipoOperacion;
    Transportadora* transportadora;
    Plaza* plazaOrigen;
    Plaza* plazaDestino;
    EntidadBancaria* entidadOrigen;
    EntidadBancaria* entidadDestino;
public:
    Operacion(std::time_t fecha, TipoOperacion tipoOperacion,
              Transportadora* transportadora, Plaza* plazaOrigen, Plaza* plazaDestino,
              EntidadBancaria* entidadOrigen, EntidadBancaria* entidadDestino);
    std::time_t getFecha() const;
    TipoOperacion getTipoOperacion() const;
    void agregarPaqueteMonetario(PaqueteMonetario* paquete);
    const std::vector<PaqueteMonetario*>& getPaquetesMonetarios() const;
    Transportadora* getTransportadora() const;
    Plaza* getPlazaOrigen() const;
    Plaza* getPlazaDestino() const;
    EntidadBancaria* getEntidadOrigen() const;
    EntidadBancaria* getEntidadDestino() const;
    void imprimir() const;
};
