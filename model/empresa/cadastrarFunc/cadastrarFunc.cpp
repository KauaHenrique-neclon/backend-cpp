#include "cadastrarFunc.hpp"
#include <iostream>
#include <stdexcept>


ModelCadastrarFuncionario::ModelCadastrarFuncionario(){
    conn = bancoDados();
    if (!conn) {
        std::cerr << "Falha ao conectar ao banco de dados no ModelEstoque." << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados.");
    }
}


bool ModelCadastrarFuncionario::inserindoFuncionario(const DadosFuncionario& funcionario){
    try{
        pqxx::work conec(*conn);
        conec.exec0("INSERT INTO funcionarios (nome,cfp , email, datanascimento, cidade, bairro) VALUES (" +
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