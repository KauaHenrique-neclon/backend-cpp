#include "cadastrarModel.hpp"

ModelCadastrar::ModelCadastrar(std::string username, std::string nome, std::string senha, std::string dataNascimento, std::string email, std::string cidade)
    : username(username), nome(nome), senha(senha), dataNascimento(dataNascimento), 
    email(email), cidade(cidade) {
        
    conn = bancoDados();

    if(!conn){
        throw std::runtime_error("Falha ao conectar ao banco de dados.");
    }
}

bool ModelCadastrar::inserirDadosCadastro(){
    try{
        pqxx::work w(*conn);
        std::string query = "INSERT INTO usuarios (username, nome, senha, data_nascimento, email, cidade) "
                          "VALUES (" + w.quote(username) + ", " + w.quote(nome) + ", " + w.quote(senha) + ", " +
                          w.quote(dataNascimento) + ", " + w.quote(email) + ", " + w.quote(cidade) + ");";
        w.exec(query);
        w.commit();
        return true;
    }catch(const std::exception &e){
        std::cerr << "Erro durante a inserção: " << e.what() << std::endl;
        return false;
    }
};