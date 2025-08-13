#ifndef CADASTRAR_FUNCIONARIO_HPP
#define CADASTRAR_FUNCIONARIO_HPP

#include "../../../config/conect.hpp"
#include <string.h>
#include <pqxx/pqxx>
#include <stdexcept>


class DadosFuncionario{
public:
    std::string nome;
    std::string cpf;
    std::string email;
    std::string dataNascimento;
    std::string cidade;
    std::string bairro;
};

class ModelCadastrarFuncionario{
private:
    pqxx::connection* conn;
public:
    ModelCadastrarFuncionario();

    bool inserindoFuncionario(const DadosFuncionario& funcionario);
};


#endif // CADASTRAR_FUNCIONARIO_HPP