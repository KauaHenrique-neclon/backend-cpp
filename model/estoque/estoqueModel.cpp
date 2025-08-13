#include "estoqueModel.hpp"
#include <iostream>
#include <stdexcept>



ModelEstoque::ModelEstoque() {
    conn = bancoDados();
    if (!conn) {
        std::cerr << "Falha ao conectar ao banco de dados no ModelEstoque." << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados.");
    }
}


std::vector<Produto> ModelEstoque::BuscandoDados() {
    std::vector<Produto> produtos;
    try {
        pqxx::work txn(*conn);
        pqxx::result res = txn.exec("SELECT id, nome, descricao, codigo, unidademedida FROM produtos");
        for (auto row : res) {
            Produto produto;
            produto.id = row["id"].as<int>();
            produto.nome = row["nome"].as<std::string>();
            produto.descricao = row["descricao"].as<std::string>();
            produto.codigo = row["codigo"].as<std::string>();
            produto.unidademedida = row["unidademedida"].as<std::string>();
            produtos.push_back(produto);
        }
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Erro ao buscar dados de produtos: " << e.what() << std::endl;
    }
    return produtos;
}


std::vector<Estoque> ModelEstoque::BuscandoDadosEstoque() {
    std::vector<Estoque> estoques;
    try {
        pqxx::work txn(*conn);
        pqxx::result res = txn.exec("SELECT id, idproduto, quantidade, localizacao, datavalidade FROM estoque");
        for (auto row : res) {
            Estoque estoque;
            estoque.id = row["id"].as<int>();
            estoque.idproduto = row["idproduto"].as<int>();
            estoque.quantidade = row["quantidade"].as<std::string>();
            estoque.localizacao = row["localizacao"].as<std::string>();
            estoque.datavalidade = row["datavalidade"].as<std::string>();
            estoques.push_back(estoque);
        }
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Erro ao buscar dados de estoque: " << e.what() << std::endl;
    }
    return estoques;
}


bool ModelEstoque::InserindoProduto(const Produto& produto) {
    try {
        pqxx::work txn(*conn);
        txn.exec0("INSERT INTO produtos (nome, descricao, codigo, unidademedida) VALUES (" +
                  txn.quote(produto.nome) + ", " +
                  txn.quote(produto.descricao) + ", " +
                  txn.quote(produto.codigo) + ", " +
                  txn.quote(produto.unidademedida) + ");");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao inserir produto: " << e.what() << std::endl;
        return false;
    }
}



bool ModelEstoque::EstoqueProduto(const Estoque& estoque) {
    try {
        pqxx::work txn(*conn);
        txn.exec0("INSERT INTO estoque (idproduto, quantidade, localizacao, datavalidade) VALUES (" +
                  txn.quote(estoque.idproduto) + ", " +
                  txn.quote(estoque.quantidade) + ", " +
                  txn.quote(estoque.localizacao) + ", " +
                  txn.quote(estoque.datavalidade) + ");");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao adicionar produto no estoque: " << e.what() << std::endl;
        return false;
    }
}


bool ModelEstoque::MovimentarProduto(int idproduto, const std::string& tipomovimentacao, const std::string& quantidade, const std::string& datamovimentacao) {
    try {
        pqxx::work txn(*conn);
        txn.exec0("INSERT INTO movimentacoes (idproduto, tipomovimentacao, quantidade, datamovimentacao) VALUES (" +
                  txn.quote(idproduto) + ", " +
                  txn.quote(tipomovimentacao) + ", " +
                  txn.quote(quantidade) + ", " +
                  txn.quote(datamovimentacao) + ");");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao movimentar produto: " << e.what() << std::endl;
        return false;
    }
}


bool ModelEstoque::Fornecedores(const Fornecedor& fornecedor) {
    try {
        pqxx::work txn(*conn);
        txn.exec0("INSERT INTO fornecedores (nome, endereco, telefone, email) VALUES (" +
                  txn.quote(fornecedor.nome) + ", " +
                  txn.quote(fornecedor.endereco) + ", " +
                  txn.quote(fornecedor.telefone) + ", " +
                  txn.quote(fornecedor.email) + ");");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao adicionar fornecedor: " << e.what() << std::endl;
        return false;
    }
}


std::vector<Fornecedor> ModelEstoque::BuscandoFornecedores() {
    std::vector<Fornecedor> fornecedores;
    try {
        pqxx::work txn(*conn);
        pqxx::result res = txn.exec("SELECT id, nome, endereco, telefone, email FROM fornecedores");
        for (auto row : res) {
            Fornecedor fornecedor;
            fornecedor.id = row["id"].as<int>();
            fornecedor.nome = row["nome"].as<std::string>();
            fornecedor.endereco = row["endereco"].as<std::string>();
            fornecedor.telefone = row["telefone"].as<std::string>();
            fornecedor.email = row["email"].as<std::string>();
            fornecedores.push_back(fornecedor);
        }
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Erro ao buscar fornecedores: " << e.what() << std::endl;
    }
    return fornecedores;
}


bool ModelEstoque::Pedidos(int idproduto, int idfornecedor, std::string datapedido, std::string statuspedido, std::string itempedido) {
    try {
        pqxx::work txn(*conn);
        txn.exec0("INSERT INTO pedidos (idproduto, idfornecedor, datapedido, statuspedido, itempedido) VALUES (" +
                  txn.quote(idproduto) + ", " +
                  txn.quote(idfornecedor) + ", " +
                  txn.quote(datapedido) + ", " +
                  txn.quote(statuspedido) + ", " +
                  txn.quote(itempedido) + ");");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao processar pedido: " << e.what() << std::endl;
        return false;
    }
}