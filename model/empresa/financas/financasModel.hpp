#ifndef FINANCAS_MODEL_HPP
#define FINANCAS_MODEL_HPP


#include "../../../config/conect.hpp"
#include <string.h>
#include <pqxx/pqxx>
#include <stdexcept>



class DadosConta{
public:
    int id;
    std::string nome;
    std::string tipo;
    float preco;
    std::string status;
    std::string vencimento;
    std::string dia_lancamento;
};


class FinancasModel{
private:
    static pqxx::connection* conn;
public:
    FinancasModel();
    ~FinancasModel();
    bool inserindoConta(const DadosConta& conta);
    std::vector<DadosConta> BuscandoContas();
};


#endif // FINANCAS_MODEL_HPP