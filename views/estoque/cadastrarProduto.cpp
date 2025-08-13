#include "cadastrarProduto.hpp"



void CadastrarProdutoView::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    cookieMiddleware.cookieMiddleware(request, response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        return; 
    }
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
        Post(request, response);
    }else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }

}

void CadastrarProdutoView::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }

        
        std::string body;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        std::string nome = object->getValue<std::string>("nome");
        std::string descricao = object->getValue<std::string>("descricao");
        std::string codigo = object->getValue<std::string>("codigo");
        std::string unidademedida = object->getValue<std::string>("unidade");

        // validar Dados
        if(nome.empty() || descricao.empty() || codigo.empty() || unidademedida.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        if(codigo.length() < 4){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Codigo precisa de pelo menso 4 digitos\"}";
            return;
        }
        ModelEstoque modelestoque;
        Produto produto;
        produto.nome = nome;
        produto.descricao = descricao;
        produto.codigo = codigo;
        produto.unidademedida = unidademedida;

        bool resultado = modelestoque.InserindoProduto(produto);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Produto Cadastrado com sucesso.\"}";
        } else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao cadastrar Produto\"}";
        }
    } catch (const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Erro ao cadastrar Produto." << e.what() << "\"}";
    }
}