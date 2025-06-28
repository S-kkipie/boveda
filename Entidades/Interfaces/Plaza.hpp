#pragma once
#include <string>
#include <vector>
#include <iostream>

class Operacion;

class Plaza {
private:
    std::string nombre;
    std::vector<Operacion*> operaciones;
public:
    Plaza(const std::string& nombre);
    std::string getNombre() const;
    void setNombre(const std::string& nombre);
    void registrarOperacion(Operacion* op);
    const std::vector<Operacion*>& getOperaciones() const;
    void imprimir() const;
};
