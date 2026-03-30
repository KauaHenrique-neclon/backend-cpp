#include "financasModel.hpp"
#include <iostream>

std::unique_ptr<pqxx::connection> FinancasModel::conn = nullptr;


void FinancasModel::conectar(){
    if (!conn) {
        conn = std::make_unique<pqxx::connection>(
            "dbname=seubanco user=postgres password=123 host=localhost"
        );

        if (!conn->is_open()) {
            throw std::runtime_error("Erro ao conectar ao banco de dados.");
        }
    }
}

FinancasModel::FinancasModel(){
    conectar();
}

FinancasModel::~FinancasModel(){
}

bool FinancasModel::inserindoConta(const DadosConta& conta){
    try{
        pqxx::work txn(*conn);

        txn.exec(
            "INSERT INTO contas(nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento, codigo_barra) VALUES (" +
            txn.quote(conta.nome) + ", " +
            txn.quote(conta.tipo) + ", " +
            txn.quote(conta.preco) + ", " +
            txn.quote(conta.status) + ", " +
            txn.quote(conta.vencimento) + ", " +
            txn.quote(conta.dia_lancamento) + ", " +
            txn.quote(conta.codigoBarra) + ");"
        );

        txn.commit();
        return true;

    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir conta: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DadosConta> FinancasModel::BuscandoContas(){
    std::vector<DadosConta> dados;

    try{
        pqxx::work txn(*conn);

        pqxx::result r = txn.exec(
            "SELECT id, nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento, codigo_barra FROM contas"
        );

        for (const auto& linha : r) {
            DadosConta conta;
            conta.id = linha["id"].as<int>();
            conta.nome = linha["nome_conta"].as<std::string>();
            conta.tipo = linha["tipo_conta"].as<std::string>();
            conta.preco = linha["preco"].as<float>();
            conta.status = linha["status"].as<std::string>();
            conta.vencimento = linha["vencimento"].as<std::string>();
            conta.dia_lancamento = linha["dia_lancamento"].as<std::string>();
            conta.codigoBarra = linha["codigo_barra"].as<int>();

            dados.push_back(conta);
        }

    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar contas: " << e.what() << std::endl;
    }

    return dados;
}

bool FinancasModel::inserirOrcamento(const DadosOrcamento& orcamento){
    try{
        pqxx::work txn(*conn);

        txn.exec(
            "INSERT INTO orcamento(nome_orcamento, preco, status, datapedido, descricao) VALUES (" +
            txn.quote(orcamento.nome_orcamento) + ", " +
            txn.quote(orcamento.preco) + ", " +
            txn.quote(orcamento.status) + ", " +
            txn.quote(orcamento.datapedido) + ", " +
            txn.quote(orcamento.descricao) + ");"
        );

        txn.commit();
        return true;

    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir orçamento: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DadosOrcamento> FinancasModel::BuscandoOrcamento(){
    std::vector<DadosOrcamento> dados;

    try{
        pqxx::work txn(*conn);

        pqxx::result r = txn.exec(
            "SELECT id, nome_orcamento, preco, status, datapedido, descricao FROM orcamento"
        );

        for(const auto& linha : r){
            DadosOrcamento o;
            o.id = linha["id"].as<int>();
            o.nome_orcamento = linha["nome_orcamento"].as<std::string>();
            o.preco = linha["preco"].as<std::string>();
            o.status = linha["status"].as<std::string>();
            o.datapedido = linha["datapedido"].as<std::string>();
            o.descricao = linha["descricao"].as<std::string>();

            dados.push_back(o);
        }

    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar orçamentos: " << e.what() << std::endl;
    }

    return dados;
}