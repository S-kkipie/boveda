#pragma once
#include <string>

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
public:
    double valor;
    Estado estado;
    Tipo tipo;
    virtual ~ElementoMonetario() = default;
};

