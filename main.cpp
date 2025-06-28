#include "Entidades/Interfaces/Transportadora.hpp"
#include "Entidades/Interfaces/Plaza.hpp"
#include "Entidades/Interfaces/EntidadBancaria.hpp"
#include "Entidades/Interfaces/Boveda.hpp"
#include "Entidades/Interfaces/Operacion.hpp"
#include "Entidades/Interfaces/PaqueteMonetario.hpp"
#include "Entidades/Interfaces/ElementoMonetario.hpp"
#include "Excepciones/ExcepcionBovedas.hpp"
#include "Excepciones/ExcepcionesEspeciales.hpp"
#include <iostream>
#include <ctime>

int main() {
    try {
        // Crear entidades
        Plaza plaza1("San Jose");
        EntidadBancaria banco1("Banco Central");
        Boveda boveda1("Boveda Principal", &plaza1);
        banco1.agregarBoveda(&boveda1);
        banco1.agregarPlaza(&plaza1);
        Transportadora hermes("Hermes");
        hermes.agregarPlaza(&plaza1);

        // Crear elemento monetario y paquete
        ElementoMonetario billete10000(10000, Estado::Bueno, Tipo::Billete);
        PaqueteMonetario paquete(&billete10000, 5);

        // Crear operación
        std::time_t ahora = std::time(nullptr);
        Operacion op(ahora, TipoOperacion::Deposito, &hermes, &plaza1, nullptr, &banco1, nullptr);
        op.agregarPaqueteMonetario(&paquete);

        std::cout << "\n[DEBUG] Estado inicial de las entidades:" << std::endl;
        plaza1.imprimir();
        banco1.imprimir();
        boveda1.imprimir();
        hermes.imprimir();
        billete10000.imprimir();
        paquete.imprimir();

        std::cout << "\n[DEBUG] Estado de la operación creada:" << std::endl;
        op.imprimir();

        // Registrar operación
        std::cout << "\n[DEBUG] Registrando operación en entidades..." << std::endl;
        banco1.registrarOperacion(&op);
        hermes.registrarOperacion(&op);
        plaza1.registrarOperacion(&op);
        boveda1.registrarOperacion(&op);

        std::cout << "\n[DEBUG] Estado final de las entidades:" << std::endl;
        plaza1.imprimir();
        banco1.imprimir();
        boveda1.imprimir();
        hermes.imprimir();

        // Consultar operaciones
        std::cout << "Operaciones en banco: " << banco1.getOperaciones().size() << std::endl;
        std::cout << "Operaciones en transportadora: " << hermes.getOperaciones().size() << std::endl;
        std::cout << "Operaciones en plaza: " << plaza1.getOperaciones().size() << std::endl;
        std::cout << "Operaciones en boveda: " << boveda1.getOperaciones().size() << std::endl;
    } catch(const ExcepcionBovedas& ex) {
        std::cerr << "Excepcion: " << ex.what() << std::endl;
    }
    return 0;
}