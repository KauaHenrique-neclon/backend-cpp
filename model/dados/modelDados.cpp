#include "modelDados.hpp"


pqxx::connection* ModelHome::conn = nullptr;

ModelHome::ModelHome() {
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

std::vector<DadosDoHome> ModelHome::buscandoDadosDashboard(){
    std::vector<DadosDoHome> dadosHome;
    try{
        pqxx::work conexao(*conn);
        std::string countTable = R"(
            SELECT
                (SELECT COUNT(*) FROM estoque) AS estoque_count,
                (SELECT COUNT(*) FROM fornecedores) AS fornecedores_count,
                (SELECT COUNT(*) FROM pedidos WHERE status = 'ENVIADO') AS pedidoAtivo_count,
                (SELECT COUNT(*) FROM produto) AS produtos_count,
                (SELECT COUNT(*) FROM usuarios) AS usuarios_count
        )";
        pqxx::row row = conexao.exec1(countTable);
        DadosDoHome dados;
        dados.TotalItemEstoque = row["estoque_count"].as<int>();
        dados.totalFornecedores = row["fornecedores_count"].as<int>();
        dados.totalPedidosAtivos = row["pedidoAtivo_count"].as<int>();
        dados.totalProdutos = row["produtos_count"].as<int>();
        dados.TotalPessoasCadastrada = row["usuarios_count"].as<int>();
        dadosHome.push_back(dados);
        conexao.commit();
    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar dados do home" << std::endl;
    }
    return dadosHome;
}