#include "Entidades/Interfaces/Transportadora.hpp"
#include "Entidades/Interfaces/Plaza.hpp"
#include "Entidades/Interfaces/EntidadBancaria.hpp"
#include "Entidades/Interfaces/Boveda.hpp"
#include "Entidades/Interfaces/Operacion.hpp"
#include "Entidades/Interfaces/PaqueteMonetario.hpp"
#include "Entidades/Interfaces/ElementoMonetario.hpp"
#include "Excepciones/ExcepcionBovedas.hpp"
#include <iostream>
#include <ctime>
#include "Funcionalidad/operaciones.cpp"
int main() {
    try {
        Plaza plaza1("San Jose");
        EntidadBancaria banco1("Banco Central");
        Boveda boveda1("Boveda Principal", &plaza1);
        banco1.agregarBoveda(&boveda1);
        banco1.agregarPlaza(&plaza1);
        Transportadora hermes("Hermes");
        hermes.agregarPlaza(&plaza1);

        ElementoMonetario billete5(5, Tipo::Billete);
        ElementoMonetario billete10(10, Tipo::Billete);
        ElementoMonetario billete100(100, Tipo::Billete);
        ElementoMonetario billete200(200, Tipo::Billete);

        ElementoMonetario moneda1(1, Tipo::Moneda);
        ElementoMonetario moneda2(2, Tipo::Moneda);
        ElementoMonetario moneda5(5, Tipo::Moneda);

        try {
            std::cout << "Depositando billetes y monedas en la bóveda..." << std::endl;
            depositar(&banco1, &boveda1, &billete5, 10, &hermes);
            depositar(&banco1, &boveda1, &billete10, 5, &hermes);
            depositar(&banco1, &boveda1, &billete100, 2, &hermes);
            depositar(&banco1, &boveda1, &billete200, 1, &hermes);
            depositar(&banco1, &boveda1, &moneda1, 20, &hermes);
            depositar(&banco1, &boveda1, &moneda2, 10, &hermes);
            depositar(&banco1, &boveda1, &moneda5, 4, &hermes);
            std::cout << "Deposito exitoso." << std::endl;
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Error en deposito: " << ex.what() << std::endl;
        }
        std::cout << "\nEstado de la bóveda después de depositar:" << std::endl;
        boveda1.imprimirDetalles();

        try {
            std::cout << "\nRetirando 2 billetes de 100 y 5 monedas de 2..." << std::endl;
            retirar(&banco1, &boveda1, &billete100, 2, &hermes);
            retirar(&banco1, &boveda1, &moneda2, 5, &hermes);
            std::cout << "Retiro exitoso." << std::endl;
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Error en retiro: " << ex.what() << std::endl;
        }
        std::cout << "\nEstado de la bóveda después de retirar:" << std::endl;
        boveda1.imprimirDetalles();

        Plaza plaza2("Alajuela");
        EntidadBancaria banco2("Banco Nacional");
        Boveda boveda2("Boveda Secundaria", &plaza2);
        banco2.agregarBoveda(&boveda2);
        banco2.agregarPlaza(&plaza2);
        hermes.agregarPlaza(&plaza2);
        try {
            std::cout << "\nTransfiriendo 5 billetes de 5 y 10 monedas de 1 de la bóveda principal a la secundaria..." << std::endl;
            transferir(&banco1, &plaza1, &boveda1, &banco2, &plaza2, &boveda2, &billete5, 5, &hermes);
            transferir(&banco1, &plaza1, &boveda1, &banco2, &plaza2, &boveda2, &moneda1, 10, &hermes);
            std::cout << "Transferencia exitosa." << std::endl;
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Error en transferencia: " << ex.what() << std::endl;
        }
        std::cout << "\nEstado de la bóveda principal después de transferir:" << std::endl;
        boveda1.imprimirDetalles();
        std::cout << "\nEstado de la bóveda secundaria después de recibir transferencia:" << std::endl;
        boveda2.imprimirDetalles();

        std::cout << "\nOperaciones registradas en la bóveda principal:" << std::endl;
        boveda1.imprimirOperaciones();
        std::cout << "\nOperaciones registradas en la bóveda secundaria:" << std::endl;
        boveda2.imprimirOperaciones();

        // Lanzar excepción por entidad nula
        try {
            std::cout << "\nIntentando depositar con entidad nula..." << std::endl;
            depositar(nullptr, &boveda1, &billete5, 1, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (entidad nula): " << ex.what() << std::endl;
        }
        // Lanzar excepción por monto inválido
        try {
            std::cout << "\nIntentando depositar monto inválido..." << std::endl;
            depositar(&banco1, &boveda1, &billete5, 0, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (monto inválido): " << ex.what() << std::endl;
        }
        // Lanzar excepción por bóveda no perteneciente al banco
        Plaza plazaFake("Fake");
        Boveda bovedaFake("Boveda Fake", &plazaFake);
        try {
            std::cout << "\nIntentando depositar en bóveda que no pertenece al banco..." << std::endl;
            depositar(&banco1, &bovedaFake, &billete5, 1, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (bóveda no pertenece al banco): " << ex.what() << std::endl;
        }
        // Lanzar excepción por transportadora no operativa
        Transportadora transNoOp("NoOp");
        try {
            std::cout << "\nIntentando depositar con transportadora no operativa..." << std::endl;
            depositar(&banco1, &boveda1, &billete5, 1, &transNoOp);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (transportadora no operativa): " << ex.what() << std::endl;
        }
        // Lanzar excepción por saldo insuficiente
        try {
            std::cout << "\nIntentando retirar más de lo disponible..." << std::endl;
            retirar(&banco1, &boveda1, &billete200, 100, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (saldo insuficiente): " << ex.what() << std::endl;
        }
        // Lanzar excepción por transferencia con boveda-plaza mismatch
        Plaza plaza3("Cartago");
        Boveda boveda3("Boveda Cartago", &plaza3);
        banco2.agregarBoveda(&boveda3);
        try {
            std::cout << "\nIntentando transferir con boveda-plaza mismatch..." << std::endl;
            transferir(&banco1, &plaza1, &boveda1, &banco2, &plaza3, &boveda3, &billete5, 1, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (boveda-plaza mismatch): " << ex.what() << std::endl;
        }
        // Lanzar excepción por capacidad insuficiente
        try {
            std::cout << "\nIntentando transferir con capacidad insuficiente..." << std::endl;
            transferir(&banco1, &plaza1, &boveda1, &banco2, &plaza2, &boveda2, &moneda1, 101, &hermes);
        } catch(const ExcepcionBovedas& ex) {
            std::cerr << "Excepción esperada (capacidad insuficiente): " << ex.what() << std::endl;
        }
    } catch(const ExcepcionBovedas& ex) {
        std::cerr << "Excepcion: " << ex.what() << std::endl;
    }
    return 0;
}