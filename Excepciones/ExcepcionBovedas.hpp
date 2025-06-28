#pragma once
#include <exception>
#include <string>

class ExcepcionBovedas : public std::exception {
public:
    std::string mensaje;
    ExcepcionBovedas(const std::string& msg) : mensaje(msg) {}
    const char* what() const noexcept override { return mensaje.c_str(); }
};

class ExcepcionSaldoInsuficiente : public ExcepcionBovedas {
public:
    ExcepcionSaldoInsuficiente(const std::string& msg) : ExcepcionBovedas(msg) {}
};

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
