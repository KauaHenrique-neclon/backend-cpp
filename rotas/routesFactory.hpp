#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>

// importando as rotas e rotas.hpp
#include "rotas.hpp"
#include "estoque/ProdutoRoutes.hpp"
#include "login/loginRoutes.hpp"
#include "empresa/empresaRoutes.hpp"
#include "compras/comprasRoutes.hpp"
#include "cadastro/cadastroRoutes.hpp"

// importando o Middleware
#include "../middleware/CORSHandler.hpp"

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory {
private:
    RouteMap routes;
    std::string basePath;

public:
    MyRequestHandlerFactory(const std::string& basePath) : basePath(basePath){
        registerProdutoRoutes(routes);
        registerLoginRoutes(routes);
        registerEmpresaRoutes(routes);
        registerComprasRoutes(routes);
        registerCadastroRoutes(routes);
    }

    HTTPRequestHandler* createRequestHandler(
        const HTTPServerRequest& request) override
    {
        std::string path = request.getURI();
        auto pos = path.find('?');
        if (pos != std::string::npos) {
            path = path.substr(0, pos);
        }
        std::cerr << "[DEBUG] Rota solicitada: " << path << " | Método: " << request.getMethod() << std::endl;
        auto it = routes.find(path);
        if (it != routes.end()) {
            //return it->second();
            std::cerr << "[DEBUG] Rota encontrada. Chamando handler..." << std::endl;
            return new CORSHandler(it->second());
        }
        class NotFoundHandler : public HTTPRequestHandler {
        public:
            void handleRequest(HTTPServerRequest&, HTTPServerResponse& response) override {
                response.setStatus(HTTPServerResponse::HTTP_NOT_FOUND);
                response.setContentType("application/json");
                response.send() << R"({"error":"Rota não encontrada"})";
            }
        };

        return new NotFoundHandler();
    }
};