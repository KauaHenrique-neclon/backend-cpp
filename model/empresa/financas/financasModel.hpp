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
    int codigoBarra;
};

class DadosOrcamento{
public:
    int id;
    std::string nome_orcamento;
    std::string preco;
    std::string status;
    std::string datapedido;
    std::string descricao;
};


class FinancasModel{
private:
    static pqxx::connection* conn;
public:
    FinancasModel();
    ~FinancasModel();
    bool inserindoConta(const DadosConta& conta);
    std::vector<DadosConta> BuscandoContas();
    bool inserirOrcamento(const DadosOrcamento& orcamento);
    std::vector<DadosOrcamento> BuscandoOrcamento();
};


#endif // FINANCAS_MODEL_HPP