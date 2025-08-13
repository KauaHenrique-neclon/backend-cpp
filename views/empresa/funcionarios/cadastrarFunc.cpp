#include "cadastrarFunc.hpp"

void CadastrarFuncionarioViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    cookieMiddleware.cookieMiddleware(request, response);
    // ele verifica se o cookie já enviou uma mensagem ou n
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        return;
    }
    if (request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    } 
    else if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST){
        Post(request, response);
    }
    else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void CadastrarFuncionarioViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        if(!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }
        response.setContentType("application/json");
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}


void CadastrarFuncionarioViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
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
        std::string cpf = object->getValue<std::string>("cpf");
        std::string email = object->getValue<std::string>("email");
        std::string dataNascimento = object->getValue<std::string>("datanascimento");
        std::string cidade = object->getValue<std::string>("cidade");
        std::string bairro = object->getValue<std::string>("bairro");
        
        ModelCadastrarFuncionario modelCadastrarFuncionaio;
        DadosFuncionario dadoFuncionario;
        dadoFuncionario.nome = nome;
        dadoFuncionario.cpf = cpf;
        dadoFuncionario.email = email;
        dadoFuncionario.dataNascimento = dataNascimento;
        dadoFuncionario.cidade = cidade;
        dadoFuncionario.bairro = bairro;

        bool resultado = modelCadastrarFuncionaio.inserindoFuncionario(dadoFuncionario);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Funcionario Cadastrado com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao cadastrar Funcionario\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"Erro ao cadastrar Funcionario." << e.what() << "\"}";
    }
}