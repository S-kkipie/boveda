#include "../Entidades/Interfaces/EntidadBancaria.hpp"
#include "../Entidades/Interfaces/Boveda.hpp"
#include "../Entidades/Interfaces/Operacion.hpp"
#include "../Entidades/Interfaces/Transportadora.hpp"
#include "../Entidades/Interfaces/ElementoMonetario.hpp"
#include "../Entidades/Interfaces/PaqueteMonetario.hpp"
#include "../Excepciones/ExcepcionBovedas.hpp"
#include <algorithm>
#include <random>

void depositar(EntidadBancaria* banco, Boveda* boveda, ElementoMonetario* elemento, int cantidad, Transportadora* transportadora) {
    if (!banco || !boveda || !transportadora || !elemento) throw ExcepcionEntidadNoEncontrada("Entidad nula");
    if (cantidad <= 0 || elemento->getValor() <= 0) throw ExcepcionOperacionInvalida("Monto o cantidad invalido");
    auto& bovedas = banco->getBovedas();
    if (std::find(bovedas.begin(), bovedas.end(), boveda) == bovedas.end()) throw ExcepcionOperacionInvalida("Boveda no pertenece al banco");
    bool plazaCoincide = false;
    for (auto* p : transportadora->getPlazas()) {
        if (p == boveda->getPlaza()) { plazaCoincide = true; break; }
    }
    if (!plazaCoincide) throw ExcepcionOperacionInvalida("Transportadora no operativa");
    std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> dis(0, 99);
    Estado estado = Estado::Bueno;
    int aleatorio = dis(gen);
    if (aleatorio < 5) estado = Estado::Falso;
    else if (aleatorio < 15) estado = Estado::Dañado;
    if (estado == Estado::Falso) throw ExcepcionElementoMonetarioInvalido("Dinero falso detectado");
    PaqueteMonetario* paquete = new PaqueteMonetario(elemento, estado, cantidad);
    boveda->getPaquetesMonetarios().push_back(paquete);
    std::time_t ahora = std::time(nullptr);
    Operacion* op = new Operacion(ahora, TipoOperacion::Deposito, transportadora, boveda->getPlaza(), nullptr, banco, nullptr);
    op->agregarPaqueteMonetario(paquete);
    banco->registrarOperacion(op);
    boveda->registrarOperacion(op);
    transportadora->registrarOperacion(op);
}

void retirar(EntidadBancaria* banco, Boveda* boveda, ElementoMonetario* elemento, int cantidad, Transportadora* transportadora) {
    if (!banco || !boveda || !transportadora || !elemento) throw ExcepcionEntidadNoEncontrada("Entidad nula");
    if (cantidad <= 0 || elemento->getValor() <= 0) throw ExcepcionOperacionInvalida("Monto o cantidad invalido");
    auto& bovedas = banco->getBovedas();
    if (std::find(bovedas.begin(), bovedas.end(), boveda) == bovedas.end()) throw ExcepcionOperacionInvalida("Boveda no pertenece al banco");
    bool plazaCoincide = false;
    for (auto* p : transportadora->getPlazas()) {
        if (p == boveda->getPlaza()) { plazaCoincide = true; break; }
    }
    if (!plazaCoincide) throw ExcepcionOperacionInvalida("Transportadora no operativa");
    double saldo = 0;
    for (auto& p : boveda->getPaquetesMonetarios()) if (p && p->getElemento()->getValor() == elemento->getValor()) saldo += p->getElemento()->getValor() * p->getCantidad();
    if (saldo < elemento->getValor() * cantidad) throw ExcepcionSaldoInsuficiente("Saldo insuficiente");
    int restante = cantidad;
    for (auto it = boveda->getPaquetesMonetarios().begin(); it != boveda->getPaquetesMonetarios().end() && restante > 0;) {
        PaqueteMonetario* p = *it;
        if (p->getElemento()->getValor() == elemento->getValor()) {
            if (p->getCantidad() <= restante) {
                restante -= p->getCantidad();
                it = boveda->getPaquetesMonetarios().erase(it);
                delete p;
            } else {
                p->setCantidad(p->getCantidad() - restante);
                restante = 0;
                ++it;
            }
        } else {
            ++it;
        }
    }
    std::time_t ahora = std::time(nullptr);
    Operacion* op = new Operacion(ahora, TipoOperacion::Retiro, transportadora, boveda->getPlaza(), nullptr, banco, nullptr);
    banco->registrarOperacion(op);
    boveda->registrarOperacion(op);
    transportadora->registrarOperacion(op);
}