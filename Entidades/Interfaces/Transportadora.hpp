#pragma once
#include <string>
#include <vector>
#include <iostream>

class Operacion;
class Plaza;

class Transportadora {
private:
    std::string nombre;
    std::vector<Plaza*> plazas;
    std::vector<Operacion*> operaciones;
public:
    Transportadora(const std::string& nombre);
    std::string getNombre() const;
    void setNombre(const std::string& nombre);
    void agregarPlaza(Plaza* plaza);
    const std::vector<Plaza*>& getPlazas() const;
    void registrarOperacion(Operacion* op);
    const std::vector<Operacion*>& getOperaciones() const;
    void imprimir() const;
};
