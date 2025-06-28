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

        // Billetes
        ElementoMonetario billete5(5, Tipo::Billete);
        ElementoMonetario billete10(10, Tipo::Billete);
        ElementoMonetario billete100(100, Tipo::Billete);
        ElementoMonetario billete200(200, Tipo::Billete);
        // Monedas
        ElementoMonetario moneda1(1, Tipo::Moneda);
        ElementoMonetario moneda2(2, Tipo::Moneda);
        ElementoMonetario moneda5(5, Tipo::Moneda);

        // Depositar billetes y monedas
        std::cout << "Depositando billetes y monedas en la bóveda..." << std::endl;
        depositar(&banco1, &boveda1, &billete5, 10, &hermes);
        depositar(&banco1, &boveda1, &billete10, 5, &hermes);
        depositar(&banco1, &boveda1, &billete100, 2, &hermes);
        depositar(&banco1, &boveda1, &billete200, 1, &hermes);
        depositar(&banco1, &boveda1, &moneda1, 20, &hermes);
        depositar(&banco1, &boveda1, &moneda2, 10, &hermes);
        depositar(&banco1, &boveda1, &moneda5, 4, &hermes);

        std::cout << "\nEstado de la bóveda después de depositar:" << std::endl;
        boveda1.imprimir();

        // Retirar billetes y monedas
        std::cout << "\nRetirando 2 billetes de 100 y 5 monedas de 2..." << std::endl;
        retirar(&banco1, &boveda1, &billete100, 2, &hermes);
        retirar(&banco1, &boveda1, &moneda2, 5, &hermes);

        std::cout << "\nEstado de la bóveda después de retirar:" << std::endl;
        boveda1.imprimir();

        std::cout << "\nOperaciones registradas en la bóveda:" << std::endl;
        for (const auto& op : boveda1.getOperaciones()) {
            if (op) op->imprimir();
        }
    } catch(const ExcepcionBovedas& ex) {
        std::cerr << "Excepcion: " << ex.what() << std::endl;
    }
    return 0;
}