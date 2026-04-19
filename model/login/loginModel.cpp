#include "loginModel.hpp"

pqxx::connection* LoginModel::conn = nullptr;


LoginModel::LoginModel(std::string email, std::string senha) : email(email), senha(senha) {
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


bool LoginModel::LoginUsuario() {
    try {
        pqxx::work w(*conn);
        pqxx::result res = w.exec("SELECT id, nome, email FROM usuarios WHERE email = " + w.quote(email) + " AND password = " + w.quote(senha) + ";");

        if (res.empty()) {
            std::cerr << "Email ou senha incorretos." << std::endl;
            return false;
        }

        
        usuario.id = res[0]["id"].as<int>();
        usuario.nome = res[0]["nome"].as<std::string>();
        usuario.email = res[0]["email"].as<std::string>();
        w.commit();
        return true;
        
    } catch (const std::exception &e) {
        std::cerr << "Erro durante o processo de login: " << e.what() << std::endl;
        return false;
    }
}


Usuario LoginModel::getUsuario() {
    return usuario;
}
