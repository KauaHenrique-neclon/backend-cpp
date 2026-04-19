#include "conect.hpp"
#include <cstdlib>
#include "env/dotenv.h"

/*
void loadEnv(const std::string& file) {
    std::ifstream env(file);
    std::string line;

    while (std::getline(env, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string key, value;

        if (std::getline(ss, key, '=') &&
            std::getline(ss, value)) {

            setenv(key.c_str(), value.c_str(), 1);
        }
    }
}



pqxx::connection* bancoDados() {
    try {
        const char* host = std::getenv("DB_HOST");
        const char* user = std::getenv("DB_USER");
        const char* name = std::getenv("DB_NAME");
        const char* pass = std::getenv("DB_PASSWORD");

        std::cout << "DB_HOST: " << std::getenv("DB_HOST") << std::endl;

        if (!host || !user || !name || !pass) {
            throw std::runtime_error("Variaveis de ambiente não definidas.");
        }

        std::string conn =
            "dbname=" + std::string(name) +
            " user=" + std::string(user) +
            " password=" + std::string(pass) +
            " host=" + std::string(host);

        return new pqxx::connection(conn);

    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
}*/

#include "conect.hpp"


pqxx::connection* bancoDados() {
    try {
        return new pqxx::connection("dbname=erp user=postgres password=5115 host=localhost");
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
}