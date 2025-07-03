#pragma once
#include <string>
#include <vector>
#include <iostream>

class Plaza;
class Operacion;
class PaqueteMonetario;

class Boveda {
private:
    std::string nombre;
    Plaza* plaza;
    std::vector<PaqueteMonetario*> paquetesMonetarios;
    std::vector<Operacion*> operaciones;
public:
    Boveda(const std::string& nombre, Plaza* plaza);
    std::string getNombre() const;
    void setNombre(const std::string& nombre);
    Plaza* getPlaza() const;
    std::vector<PaqueteMonetario*>& getPaquetesMonetarios();
    void setPlaza(Plaza* plaza);
    void registrarOperacion(Operacion* op);
    const std::vector<Operacion*>& getOperaciones() const;
    void imprimirDetalles() const;
    void imprimirOperaciones() const;
};
