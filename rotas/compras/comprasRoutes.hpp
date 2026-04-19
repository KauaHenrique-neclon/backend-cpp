#include <Poco/Net/HTTPRequestHandler.h>
#include "../../middleware/cookie.hpp"
#include <unordered_map>
#include <functional>
#include <Poco/Net/HTTPRequestHandler.h>

// importanto views
#include "../../views/compras/fornecedores/fornecedores.hpp"
#include "../../views/compras/pedidos/pedidos.hpp"
#include "../../views/compras/fornecedores/listaFornecedores.hpp"
#include "../../views/compras/pedidos/aprovarPedido.hpp"

// importando cookies
#include "session/sessao.hpp"
#include "middleware/cookie.hpp"

using namespace Poco;
using namespace Poco::Net;

class FornecedoresPage : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session sessao;
        Cookie cookie(sessao);
        /*if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }*/
        FornecedoresViews fornecedoresViews(sessao, cookie);
        fornecedoresViews.handleRequest(request, response);
    }
};

class ListaFornecedoresPage : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session sessao;
        Cookie cookie(sessao);
        /*if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }*/
        ListaFornecedoresViews listaFornecedores(sessao, cookie);
        listaFornecedores.handleRequest(request, response);
    }
};

class PedidosPage : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        try
        {
            Session sessao;
            Cookie cookie(sessao);
            /*if (!sessao.IsAuthenticated()) {
                response.setStatus(HTTPServerResponse::HTTP_UNAUTHORIZED);
                response.send() << "A sessão não está ativa.";
                return;
            }*/
            PedidosViews pedidosViews(sessao, cookie);
            pedidosViews.handleRequest(request, response);
        }
        catch (const std::exception &e)
        {
            response.setStatus(HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.send() << "Erro interno do servidor.";
        }
    }
};


class AprovarPedidoPage : public HTTPRequestHandler 
{
    public:
        void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
        {
            try{
                Session sessao;
                Cookie cookie(sessao);
                /*if (!sessao.IsAuthenticated()) {
                    response.setStatus(HTTPServerResponse::HTTP_UNAUTHORIZED);
                    response.send() << "A sessão não está ativa.";
                    return;
                }*/
                AprovarPedidoViews aprovarPedidoView(sessao, cookie);
                aprovarPedidoView.handleRequest(request, response);
            }catch(const std::exception &e){
                response.setStatus(HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
                response.send() << "Erro interno do servidor.";
            }
        }
};



using RouteMap = std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler *()>>;

inline void registerComprasRoutes(RouteMap &routes)
{
    routes["/fornecedores"] = []() -> HTTPRequestHandler *
    {
        return new FornecedoresPage();
    };
    routes["/pedidos"] = []() -> HTTPRequestHandler *
    {
        return new PedidosPage();
    };
    routes["/listaFornecedores"] = []() -> HTTPRequestHandler *
    {
        return new ListaFornecedoresPage();
    };
    routes["/aprovarPedido"] = []() -> HTTPRequestHandler * {
        return new AprovarPedidoPage();
    };
}