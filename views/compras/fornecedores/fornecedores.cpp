#include "fornecedores.hpp"

void FornecedoresViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
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

void FornecedoresViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        if(!sessao.IsAuthenticated()) {
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
        std::string endereco = object->getValue<std::string>("endereco");
        std::string telefone = object->getValue<std::string>("telefone");
        std::string email = object->getValue<std::string>("email");

        if(telefone.length() < 11 && telefone.length() > 11){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Telefone deve conter 11 numeros\"}";
            return;
        }
        if (!Poco::RegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(email)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Email inválido\"}";
            return;
        }

        if(nome.empty() || endereco.empty() || telefone.empty() || email.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return; 
        }
        ModelEstoque modelestoque;
        Fornecedor fornecedor;
        fornecedor.nome = nome;
        fornecedor.telefone = telefone;
        fornecedor.endereco = endereco;
        fornecedor.email = email;
        
        bool resultado = modelestoque.Fornecedores(fornecedor);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Fornecedor Cadastrado com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao cadastrar Fornecedores\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}


void FornecedoresViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        if(!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }
        ModelEstoque modelEstoque;
        std::vector<Fornecedor> dadosFornecedores = modelEstoque.BuscandoFornecedores();


        std::stringstream jsonData;
        jsonData << "[";
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
        jsonData << "]";
        response.send() << jsonData.str();
    }catch(std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}