#include "pedidosAceitos.hpp"

void PedidosAceitos::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    

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


void PedidosAceitos::Get(Poco::Net::HTTPServerResponse& response) {
    try{

        response.setContentType("application/json");

        ModelCompras modelCompras;
        std::vector<Pedido> dadosPedidosAceitos = modelCompras.BuscandoPedidosAceitos();

        Poco::JSON::Array arrayPedidosAceitos;

        std::cout << "=== Pedidos ativos === " << std::endl;
        for (const auto& pedido : dadosPedidosAceitos) {
            std::cout << "ID: " << pedido.id
              << ", Nome: " << pedido.nomeProduto
              << ", Status: " << pedido.status
              << ", nome fornecedor: " << pedido.nomeFornecedor
              << std::endl;
        }

        // preparar o objeto para enviar pro React
        for (const auto& pedido : dadosPedidosAceitos) {
            Poco::JSON::Object obj;
            obj.set("id", pedido.id);
            obj.set("idFornecedor", pedido.idFornecedor);
            obj.set("idProduto", pedido.idProduto);
            obj.set("status", pedido.status);
            obj.set("nomeProduto", pedido.nomeProduto);
            obj.set("datapedido", pedido.datapedido);
            obj.set("nomeForn", pedido.nomeFornecedor);
            arrayPedidosAceitos.add(obj);
        }

        // envio do objeto
        Poco::JSON::Object responseObj;
        responseObj.set("dadosPedidoAceito", arrayPedidosAceitos);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, ostr);
    }catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}


void PedidosAceitos::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try{
        response.setContentType("application/json");

        std::string body;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr objeto = result.extract<Poco::JSON::Object::Ptr>();

        std::string idPedido = objeto->getValue<std::string>("idPedido");
        std::string status = objeto->getValue<std::string>("status");
        std::string motivo;
        if (objeto->has("motivo")) {
            motivo = objeto->getValue<std::string>("motivo");
        } else {
            motivo = ""; // valor padrão 
        }

        // validar dados vindo do front
        if (idPedido.empty() || status.empty()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        int idPedidoInt = std::stoi(idPedido);

        ModelCompras modelCompras;
        bool resultado = modelCompras.FinalizandoPedido(idPedidoInt, status, motivo);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Pedido Finalizado com Sucesso\"}";
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao finalizar pedido\"}";
        }
    }catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Erro ao aprovar pedidos." << e.what() << "\"}";
    }
}