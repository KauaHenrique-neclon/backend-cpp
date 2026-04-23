#ifndef MODEL_COMPRAS_HPP
#define MODEL_COMPRAS_HPP


#include <vector>
#include <string>
#include "../../config/conect.hpp"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTime.h"


class Pedido {
public:
    int id;
    int idProduto;
    int idFornecedor;
    std::string datapedido;
    std::string status;
    std::string nomeProduto;
    std::string nomeFornecedor;
};


class ModelCompras {
public:
    ModelCompras();
    bool InserindoPedido(const Pedido& pedido);
    std::vector<Pedido> BuscandoPedidoEnviado();
    bool AprovandoPedido(int idpedido, const std::string& status);
    std::vector<Pedido> BuscandoPedidosAceitos();
    bool FinalizandoPedido(int idpedido, const std::string& status, const std::string& motivo = "");

private:
    static pqxx::connection* conn;
};


#endif // MODEL_COMPRAS_HPP