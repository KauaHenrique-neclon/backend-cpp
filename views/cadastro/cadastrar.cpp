#include "cadastrar.hpp"

void CadastrarView::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
        Post(request, response);
    } else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
        Get(response);
    } else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }

}

void CadastrarView::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        if (!sessao.IsAuthenticated()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        std::string username = object->getValue<std::string>("username");
        std::string nome = object->getValue<std::string>("nome");
        std::string senha = object->getValue<std::string>("senha");
        std::string dataNascimento = object->getValue<std::string>("dataNascimento");
        std::string email = object->getValue<std::string>("email");
        std::string cidade = object->getValue<std::string>("cidade");

        if (username.empty() || nome.empty() || senha.empty() || dataNascimento.empty() || email.empty() || cidade.empty()) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        if (!Poco::RegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(email)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Email inválido\"}";
            return;
        }

        if(senha.length() < 8){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Senha muito pequena, Pelo menos 8 caracteres\"}";
            return;
        }


        ModelCadastrar modelCadastrar(username, nome, senha, dataNascimento, email, cidade);
        bool resultado = modelCadastrar.inserirDadosCadastro();
        if (resultado) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Usuário cadastrado com sucesso\"}";
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao cadastrar usuário\"}";
        }
    } catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}

/*
void CadastrarView::Get(Poco::Net::HTTPServerResponse& response){
    response.setContentType("text/html");
    std::ifstream file("templates/cadastrar.html");
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo cadastrar.html" << std::endl;
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.send().flush();
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string templateStr = buffer.str();

    // Enviar a resposta
    std::ostream& out = response.send();
    out << templateStr;
    out.flush();
}
*/