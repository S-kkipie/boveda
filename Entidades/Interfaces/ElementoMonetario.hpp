#pragma once
#include <string>
#include <iostream>


enum class Tipo {
    Billete,
    Moneda,
    Joya,
    Bono,
    Otro
};

class ElementoMonetario {
protected:
    double valor;
    Tipo tipo;
public:
    ElementoMonetario(double valor,  Tipo tipo);
    virtual ~ElementoMonetario() = default;
    double getValor() const;
    Tipo getTipo() const;
    void setValor(double valor);
    void setTipo(Tipo tipo);
    void imprimir() const;
};

