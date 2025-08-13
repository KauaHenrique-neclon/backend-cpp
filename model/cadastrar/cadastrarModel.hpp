#ifndef CADASTRARMODEL_HPP
#define CADASTRARMODEL_HPP

#include "../../config/conect.hpp"
#include <string.h>
#include <pqxx/pqxx>
#include <stdexcept>



class ModelCadastrar {
private:
    pqxx::connection* conn;
    std::string username;
    std::string nome;
    std::string senha;
    std::string dataNascimento;
    std::string email;
    std::string cidade;

public:
    ModelCadastrar(std::string username, std::string nome, std::string senha, std::string dataNascimento,
    std::string email, std::string cidade);

    bool inserirDadosCadastro();
};


#endif // CADASTRARMODEL_HPP
//  pqxx::connection* conn = bancoDados();