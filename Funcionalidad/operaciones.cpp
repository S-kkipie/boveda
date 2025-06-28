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

void transferir(
    EntidadBancaria* bancoOrigen, Plaza* plazaOrigen, Boveda* bovedaOrigen,
    EntidadBancaria* bancoDestino, Plaza* plazaDestino, Boveda* bovedaDestino,
    ElementoMonetario* elemento, int cantidad, Transportadora* transportadora
) {
    if (!bancoOrigen || !plazaOrigen || !bancoDestino || !plazaDestino || !bovedaOrigen || !bovedaDestino || !transportadora || !elemento)
        throw ExcepcionEntidadNoEncontrada("Entidad nula");
    if (cantidad <= 0 || elemento->getValor() <= 0)
        throw ExcepcionOperacionInvalida("Monto o cantidad invalido");
    auto& bovedasOrigen = bancoOrigen->getBovedas();
    auto& bovedasDestino = bancoDestino->getBovedas();
    if (std::find(bovedasOrigen.begin(), bovedasOrigen.end(), bovedaOrigen) == bovedasOrigen.end())
        throw ExcepcionOperacionInvalida("Boveda origen no pertenece al banco origen");
    if (std::find(bovedasDestino.begin(), bovedasDestino.end(), bovedaDestino) == bovedasDestino.end())
        throw ExcepcionOperacionInvalida("Boveda destino no pertenece al banco destino");
    if (bovedaOrigen->getPlaza() != plazaOrigen)
        throw BovedaPlazaMismatchException("Boveda origen no corresponde a plaza origen");
    if (bovedaDestino->getPlaza() != plazaDestino)
        throw BovedaPlazaMismatchException("Boveda destino no corresponde a plaza destino");
    bool plazaCoincide = false;
    for (auto* p : transportadora->getPlazas()) {
        if (p == plazaOrigen || p == plazaDestino) { plazaCoincide = true; break; }
    }
    if (!plazaCoincide)
        throw ExcepcionOperacionInvalida("Transportadora no operativa");
    double saldo = 0;
    for (auto& p : bovedaOrigen->getPaquetesMonetarios())
        if (p && p->getElemento()->getValor() == elemento->getValor())
            saldo += p->getElemento()->getValor() * p->getCantidad();
    if (saldo < elemento->getValor() * cantidad)
        throw ExcepcionSaldoInsuficiente("Saldo insuficiente en boveda origen");
    // Simular capacidad de transportadora
    if (cantidad > 100) throw CapacidadInsuficienteException("Transportadora sin capacidad suficiente");
    // Extraer paquetes
    std::vector<PaqueteMonetario*> paquetesTransferidos;
    int restante = cantidad;
    std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> dis(0, 99);
    for (auto it = bovedaOrigen->getPaquetesMonetarios().begin(); it != bovedaOrigen->getPaquetesMonetarios().end() && restante > 0;) {
        PaqueteMonetario* p = *it;
        if (p->getElemento()->getValor() == elemento->getValor()) {
            int extraer = std::min(p->getCantidad(), restante);
            Estado estado = Estado::Bueno;
            int aleatorio = dis(gen);
            if (aleatorio < 5) estado = Estado::Falso;
            else if (aleatorio < 15) estado = Estado::Dañado;
            PaqueteMonetario* paqueteNuevo = new PaqueteMonetario(elemento, estado, extraer);
            paquetesTransferidos.push_back(paqueteNuevo);
            if (p->getCantidad() == extraer) {
                it = bovedaOrigen->getPaquetesMonetarios().erase(it);
                delete p;
            } else {
                p->setCantidad(p->getCantidad() - extraer);
                ++it;
            }
            restante -= extraer;
        } else {
            ++it;
        }
    }
    // Validar manifiesto
    if (paquetesTransferidos.empty())
        throw IntegridadManifiestoException("Manifiesto vacío o inconsistente");
    bool hayDaniado = false, hayFalso = false;
    for (auto* p : paquetesTransferidos) {
        if (p->getEstado() == Estado::Dañado) hayDaniado = true;
        if (p->getEstado() == Estado::Falso) hayFalso = true;
    }
    if (hayFalso) {
        for (auto* p : paquetesTransferidos) delete p;
        throw DineroFalsoException("Dinero falso detectado en transferencia. Protocolo de seguridad activado.");
    }
    if (hayDaniado) {
        for (auto* p : paquetesTransferidos) delete p;
        throw DineroDaniadoException("Dinero dañado detectado en transferencia. Operación revertida.");
    }
    // Simular posible demora
    if (dis(gen) < 2) throw TransporteDemoradoException("Transporte demorado");
    // Registrar en bóveda destino
    for (auto* p : paquetesTransferidos) bovedaDestino->getPaquetesMonetarios().push_back(p);
    std::time_t ahora = std::time(nullptr);
    Operacion* op = new Operacion(ahora, TipoOperacion::Transferencia, transportadora, plazaOrigen, plazaDestino, bancoOrigen, bancoDestino);
    for (auto* p : paquetesTransferidos) op->agregarPaqueteMonetario(p);
    bancoOrigen->registrarOperacion(op);
    bancoDestino->registrarOperacion(op);
    bovedaOrigen->registrarOperacion(op);
    bovedaDestino->registrarOperacion(op);
    transportadora->registrarOperacion(op);
    // Si todo bien, operación completada
}