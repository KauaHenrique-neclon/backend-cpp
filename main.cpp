#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include <Poco/URI.h>
#include <iostream>

#include "session/sessao.hpp"
#include "middleware/cookie.hpp"

// importando os views 
#include "views/home/home.hpp"
#include "views/login/login.hpp"
#include "views/cadastro/cadastrar.hpp"
#include "views/estoque/cadastrarProduto.hpp"
#include "views/estoque/estoque.hpp"
#include "views/compras/fornecedores/fornecedores.hpp"
#include "views/compras/pedidos/pedidos.hpp"
#include "views/empresa/funcionarios/cadastrarFunc.hpp"
#include "views/empresa/controlePonto/controlePonto.hpp"
#include "views/empresa/financas/contabilidade/contabilidade.hpp"


using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

class HomePage : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        Session sessao;
        HomeClass home(sessao);
        home.render(response);
    }
};

class LoginPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        LoginView login;
        login.handleRequest(request, response);
    }
};

class CadastrarPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{  
    }
};

class CadastrarProdutoPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override{
        Session sessao;
        Cookie cookie(sessao);
        if (!sessao.IsAuthenticated()) {            
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }
        CadastrarProdutoView cadastroProduto(sessao, cookie);
        cadastroProduto.handleRequest(request, response);
    }
};

class EstoquePage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        Session sessao;
        Cookie cookie(sessao);

        if (!sessao.IsAuthenticated()) {            
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }
        EstoqueViews estoqueView(sessao, cookie);
        estoqueView.handleRequest(request, response);
    }
};


class FornecedoresPage : public HTTPRequestHandler{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
        Session sessao;
        Cookie cookie(sessao);
        if (!sessao.IsAuthenticated()) {            
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
            response.send() << "A sessão não está ativa.";
            return;
        }
        FornecedoresViews fornecedoresViews(sessao, cookie);
        fornecedoresViews.handleRequest(request, response);
    }
};

class PedidosPage : public HTTPRequestHandler{
public:

    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
        Session sessao;
        PedidosViews pedidosViews(sessao);
        pedidosViews.handleRequest(request, response);
    }
};


class ControleDePontoPage : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        try {
            Session sessao;
            Cookie cookie(sessao);
            if (!sessao.IsAuthenticated()) {
                response.setStatus(HTTPServerResponse::HTTP_UNAUTHORIZED);
                response.send() << "A sessão não está ativa.";
                return;
            }
            ControleDePontoViews controleDePontoViews(sessao, cookie);
            controleDePontoViews.handleRequest(request, response);
        } catch (const std::exception& e) {
            response.setStatus(HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.send() << "Erro interno do servidor.";
        }
    }
};

class ContabilidadePage : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        try {
            Session sessao;
            Cookie cookie(sessao);
            if (!sessao.IsAuthenticated()) {
                response.setStatus(HTTPServerResponse::HTTP_UNAUTHORIZED);
                response.send() << "A sessão não está ativa.";
                return;
            }
            ContabilidadeViews contabilidadeViews(sessao, cookie);
            contabilidadeViews.handleRequest(request, response);
        } catch (const std::exception& e) {
            response.setStatus(HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.send() << "Erro interno do servidor.";
        }
    }
};


class MyRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
    MyRequestHandlerFactory(const std::string& basePath) : _basePath(basePath) {}
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) override {
        Poco::URI uri(request.getURI());
        const std::string& path = uri.getPath();
        
        if (path == "/") {
            std::cerr << "Request no Login" << std::endl;
            return new LoginPage();
        } else if (path == "/cadastrar"){
            std::cerr << "Request no Cadastro" << std::endl;
            return new CadastrarPage();
        } else if (path == "/home") {
            return new HomePage();
        } else if (path == "/cadastrarProduto"){
            return new CadastrarProdutoPage();
        } else if (path == "/Estoque"){
            return new EstoquePage();
        } else if (path == "/Fornecedores"){
            return new FornecedoresPage();
        } else if (path == "/pedidos"){
            return new PedidosPage();
        }else if (path == "/Contabilidade"){
            return new ContabilidadePage();
        }
        else {
            return;
        }
    }
private:
    std::string _basePath;
};

class MyServer : public ServerApplication {
protected:
    int main(const std::vector<std::string>& args) override {
        UInt16 port = 9980;
        ServerSocket svs(port);
        std::string basePath = "C:\\backend cpp\\static";
        HTTPServer s(new MyRequestHandlerFactory(basePath), svs, new HTTPServerParams());
        s.start();

        std::cout << "Server started on port " << port << std::endl;
        waitForTerminationRequest();
        s.stop();
        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv) {
    MyServer app;
    return app.run(argc, argv);
}

// g++ -o server server.cpp views/cadastro/cadastrar.cpp views/home/home.cpp views/login/login.cpp -lPocoNet -lPocoUtil -lPocoFoundation -lpqxx -lpq

// http://localhost:9980/

// g++ *.cpp -o server -lPocoNet -lPocoUtil -lPocoFoundation -lpqxx -lpq