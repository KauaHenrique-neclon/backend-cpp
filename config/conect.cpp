#include "conect.hpp"


pqxx::connection* bancoDados() {
    try {
        return new pqxx::connection("dbname=erp user=postgres password=5115 host=localhost");
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
}