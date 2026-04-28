#include "dadosHome.hpp"


void DadosHomeViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    //cookieMiddleware.cookieMiddleware(request, response);
    
    response.set("Access-Control-Allow-Origin", "http://localhost:3000");
    response.set("Access-Control-Allow-Credentials", "true");
    response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response.set("Access-Control-Allow-Headers", "Content-Type");

    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.send();
        return;
    }
    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET){
        Get(response);
    } else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void DadosHomeViews::Get(Poco::Net::HTTPServerResponse& response) {
    try{
        response.setContentType("application/json");
        ModelHome modelHome;
        std::vector<DadosDoHome> dadosDashboard = modelHome.buscandoDadosDashboard();

        for (const auto dados : dadosDashboard) {
            std::cout << "Forne: " << dados.totalFornecedores
                << "Estoque: " << dados.TotalItemEstoque
                << "Produto: " << dados.totalProdutos
                << std::endl;
        }
        Poco::JSON::Array arrayDadosDashboard;
        Poco::JSON::Object responseObj;
        responseObj.set("dados", arrayDadosDashboard);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, ostr);
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}