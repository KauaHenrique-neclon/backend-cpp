#include "contabilidade.hpp"


void ContabilidadeViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){
        Post(request, response);
    }else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void ContabilidadeViews::Post(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    try{
        std::string body;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr objeto = result.extract<Poco::JSON::Object::Ptr>();

        std::string nome_conta = objeto->getValue<std::string>("nomeConta");
        std::string tipoConta = objeto->getValue<std::string>("tipoConta");
        std::string preco = objeto->getValue<std::string>("valor");
        std::string status = objeto->getValue<std::string>("statusConta");
        std::string vencimento = objeto->getValue<std::string>("vencimento");

        time_t tempoAtual = time(0);
        tm* dataHora = localtime(&tempoAtual);
        char data[80];
        strftime(data, sizeof(data), "%d/%m/%Y", dataHora);
        float precoFloat = std::stof(preco);
       
        std::string dataLancamento = data;

        FinancasModel financasModel;
        DadosConta dadosConta;
        dadosConta.nome = nome_conta;
        dadosConta.tipo = tipoConta;
        dadosConta.preco = precoFloat;
        dadosConta.status = status;
        dadosConta.vencimento = vencimento;
        dadosConta.dia_lancamento = dataLancamento;

        bool resultado = financasModel.inserindoConta(dadosConta);
        if(resultado){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
            response.setContentType("application/json");
            response.send() << "{\"message\": \"Conta Regristada com sucesso.\"}";
        }else{
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro ao registrar conta no sistema\"}";
        }
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}



void ContabilidadeGetViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){
        Get(response);
    }else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}

void ContabilidadeGetViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        response.setContentType("application/json");
        FinancasModel financasModel;
        std::vector<DadosConta> dadosConta = financasModel.BuscandoContas();
        Poco::JSON::Array array;
        for (const auto& dados : dadosConta){
            Poco::JSON::Object objeto;
            objeto.set("id", dados.id);
            objeto.set("nome", dados.nome);
            objeto.set("tipo", dados.tipo);
            objeto.set("preco", dados.preco);
            objeto.set("status", dados.status);
            objeto.set("vencimento", dados.vencimento);
            objeto.set("dia_lancamento", dados.dia_lancamento);
            array.add(objeto);
        }
        std::ostream& ostr = response.send();
        Poco::JSON::Stringifier::stringify(array, ostr);
    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}