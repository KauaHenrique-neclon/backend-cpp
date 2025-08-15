#include "financasModel.hpp"

FinancasModel::FinancasModel(){
    conn = bancoDados();
    if (!conn) {
        std::cerr << "Falha ao conectar ao banco de dados no ModelEstoque." << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados.");
    }
}

bool FinancasModel::inserindoConta(const DadosConta& conta){
    pqxx::work conect(*conn);
    try{
        conect.exec0("INSERT INTO contas(nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento) VALUES (" +
            conect.quote(conta.nome) +" , " +
            conect.quote(conta.tipo) + ", " +
            conect.quote(conta.preco) + ", " +
            conect.quote(conta.status) + ", " +
            conect.quote(conta.vencimento) + " , " +
            conect.quote(conta.dia_lancamento) + " );");
        conect.commit();
        return true;
    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir produto: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DadosConta> FinancasModel::BuscandoContas(){
    std::vector<DadosConta> dados;
    try{
        pqxx::work conect(*conn);
        pqxx::result resultado = conect.exec("SELECT id ,nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento FROM contas");
        conect.commit();
        for (const auto& linha : resultado) {
            DadosConta conta;
            conta.id = linha["id"].as<int>();
            conta.nome = linha["nome_conta"].as<std::string>();
            conta.tipo = linha["tipo_conta"].as<std::string>();
            conta.preco = linha["preco"].as<float>();
            conta.status = linha["status"].as<std::string>();
            conta.vencimento = linha["vencimento"].as<std::string>();
            conta.dia_lancamento = linha["dia_lancamento"].as<std::string>();
            dados.push_back(conta);
        }
    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar dados de contas: " << e.what() << std::endl;
    }
    return dados;
}

FinancasModel::~FinancasModel(){
    delete conn;
}