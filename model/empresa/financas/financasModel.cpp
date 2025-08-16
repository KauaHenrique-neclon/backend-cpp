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
        conect.exec0("INSERT INTO contas(nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento, codigo_barra) VALUES (" +
            conect.quote(conta.nome) +" , " +
            conect.quote(conta.tipo) + ", " +
            conect.quote(conta.preco) + ", " +
            conect.quote(conta.status) + ", " +
            conect.quote(conta.vencimento) + " , " +
            conect.quote(conta.dia_lancamento) + ", " +
            conect.quote(conta.codigoBarra) + ");");
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
        pqxx::result resultado = conect.exec("SELECT id ,nome_conta, tipo_conta, preco, status, vencimento, dia_lancamento,codigo_barra FROM contas");
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
            conta.codigoBarra = linha["codigo_barra"].as<int>();
            dados.push_back(conta);
        }
    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar dados de contas: " << e.what() << std::endl;
    }
    return dados;
}

bool FinancasModel::inserirOrcamento(const DadosOrcamento& orcamento){
    try{
        pqxx::work conect(*conn);
        pqxx::result resultado = conect.exec0("INSERT INTO orcamento(nome_orcamento, preco, status, datapedido, descricao) VALUES(" + 
            conect.quote(orcamento.nome_orcamento) +" , " +
            conect.quote(orcamento.preco) + ", " +
            conect.quote(orcamento.status) + ", " +
            conect.quote(orcamento.datapedido) + ", " +
            conect.quote(orcamento.descricao) + ");");
        conect.commit();
        return true;
    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir Orçamento: " << e.what() << std::endl;
        return false;
    }
}


std::vector<DadosOrcamento> FinancasModel::BuscandoOrcamento(){
    std::vector<DadosOrcamento> dados;
    try{
        pqxx::work conect(*conn);
        pqxx::result resultado = conect.exec0("SELECT id, nome_orcamento, preco, status, datapedido, descricao FROM orcamento");
        conect.commit();
        for(const auto& linha : resultado){
            DadosOrcamento orcamento;
            orcamento.id = linha["id"].as<int>();
            orcamento.nome_orcamento = linha["nome_orcamento"].as<std::string>();
            orcamento.preco = linha["preco"].as<std::string>();
            orcamento.status = linha["status"].as<std::string>();
            orcamento.datapedido = linha["datapedido"].as<std::string>();
            orcamento.descricao = linha["descricao"].as<std::string>();
            dados.push_back(orcamento);
        }
    }catch(const std::exception& e){
       std::cerr << "Erro ao buscar dados de orçamentos: " << e.what() << std::endl; 
    }
    return dados;
}


FinancasModel::~FinancasModel(){
    delete conn;
}