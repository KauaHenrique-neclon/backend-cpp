#ifndef MODEL_DADOS_HPP
#define MODEL_DADOS_HPP

#include "../../config/conect.hpp"
#include <string>
#include <vector>
#include <stdexcept>

class DadosDoHome{
    public:
        int TotalItemEstoque;
        int TotalPessoasCadastrada;
        int totalFornecedores;
        int totalPedidosAtivos;
        int totalProdutos;
};

class ModelHome{
    private:
        static pqxx::connection* conn;
    public:
        ModelHome();
        std::vector<DadosDoHome> buscandoDadosDashboard();
};

#endif