#include "login.hpp"


void LoginView::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    if (request.getMethod()  == Poco::Net::HTTPRequest::HTTP_POST) {
        Post(request, response);
    } else {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void LoginView::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    std::string body;
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(request.stream());
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

    std::string email = object->getValue<std::string>("email");
    std::string password = object->getValue<std::string>("password");

    LoginModel loginModel(email, password);

    if (loginModel.LoginUsuario()) {
        Usuario usuario = loginModel.getUsuario();
        std::cout << "Login bem-sucedido! Bem-vindo, " << usuario.nome << "." << std::endl;
    } else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
        response.setContentType("text/html");
        response.send() << "Invalid Username or Password";
    }
}

/*
void LoginView::Get(Poco::Net::HTTPServerResponse& response) {
    response.setContentType("text/html");

    std::ifstream file("templates/login.html");
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo login.html" << std::endl;
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
}*/