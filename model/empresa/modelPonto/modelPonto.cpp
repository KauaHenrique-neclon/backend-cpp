#include "modelPonto.hpp"


ModelPonto::ModelPonto() {
    conn = bancoDados();
    if (!conn) {
        std::cerr << "Falha ao conectar ao banco de dados no ModelEstoque." << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados.");
    }
}


bool ModelPonto::inserindoPonto(const DadosPonto& dadosPonto){
    try{
        pqxx::work conect(*conn);

        if(dadosPonto.tipo == "entrada"){
            conect.exec("INSERT INTO frequencia(cpf, data, hora_entrada) VALUES(" +
                        conect.quote(dadosPonto.cpf) + ", " +
                        conect.quote(dadosPonto.data) + "," +
                        conect.quote(dadosPonto.horaentrada) + ");");
            conect.commit();
            return true;
        }
        else if(dadosPonto.tipo == "saida"){
            conect.exec("UPDATE frequencia SET horasaida = NOW() WHERE cpf = " + conect.quote(dadosPonto.cpf) +
                        " AND data = " + conect.quote(dadosPonto.data) +
                        " AND hora_saida IS NULL");
            conect.commit();
            return true;
        }
        else {
            std::cerr << "Tipo de ponto inválido: " << dadosPonto.tipo << std::endl;
            return false;
        }

    } catch (const std::exception& e){
        std::cerr << "Erro ao inserir ponto: " << e.what() << std::endl;
        return false;
    }
}



std::vector<DadosPonto> ModelPonto::BuscandoDadosPontos() {
    std::vector<DadosPonto> dadosPontos;
    try {
        pqxx::work coonn(*conn);
        pqxx::result res = coonn.exec("SELECT id, cpf, data, horaentrada, horasaida FROM frequencia");
        for (auto row : res) {
            DadosPonto ponto;
            ponto.id = row["id"].as<int>();
            ponto.cpf = row["cpf"].as<int>();
            ponto.data = row["data"].as<std::string>();
            ponto.horaentrada = row["horaentrada"].as<std::string>();
            ponto.horasaida = row["horasaida"].as<std::string>();
            dadosPontos.push_back(ponto);
        }
        coonn.commit();
    } catch (std::exception& e) {
        std::cerr << "Erro ao buscar dados do ponto: " << e.what() << std::endl;
    }
    return dadosPontos;
}
