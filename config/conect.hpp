#ifndef CONECT_HPP
#define CONECT_HPP


#include <pqxx/pqxx>
#include <iostream>

pqxx::connection* bancoDados() {
    try {
        return new pqxx::connection("dbname=erp user=postgres password=5115 host=localhost");
    } catch (const pqxx::failure &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erro desconhecido: " << e.what() << std::endl;
    }
    return nullptr;
}


#endif 