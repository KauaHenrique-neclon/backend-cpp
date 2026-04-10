#include "pedidos.hpp"


void PedidosViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    
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

        Poco::JSON::Array arrayEstoque;

        for (const auto& produto : dadosEstoque) {
            Poco::JSON::Object obj;
            obj.set("id", produto.id);
            obj.set("nome", produto.nome);
            obj.set("descricao", produto.descricao);
            obj.set("codigo", produto.codigo);
            obj.set("unidademedida", produto.unidademedida);
            arrayEstoque.add(obj);
        };
        Poco::JSON::Array arrayFornecedor;
        for (const auto& fornecedor : dadosFornecedores) {
            Poco::JSON::Object obj;
            obj.set("id", fornecedor.id);
            obj.set("nome", fornecedor.nome);
            obj.set("endereco", fornecedor.endereco);
            obj.set("telefone", fornecedor.telefone);
            obj.set("email", fornecedor.email);
            arrayFornecedor.add(obj);
        }
        Poco::JSON::Object responseObj;
        responseObj.set("dadosEstoque", arrayEstoque);
        responseObj.set("dadosFornecedor", arrayFornecedor);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, ostr);
    } catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}