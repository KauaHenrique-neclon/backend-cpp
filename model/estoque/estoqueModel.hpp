#ifndef MODEL_ESTOQUE_HPP
#define MODEL_ESTOQUE_HPP

//#include <soci/soci.h>
//#include <soci/postgresql/soci-postgresql.h>
#include <vector>
#include <string>
#include "../../config/conect.hpp"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTime.h"

class Produto {
public:
    int id;
    std::string nome;
    std::string descricao;
    std::string codigo;
    std::string unidademedida;
};

class Estoque {
public:
    int id;
    int idproduto;
    std::string quantidade;
    std::string localizacao;
    std::string datavalidade;
};

class Fornecedor {
public:
    int id;
    std::string nome;
    std::string endereco;
    std::string telefone;
    std::string email;
};


class ModelEstoque {
public:
    ModelEstoque();
    //pqxx::connection* conn;
    std::vector<Produto> BuscandoDados();
    std::vector<Estoque> BuscandoDadosEstoque();
    bool InserindoProduto(const Produto& produto);
    bool EstoqueProduto(const Estoque& estoque);
    bool MovimentarProduto(int idproduto, const std::string& tipomovimentacao, const std::string& quantidade, const std::string& datamovimentacao);
    bool Fornecedores(const Fornecedor& fornecedor);
    bool Pedidos(int idproduto,int idfornecedor, std::string datapedido, std::string statuspedido, std::string itempedido);
    std::vector<Fornecedor> BuscandoFornecedores();

private:
    static pqxx::connection* conn;
};

#endif // MODEL_ESTOQUE_HPP
