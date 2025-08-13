#include "verPonto.hpp"


void VerPontoViews::handleResquest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){

    }else if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){

    }else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}



void VerPontoViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        response.setContentType("application/json");
        ModelPonto modelponto;
        std::vector<DadosPonto> pegandoDadosPonto = modelponto.BuscandoDadosPontos();
        Poco::JSON::Array array;
        for (const auto& ponto : pegandoDadosPonto) {
            Poco::JSON::Object obj;
            obj.set("id", ponto.id);
            obj.set("funcionario_id", ponto.funcionario_id);
            obj.set("data", ponto.data);
            obj.set("horaentrada", ponto.horaentrada);
            obj.set("horasaida", ponto.horasaida);
            array.add(obj);
        }
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(array, ostr);
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}