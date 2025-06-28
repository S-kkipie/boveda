#pragma once
#include <string>
#include <iostream>

enum class Estado {
    Bueno,
    Dañado,
    Falso
};

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
    Estado estado;
    Tipo tipo;
public:
    ElementoMonetario(double valor, Estado estado, Tipo tipo);
    virtual ~ElementoMonetario() = default;
    double getValor() const;
    Estado getEstado() const;
    Tipo getTipo() const;
    void setValor(double valor);
    void setEstado(Estado estado);
    void setTipo(Tipo tipo);
    void imprimir() const;
};

