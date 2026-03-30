#include "login.hpp"


void LoginView::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
   
    response.set("Access-Control-Allow-Origin", "*");
    response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response.set("Access-Control-Allow-Headers", "Content-Type");

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.send();
        return;
    }
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
        Post(request, response);
    } else {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void LoginView::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        std::string email = object->getValue<std::string>("email");
        std::string password = object->getValue<std::string>("senha");

        Session sessao;
        if (sessao.Login(email, password)) {
            Usuario usuarioo = sessao.getUsuario();

            // cookie de sessao
            Poco::Net::HTTPCookie cookie("sessionId", "ALGUM_ID_UNICO");
            cookie.setPath("/");
            cookie.setHttpOnly(true);
            response.addCookie(cookie);

            // Resposta JSON
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("application/json");

            Poco::JSON::Object jsonResponse;
            jsonResponse.set("nome", usuarioo.nome);

            std::ostream& out = response.send();
            jsonResponse.stringify(out);

        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            Poco::JSON::Object error;
            error.set("error", "Invalid Username or Password");
            std::ostream& out = response.send();
            error.stringify(out);
        }

    } catch (const Poco::Exception& ex) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Erro ao processar JSON";
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