#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Boveda.hpp"
#include "Plaza.hpp"

class Operacion;


class EntidadBancaria {
private:
    std::string nombre;
    std::vector<Boveda*> bovedas;
    std::vector<Plaza*> plazas;
    std::vector<Operacion*> operaciones;
public:
    EntidadBancaria(const std::string& nombre);
    std::string getNombre() const;
    void setNombre(const std::string& nombre);
    void agregarBoveda(Boveda* boveda);
    void agregarPlaza(Plaza* plaza);
    const std::vector<Boveda*>& getBovedas() const;
    const std::vector<Plaza*>& getPlazas() const;
    void registrarOperacion(Operacion* op);
    const std::vector<Operacion*>& getOperaciones() const;
    void imprimir() const;
};
