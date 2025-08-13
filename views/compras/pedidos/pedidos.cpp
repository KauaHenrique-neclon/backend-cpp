#include "pedidos.hpp"


void PedidosViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){
        Post(request, response);
    }
    else if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    } else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void PedidosViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        if(!sessao.IsAuthenticated()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }
        std::string body;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
        std::string idProduto = object->getValue<std::string>("idProduto");
        std::string idfornecedor = object->getValue<std::string>("idfornecedor");
        std::string datapedido = object->getValue<std::string>("datapedido");
        std::string status = object->getValue<std::string>("statuspedido");
        std::string item = object->getValue<std::string>("itempedido");

        int idProdutoInt = std::stoi(idProduto);
        int idFornecedorInt = std::stoi(idfornecedor);
        if(idProduto.empty() || idfornecedor.empty() || datapedido.empty() || status.empty() || item.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;   
        }
        ModelEstoque modelestoque;
        bool resultado = modelestoque.Pedidos(idProdutoInt, idFornecedorInt, datapedido, status, item);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Pedido enviado com sucesso.\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}

void PedidosViews::Get(Poco::Net::HTTPServerResponse& response){
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
        std::vector<Fornecedor> dadosFornecedores = modelEstoque.BuscandoFornecedores();

        std::stringstream jsonData;
        jsonData << "{\"estoque\":[";
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
        jsonData << "],\"fornecedores\":[";
        for (const auto& fornecedor : dadosFornecedores) {
            jsonData << "{\"id\":\"" << fornecedor.id << "\",";
            jsonData << "\"nome\":\"" << fornecedor.nome << "\",";
            jsonData << "\"endereço\":\"" << fornecedor.endereco << "\",";
            jsonData << "\"telefone\":\"" << fornecedor.telefone << "\",";
            jsonData << "\"email\":\"" << fornecedor.email << "\"},";
        }
        if (!dadosFornecedores.empty()) {
            jsonData.seekp(-1, std::ios_base::cur);
        }
        jsonData << "]}";

        response.send() << jsonData.str();
    } catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}