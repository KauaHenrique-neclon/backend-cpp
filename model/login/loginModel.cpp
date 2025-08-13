#include "loginModel.hpp"

pqxx::connection* LoginModel::conn = nullptr;


LoginModel::LoginModel(std::string email, std::string senha) : email(email), senha(senha) {
    conn = bancoDados();
    if (!conn) {
        std::cerr << "Falha ao conectar ao banco de dados no ModelEstoque." << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados.");
    }
}


bool LoginModel::LoginUsuario() {
    try {
        pqxx::work w(*conn);
        pqxx::result res = w.exec("SELECT id, nome, email FROM usuarios WHERE email = " + w.quote(email) + " AND senha = " + w.quote(senha) + ";");

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
