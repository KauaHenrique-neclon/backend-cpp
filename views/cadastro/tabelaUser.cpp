#include "tabelaUser.hpp"



void TabelaUserView::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    
    //cookieMiddleware.cookieMiddleware(request, response);

     
    response.set("Access-Control-Allow-Origin", "http://localhost:3000");
    response.set("Access-Control-Allow-Credentials", "true");
    response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response.set("Access-Control-Allow-Headers", "Content-Type");

    if(request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        return;
    }
    else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET){
        Get(response);
    } else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void TabelaUserView::Get(Poco::Net::HTTPServerResponse& response){
    try{
        /*
        if(!sessao.IsAuthenticated()) {

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Acesso Negado\"}";
            return;
        }*/

        response.setContentType("application/json");
        ModelCadastrar modelCadastrar;
        std::vector<Cadastro> dadosCadastro = modelCadastrar.BuscandoCadastro();

        for (const auto& cadastro : dadosCadastro) {
            std::cout << "ID: " << cadastro.id
                    << "Nome: " << cadastro.nome
                    << "Email: " << cadastro.email
                    << std::endl;
        }

        Poco::JSON::Array array;
        
        for (const auto& cadastro : dadosCadastro) {
            Poco::JSON::Object obj;
            obj.set("id", cadastro.id);
            obj.set("nome", cadastro.nome);
            obj.set("dataNascimento", cadastro.dataNascimento);
            obj.set("email", cadastro.email);
            obj.set("cidade", cadastro.cidade);
            array.add(obj);
        }

        Poco::JSON::Object responseObj;
        responseObj.set("dados", array);
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, ostr);
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}