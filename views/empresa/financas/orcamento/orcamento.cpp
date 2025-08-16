#include "orcamento.hpp"


OrcamentoViews::OrcamentoViews() {}


void OrcamentoViews::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET){

    }else if(request.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST){

    }else{
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED);
        response.send();
    }
}


void OrcamentoViews::Post(Poco::Net::HTTPServerRequest& resquet, Poco::Net::HTTPServerResponse& response){
    try{
        std::string body;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(resquet.stream());
        Poco::JSON::Object::Ptr objeto = result.extract<Poco::JSON::Object::Ptr>();

        std::string nome = objeto->getValue<std::string>("");
        std::string preco = objeto->getValue<std::string>("");
        std::string status = objeto->getValue<std::string>("");
        std::string descricao = objeto->getValue<std::string>("");

        time_t tempoAtual = time(0);
        tm* dataHora = localtime(&tempoAtual);
        char data[80];
        strftime(data, sizeof(data), "%d/%m/%Y", dataHora);
        std::string dataLancamento = data;

        if(nome.empty() || preco.empty() || status.empty() || descricao.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Todos os campos são obrigatórios\"}";
            return;
        }
        if( dataLancamento.empty()){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("application/json");
            response.send() << "{\"error\": \"Erro no servidor\"}";
            return;
        }

    }catch(const std::exception& e){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("application/json");
        response.send() << "{\"error\": \"" << e.what() << "\"}";
    }
}


void OrcamentoViews::Get(Poco::Net::HTTPServerResponse& response){
    try{
        response.setContentType("application/json");
        FinancasModel financasModel;
        std::vector<DadosOrcamento> dadosOrcamento = financasModel.BuscandoOrcamento();
        Poco::JSON::Array array;
        for (const auto& dados : dadosOrcamento){
            Poco::JSON::Object objeto;
            objeto.set("id", dados.id);
            objeto.set("nome", dados.nome_orcamento);
            objeto.set("preco", dados.preco);
            objeto.set("status", dados.status);
            objeto.set("datapedido", dados.datapedido);
            objeto.set("descricao", dados.descricao);
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