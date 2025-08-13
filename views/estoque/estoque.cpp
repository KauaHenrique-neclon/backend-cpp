#include "estoque.hpp"

void EstoqueViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    cookieMiddleware.cookieMiddleware(request, response);
    // ele verifica se o cookie já enviou uma mensagem ou n
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        return; 
    }
    if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    } else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void EstoqueViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        if(!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }
    
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
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(array, ostr);
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}