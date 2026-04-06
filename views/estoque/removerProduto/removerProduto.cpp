#include "removerProduto.hpp"

void RemoverProdutoViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    
    //cookieMiddleware.cookieMiddleware(request, response);

    response.set("Access-Control-Allow-Origin", "http://localhost:3000");
    response.set("Access-Control-Allow-Credentials", "true");
    response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response.set("Access-Control-Allow-Headers", "Content-Type");

    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.send();
        return;
    }
    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET){
        Get(response);
    }
    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST){
        Post(request, response);
    }
    else{
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void RemoverProdutoViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        response.setContentType("application/json");
        ModelEstoque modelEstoque;
        std::vector<Produto> dadosEstoque = modelEstoque.BuscandoDados();

        for (const auto& produto : dadosEstoque) {
            std::cout << "ID: " << produto.id 
                      << " Nome: " << produto.nome 
                      << std::endl;
        }

        Poco::JSON::Array array;
        for (const auto& produto : dadosEstoque){
            Poco::JSON::Object obj;
            obj.set("id", produto.id);
            obj.set("nome", produto.nome);
            obj.set("descricao", produto.descricao);
            obj.set("codigo", produto.codigo);
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

void RemoverProdutoViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        /*
        if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }
        */

        // pegando o JSON do React
        std::string body;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var resultado = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = resultado.extract<Poco::JSON::Object::Ptr>();


        std::string idProduto = object->getValue<std::string>("id");

        if(idProduto.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        
        int idProdutoInt = std::stoi(idProduto);
        ModelEstoque modelEstoque;
        bool resultadoDesativamento = modelEstoque.RemoverProduto(idProdutoInt);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Produto desativado com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao desativar o produto.\"}";
        }

    }catch (const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Erro ao cadastrar Produto." << e.what() << "\"}";
    }
}