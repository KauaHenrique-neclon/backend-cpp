#include "cadastrarModel.hpp"
#include <iostream>
#include <stdexcept>


pqxx::connection* ModelCadastrar::conn = nullptr;

ModelCadastrar::ModelCadastrar() {
    if (!conn) {
        try {
            conn = new pqxx::connection("dbname=erp user=postgres password=5115 host=localhost");
            if (!conn->is_open()) {
                throw std::runtime_error("Falha na conexão com o banco.");
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro de conexão: " << e.what() << std::endl;
            throw;
        }
    }
}

bool ModelCadastrar::inserirDadosCadastro(const Cadastro& cadastro){
    try{
        pqxx::work w(*conn);
        std::string query = "INSERT INTO usuarios (username, nome, senha, data_nascimento, email, cidade) "
                          "VALUES (" + 
                        w.quote(cadastro.username) + ", " + 
                        w.quote(cadastro.nome) + ", " + 
                        w.quote(cadastro.senha) + ", " +
                        w.quote(cadastro.dataNascimento) + ", " + 
                        w.quote(cadastro.email) + ", " + 
                        w.quote(cadastro.cidade) + ");";
        w.exec(query);
        w.commit();
        return true;
    }catch(const std::exception &e){
        std::cerr << "Erro durante a inserção: " << e.what() << std::endl;
        return false;
    }
};

std::vector<Cadastro> ModelCadastrar::BuscandoCadastro() {
    std::vector<Cadastro> cadastros;
    try{
        pqxx::work conexao(*conn);
        pqxx::result res = conexao.exec("SELECT id, username, nome, senha, data_nascimento, email, cidade FROM usuarios");
        for (auto row : res) {
            Cadastro cadastro;
            cadastro.id = row["id"].as<int>();
            cadastro.nome = row["nome"].as<std::string>();
            cadastro.username = row["username"].as<std::string>();
            cadastro.dataNascimento = row["data_nascimento"].as<std::string>();
            cadastro.email = row["email"].as<std::string>();
            cadastro.cidade = row["cidade"].as<std::string>();
            cadastros.push_back(cadastro);
        }
        conexao.commit();
    }catch(const std::exception &e){
        std::cerr << "Erro ao buscar dados de cadastros" << std::endl;
    }
    return cadastros;
}
