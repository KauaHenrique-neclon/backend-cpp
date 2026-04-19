#include "cadastrarFunc.hpp"
#include <iostream>
#include <stdexcept>


ModelCadastrarFuncionario::ModelCadastrarFuncionario(){
    conn = bancoDados();

    if (conn == nullptr || !conn->is_open()) {
        std::cerr << "Falha ao conectar ao banco." << std::endl;
        return;
    }
    if (!conn->is_open()) {
        std::cerr << "Conexão não abriu" << std::endl;
        delete conn;
        return;
    }
}


bool ModelCadastrarFuncionario::inserindoFuncionario(const DadosFuncionario& funcionario){
    try{
        pqxx::work conec(*conn);
        conec.exec("INSERT INTO funcionarios (nome,cfp , email, datanascimento, cidade, bairro) VALUES (" +
                  conec.quote(funcionario.nome) + ", " +
                  conec.quote(funcionario.cpf) + ", " +
                  conec.quote(funcionario.email) + ", " +
                  conec.quote(funcionario.dataNascimento) + ", " +
                  conec.quote(funcionario.cidade) + ", " +
                  conec.quote(funcionario.bairro) + " );");
        conec.commit();
        return true;
    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir produto: " << e.what() << std::endl;
        return false;
    }
}

ModelCadastrarFuncionario::~ModelCadastrarFuncionario() {
    delete conn;
}