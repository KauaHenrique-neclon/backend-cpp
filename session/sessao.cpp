#include "sessao.hpp"
#include <iostream>

Session::Session() : authenticated(false), loginModel(nullptr) {
   
}

bool Session::Login(const std::string& email, const std::string& senha) {
    loginModel = new LoginModel(email, senha); 
    if (loginModel->LoginUsuario()) {
        authenticated = true;
        usuario = loginModel->getUsuario();
        std::cout << "Usuário autenticado: " << usuario.nome << std::endl;
        return true;
    }
    std::cout << "Falha na autenticação." << std::endl;
    return false;
}

void Session::Logout() {
    authenticated = false;
    delete loginModel;
    loginModel = nullptr;
    std::cout << "Usuário desconectado." << std::endl;
    std::cout << "Usuário desconectado." << std::endl;
}

bool Session::IsAuthenticated() const {
    return authenticated;
}

bool Session::AccessPage(const std::string& page) {
    if (IsAuthenticated()) {
        std::cout << "Acesso à página: " << page << std::endl;
        return true;
    } else {
        std::cout << "Acesso negado à página: " << page << std::endl;
        return false;
    }
}