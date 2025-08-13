#include "home.hpp"


void HomeClass::render(HTTPServerResponse& response) {
    if(session.IsAuthenticated()){
        response.setContentType("text/html");


        std::ifstream file("templates/home.html");
        if (!file) {
            std::cerr << "Erro ao abrir o arquivo home.html" << std::endl;
            response.setStatusAndReason(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.send().flush();
            return;
        }
    
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string templateStr = buffer.str();

        std::ostream& out = response.send();
        out << templateStr;
        out.flush();
    }else{
        std::cerr << "Acesso negado" << std::endl;
    }
}
