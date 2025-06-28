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
