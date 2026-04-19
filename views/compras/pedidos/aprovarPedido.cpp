#include "aprovarPedido.hpp"


void AprovarPedidoViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
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


void AprovarPedidoViews::Get(Poco::Net::HTTPServerResponse& response) {
    try{
        /*if(!sessao.IsAuthenticated()) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Acesso Negado\"}";
        return;
        }*/
        response.setContentType("application/json");
        ModelCompras modelCompras;
        std::vector<Pedido> dadosPedidos = modelCompras.BuscandoPedidoEnviado();
        
        Poco::JSON::Array arrayPedidosEnviados;

        std::cout << "=== Pedidos ativos" << std::endl;
        for (const auto& pedido : dadosPedidos) {
            std::cout << "ID: " << pedido.id
              << ", Status: " << pedido.status
              << std::endl;
        }

        // preparando o objeto
        for (const auto& pedido : dadosPedidos) {
            Poco::JSON::Object obj;
            obj.set("id", pedido.id);
            obj.set("idFornecedor", pedido.idFornecedor);
            obj.set("idProduto", pedido.idProduto);
            obj.set("item", pedido.item);
            obj.set("status", pedido.status);
            arrayPedidosEnviados.add(obj);
        }

        // envindo objeto
        Poco::JSON::Object responseObg;
        responseObg.set("dadosPedidos", arrayPedidosEnviados);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObg, ostr);
    }catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}

void AprovarPedidoViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    
}