#include "controlePonto.hpp"


void ControleDePontoViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){
        Post(request, response);
    }
    else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void ControleDePontoViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        std::string body;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        std::string funcionario_id = object->getValue<std::string>("funcionario_id");
        std::string tipo = object->getValue<std::string>("tipo");

        time_t tempoAtual = time(0);
        tm* dataHora = localtime(&tempoAtual);
        char data[80];
        strftime(data, sizeof(data), "%Y-%m-%d", dataHora);
        char horaEntrada[80];
        strftime(horaEntrada, sizeof(horaEntrada), "%H:%M:%S", dataHora);

        ModelPonto modelPonto;
        DadosPonto dadosPonto;
        dadosPonto.funcionario_id = funcionario_id;
        dadosPonto.data = data;
        dadosPonto.horaentrada = horaEntrada;
        dadosPonto.tipo = tipo;

        bool resultado = modelPonto.inserindoPonto(dadosPonto);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Ponto registrado com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao registrar ponto\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}