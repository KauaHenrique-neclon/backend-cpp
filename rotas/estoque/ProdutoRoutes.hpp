#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views
#include "../../views/estoque/estoque.hpp"
#include "../../views/estoque/removerProduto/removerProduto.hpp"
#include "../../views/estoque/cadastrarProduto.hpp"


// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"



using namespace Poco;
using namespace Poco::Net;

class EstoquePage : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request,HTTPServerResponse& response) override {
        Session sessao;
        Cookie cookie(sessao);

        EstoqueViews estoqueView(sessao, cookie);
        estoqueView.handleRequest(request, response);
    }
};

class RemoverProdutoPage : public HTTPRequestHandler{
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        Session sessao;
        Cookie cookie(sessao);

        /*if (!sessao.IsAuthenticated()) {            
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }*/
        RemoverProdutoViews removerProdutoView;
        removerProdutoView.handleRequest(request, response);
    }
};

class CadastrarProdutoPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        Session sessao;
        Cookie cookie(sessao);
        /*if (!sessao.IsAuthenticated()) {            
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }*/
        CadastrarProdutoView cadastroProduto(sessao, cookie);
        cadastroProduto.handleRequest(request, response);
    }
};





using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()>>;

inline void registerProdutoRoutes(RouteMap& routes) {
    routes["/estoque"] = []() -> HTTPRequestHandler* {
        std::cerr << "[DEBUG] Chamando a função do estoque " << std::endl;
        return new EstoquePage(); 
    };
    routes["/estoque/cadastrar"] = []() -> HTTPRequestHandler* {
        return new CadastrarProdutoPage();
    };
    routes["/estoque/remover"] = []() -> HTTPRequestHandler* {
        return new RemoverProdutoPage();
    };
}