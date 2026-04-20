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
              << ", Nome: " << pedido.nomeProduto
              << ", Data: " << pedido.datapedido
              << std::endl;
        }

        // preparando o objeto
        for (const auto& pedido : dadosPedidos) {
            Poco::JSON::Object obj;
            obj.set("id", pedido.id);
            obj.set("idFornecedor", pedido.idFornecedor);
            obj.set("idProduto", pedido.idProduto);
            obj.set("status", pedido.status);
            obj.set("nomeProduto", pedido.nomeProduto);
            obj.set("datapedido", pedido.datapedido);
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
    try{
        /*if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }*/

        response.setContentType("application/json");

        std::string body;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr objeto = result.extract<Poco::JSON::Object::Ptr>();

        std::string idProduto = objeto->getValue<std::string>("idPedido");
        std::string status = objeto->getValue<std::string>("status");
        
        // validar dados vindo do front
        if (idProduto.empty() || status.empty()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        int idProdutoInt = std::stoi(idProduto);
        ModelCompras modelCompras;
        bool resultado = modelCompras.AprovandoPedido(idProdutoInt, status);
        if (resultado) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Pedido com status mudado com sucesso\"}";
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao mudar pedido\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Erro ao aprovar pedidos." << e.what() << "\"}";
    }
}