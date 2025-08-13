#include "movimentandoProduto.hpp"

void RemoverProduto::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST){
        Post(request, response);
    }else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET){
        Get(response);
    }else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void RemoverProduto::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        std::string body;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        std::string idProduto = object->getValue<std::string>("idProduto");
        int idProdutoInt = std::stoi(idProduto);
        std::string tipo = object->getValue<std::string>("tipo");
        std::string quantidade = object->getValue<std::string>("quantidade");
        std::string data = object->getValue<std::string>("data");
        if(idProduto.empty() || tipo.empty() || quantidade.empty() || data.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Id do produto não encontrado.\"}";
            return;
        }
        ModelEstoque modelestoque;
        bool resultado = modelestoque.MovimentarProduto(idProdutoInt, tipo, quantidade, data);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Produto removido com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao remover Produto\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}


void RemoverProduto::Get(Poco::Net::HTTPServerResponse& response) {
    response.setContentType("application/json");

    ModelEstoque modelEstoque;
    std::vector<Produto> dadosEstoque = modelEstoque.BuscandoDados();


    std::stringstream jsonData;
    jsonData << "[";
    for (const auto& produto : dadosEstoque) {
        jsonData << "{\"id\":\"" << produto.id << "\",";
        jsonData << "\"nome\":\"" << produto.nome << "\",";
        jsonData << "\"descricao\":\"" << produto.descricao << "\",";
        jsonData << "\"codigo\":\"" << produto.codigo << "\",";
        jsonData << "\"unidademedida\":\"" << produto.unidademedida << "\"},";
    }
    if (!dadosEstoque.empty()) {
        jsonData.seekp(-1, std::ios_base::cur);
    }
    jsonData << "]";
    response.send() << jsonData.str();
}
