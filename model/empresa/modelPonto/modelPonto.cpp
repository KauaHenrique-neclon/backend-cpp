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
            conect.exec0("INSERT INTO frequencia(id_funcionario, data, hora_entrada) VALUES(" +
                conect.quote(dadosPonto.funcionario_id) + ", " +
                conect.quote(dadosPonto.data) + "," + 
                conect.quote(dadosPonto.horaentrada) + ");");
            conect.commit();
            return true;
        }
        else if(dadosPonto.tipo == "saida"){
            conect.exec_params("UPDATE frequencia SET horasaida = NOW() WHERE funcionario_id = $1 AND data = $2 AND hora_saida IS NULL", dadosPonto.funcionario_id, dadosPonto.horasaida);
            conect.commit();
            return true;
        }
    }catch (const std::exception& e){
        std::cerr << "Erro ao inserir produto: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DadosPonto> ModelPonto::BuscandoDadosPontos() {
    std::vector<DadosPonto> dadosPontos;
    try {
        pqxx::work coonn(*conn);
        pqxx::result res = coonn.exec("SELECT id, funcionario_id, data, horaentrada, horasaida FROM frequencia");
        for (auto row : res) {
            DadosPonto ponto;
            ponto.id = row["id"].as<int>();
            ponto.funcionario_id = row["funcionario_id"].as<int>();
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
