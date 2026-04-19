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

// buscandoPedidosEnviados
std::vector<Pedido> ModelCompras::BuscandoPedidoEnviado(){
    std::vector<Pedido> pedidos;
    try{
        pqxx::work conexao(*conn);
        std::string query = "SELECT * FROM pedidos WHERE status = enviado";
        pqxx::result res = conexao.exec(query);
        for (auto row : res) {
            Pedido pedido;
            pedido.id = row["id"].as<int>();
            pedido.idProduto = row["idproduto"].as<int>();
            pedido.idFornecedor = row["idfornecedor"].as<int>();
            pedido.datapedido = row["datapedido"].as<std::string>();
            pedido.item = row["item"].as<std::string>();
            pedidos.push_back(pedido);
        }
        conexao.commit();
    }catch(const std::exception &e){
        std::cerr << "Erro ao buscar dados de produtos: " << e.what() << std::endl;
    }
    return pedidos;
}


// Inserindo Pedido
bool ModelCompras::InserindoPedido(const Pedido& pedido){
    try{
        pqxx::work conexao(*conn);
        std::string query = "INSERT INTO pedido (idproduto, idfornecedor, datapedido, status, item) VALUES (" +
            conexao.quote(pedido.idProduto) + ", " +
            conexao.quote(pedido.idFornecedor) + ", " +
            conexao.quote(pedido.datapedido) + ", " +
            conexao.quote(pedido.status) + ", " +
            conexao.quote(pedido.item) + ");";
        conexao.commit();
        return true; 
    }catch(const std::exception &e){
        std::cerr << "Erro ao inserir Pedido: " << e.what() << std::endl;
        return false;
    }
}

bool ModelCompras::AprovandoPedido(int idpedido, const std::string& status) {
    try{
        pqxx::work conexao(*conn);
        std::string query = "UPDATE pedido SET status = " + conexao.quote(status) +
            " WHERE idpedido = " + conexao.quote(idpedido) + ";";
        conexao.exec(query);
        conexao.commit();
        return true;
    }catch(const std::exception &e){
        std::cerr << "Erro ao aprovar pedido" << e.what() << std::endl;
        return false;
    }
}
