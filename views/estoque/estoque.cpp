#include "estoque.hpp"

void EstoqueViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    
    cookieMiddleware.cookieMiddleware(request, response);

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


void EstoqueViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        /*
        if(!sessao.IsAuthenticated()) {

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }*/


        response.setContentType("application/json");

        ModelEstoque modelEstoque;
        std::vector<Produto> dadosEstoque = modelEstoque.BuscandoDados();

        Poco::JSON::Array array;

        for (const auto& produto : dadosEstoque) {
            Poco::JSON::Object obj;
            obj.set("id", produto.id);
            obj.set("nome", produto.nome);
            obj.set("descricao", produto.descricao);
            obj.set("codigo", produto.codigo);
            obj.set("unidademedida", produto.unidademedida);
            array.add(obj);
        }

        Poco::JSON::Object responseObj;
        responseObj.set("dados", array);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, ostr);


    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}