#include "ExcepcionBovedas.hpp"

class ExcepcionEntidadNoEncontrada : public ExcepcionBovedas {
public:
    ExcepcionEntidadNoEncontrada(const std::string& msg) : ExcepcionBovedas(msg) {}
};

class ExcepcionOperacionInvalida : public ExcepcionBovedas {
public:
    ExcepcionOperacionInvalida(const std::string& msg) : ExcepcionBovedas(msg) {}
};

class ExcepcionElementoMonetarioInvalido : public ExcepcionBovedas {
public:
    ExcepcionElementoMonetarioInvalido(const std::string& msg) : ExcepcionBovedas(msg) {}
};
