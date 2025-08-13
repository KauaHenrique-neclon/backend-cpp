#ifndef LOGINMODEL_HPP
#define LOGINMODEL_HPP

#include "../../config/conect.hpp"
#include <string.h>
#include <pqxx/pqxx>
#include <stdexcept>


class Usuario{
public:
    int id;
    std::string nome;
    std::string email;
    Usuario(int id, std::string nome, std::string email) : id(id), nome(nome), email(email) {}Usuario() : id(0), nome(""), email("") {}
    Usuario() : id(0), nome(""), email("") {} 
};

class LoginModel{
private:
    static pqxx::connection* conn;
    std::string email;
    std::string senha;
    Usuario usuario;
public:
    LoginModel(std::string email ,std::string senha);
    bool LoginUsuario();
    Usuario getUsuario();
};


#endif // LOGINMODEL_HPP