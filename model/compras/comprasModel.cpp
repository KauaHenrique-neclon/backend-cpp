#include "comprasModel.hpp"


pqxx::connection* ModelCompras::conn = nullptr;

ModelCompras::ModelCompras() {
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

// buscando Pedidos Enviados, para aprovar pedidos
std::vector<Pedido> ModelCompras::BuscandoPedidoEnviado(){
    std::vector<Pedido> pedidos;
    try{
        pqxx::work conexao(*conn);
        std::string query = R"( SELECT pdd.id, pdd.idproduto,
                pdd.idfornecedor, pdd.status, pdd.datapedido,
                prod.nome AS nome
                FROM pedido pdd JOIN produtos prod ON prod.id = pdd.idproduto
                WHERE pdd.status = 'ENVIADO' )";
        pqxx::result res = conexao.exec(query);
        for (auto row : res) {
            Pedido pedido;
            pedido.id = row["id"].as<int>();
            pedido.idProduto = row["idproduto"].as<int>();
            pedido.idFornecedor = row["idfornecedor"].as<int>();
            pedido.datapedido = row["datapedido"].as<std::string>();
            pedido.nomeProduto = row["nome"].as<std::string>();
            pedido.status = row["status"].as<std::string>();
            pedidos.push_back(pedido);
        }
        conexao.commit();
    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar dados de pedidos: " << e.what() << std::endl;
    }
    return pedidos;
}


// Inserindo Pedido no banco de dados
bool ModelCompras::InserindoPedido(const Pedido& pedido){
    try{
        pqxx::work conexao(*conn);
        std::string query = "INSERT INTO pedido (idproduto, idfornecedor, datapedido, status) VALUES (" +
            conexao.quote(pedido.idProduto) + ", " +
            conexao.quote(pedido.idFornecedor) + ", " +
            conexao.quote(pedido.datapedido) + ", " +
            conexao.quote(pedido.status) + ");";
        conexao.commit();
        return true; 
    }catch(const std::exception& e){
        std::cerr << "Erro ao inserir Pedido: " << e.what() << std::endl;
        return false;
    }
}


// aprovando pedidos, para enviar para o setor de entregas
bool ModelCompras::AprovandoPedido(int idpedido, const std::string& status) {
    try{
        pqxx::work conexao(*conn);
        std::string query = "UPDATE pedido SET status = " + conexao.quote(status) +
            " WHERE id = " + conexao.quote(idpedido) + ";";
        conexao.exec(query);
        conexao.commit();
        return true;
    }catch(const std::exception& e){
        std::cerr << "Erro ao aprovar pedido" << e.what() << std::endl;
        return false;
    }
}




// pedidos aceitos, buscando pedidos aceitos para mostrar no
// painel de pedidos para entregar
std::vector<Pedido> ModelCompras::BuscandoPedidosAceitos(){

    std::cout << "dentro do buscando pedidos aceitos" << std::endl;
    std::vector<Pedido> pedidos;
    try{
        pqxx::work conexao(*conn);
        std::string query = R"(SELECT pdd.id, pdd.idproduto,
                pdd.idfornecedor, pdd.status, pdd.datapedido,
                prod.nome AS nome,
                forn.nome AS nomeForn
                FROM pedido pdd 
                JOIN produtos prod ON prod.id = pdd.idproduto 
                JOIN fornecedores forn ON forn.id = pdd.idfornecedor
                WHERE pdd.status = 'APROVADA')";
        pqxx::result res = conexao.exec(query);
        for (auto row : res) {
            Pedido pedido;
            pedido.id = row["id"].as<int>();
            pedido.idProduto = row["idproduto"].as<int>();
            pedido.idFornecedor = row["idfornecedor"].as<int>();
            pedido.datapedido = row["datapedido"].as<std::string>();
            pedido.nomeProduto = row["nome"].as<std::string>();
            pedido.nomeFornecedor = row["nomeForn"].as<std::string>();
            pedido.status = row["status"].as<std::string>();
            pedidos.push_back(pedido);
        }
        conexao.commit();
    }catch(const std::exception& e){
        std::cerr << "Erro ao buscar pedidos aceitos" << e.what() << std::endl;
    }
    return pedidos;
}



// finalizando pedidos, setor de entregas
bool ModelCompras::FinalizandoPedido(int idpedido, const std::string& status, const std::string& motivo){
    try{
        pqxx::work conexao(*conn);
        if(motivo == "CANCELADO"){
            if (motivo.empty()) {
                throw std::runtime_error("Motivo obrigatório para cancelamento");
                return false;
            }
            std::string query = "UPDATE pedido SET status = " + conexao.quote(status) +
                ", motivo_cancelamento = " + conexao.quote(motivo) +
                " WHERE id = " + conexao.quote(idpedido) + ";";
            conexao.exec(query);
            conexao.commit();
        }else{
            std::string query = "UPDATE pedido SET status = " + conexao.quote(status) +
                "WHERE id = " + conexao.quote(idpedido) + ";";
            conexao.exec(query);
            conexao.commit();
        }
        return true;
    }catch(const std::exception& e){
        std::cerr << "Erro ao Finalizar pedido" << e.what() << std::endl;
        return false;
    }
}