#ifndef CADASTRARMODEL_HPP
#define CADASTRARMODEL_HPP

#include "../../config/conect.hpp"
#include <string.h>
#include <stdexcept>


class Cadastro {
public:
    int id;
    std::string username;
    std::string nome;
    std::string senha;
    std::string dataNascimento;
    std::string email;
    std::string cidade;
};

class ModelCadastrar {
private:
    static pqxx::connection* conn;

public:
    ModelCadastrar();
    std::vector<Cadastro> BuscandoCadastro();
    bool inserirDadosCadastro(const Cadastro& cadastro);
};


#endif // CADASTRARMODEL_HPP
//  pqxx::connection* conn = bancoDados();