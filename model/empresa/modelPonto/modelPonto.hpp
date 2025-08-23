#ifndef MODEL_PONTO_HPP
#define MODEL_PONTO_HPP

#include <stdio.h>
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include "../../../config/conect.hpp"


class DadosPonto{
public:
    std::string id;
    std::string cpf;
    std::string data;
    std::string horaentrada;
    std::string horasaida;
    std::string tipo;
};


class ModelPonto{
private:
    pqxx::connection* conn;
public:
    ModelPonto();

    bool inserindoPonto(const DadosPonto& dadosPonto);
    std::vector<DadosPonto> BuscandoDadosPontos();
};


#endif // MODEL_PONTO_HPP