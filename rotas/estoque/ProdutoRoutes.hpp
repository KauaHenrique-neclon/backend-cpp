#pragma once
#include "../../views/estoque/estoque.hpp"
#include "../../views/estoque/cadastrarProduto.hpp"
#include "../../views/estoque/removerProduto/removerProduto.hpp"
#include "../rotas.hpp"

inline void registerProdutoRoutes(RouteMap& routes) {
    routes["/estoque"] = [] { return new EstoqueViews(); };
    routes["/cadastrarProduto"] = [] { return new CadastrarProdutoView(); };
    routes["/removerProduto"] = [] { return new RemoverProdutoViews(); };
}