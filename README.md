## Backend em C++ utilizando Poco e React Nextjs no Frontend

#### Servidor HTTP com Poco em C++ Descrição

Projeto de servidor HTTP escrito em C++ usando o framework Poco.
Implementa várias rotas HTTP que renderizam views específicas, com checagem de autenticação via sessão e cookies.
Suporta páginas como login, cadastro, estoque, fornecedores, pedidos, controle de ponto e contabilidade.
utiliza um padrão de Factory para criar handlers com base no caminho da requisição.
Principais componentes

#### Pasta com Views do Projeto

    HomePage, LoginPage, CadastrarPage, CadastrarProdutoPage, EstoquePage, 
    FornecedoresPage, PedidosPage, ControleDePontoPage, ContabilidadePage: 
    classes de manipuladores de requisição (HTTPRequestHandler).

    responsáveis por responder às rotas correspondentes.
    Session (sessao.hpp) e Cookie (cookie.hpp): gerenciamento de 
    autenticação/sessão do usuário.

    Views (home, login, cadastrar, estoque, fornecedores, pedidos, 
    funcionarios, controle de ponto, contabilidade): componentes que renderizam
    as páginas para cada rota. MyRequestHandlerFactory: fabrica os manipuladores 
    com base no caminho da URL.

    MyServer: servidor HTTP configurado com porta 9980 e diretório base de 
    recursos estáticos.
    Dependências: Poco Net, Poco Util, Poco Foundation; também PQXX (para PostgreSQL) 
    - conforme o link com -lpqxx e -lpq no final do README de build.
    Compilação: g++ *.cpp -o server -lPocoNet -lPocoUtil -lPocoFoundation -lpqxx -lpq
    Arquitetura básica

### Sobre o server
    Um servidor HTTP criado com Poco::Net que escuta na porta 9980.
    Um factory (MyRequestHandlerFactory) decide qual page handler criar
    com base no path da URL.

    Cada handler verifica a sessão (sessao.IsAuthenticated()) via cookie, 
    retornando HTTP 401 se não autenticado (A sessão não está ativa).

    Se autenticado, o handler invoca a view correspondente para renderizar a 
    resposta (ex.: HomeClass, LoginView, EstoqueViews, etc).


### Rotas suportadas

    / -> LoginPage
    /cadastrar -> CadastrarPage
    /home -> HomePage
    /cadastrarProduto -> CadastrarProdutoPage
    /Estoque -> EstoquePage
    /Fornecedores -> FornecedoresPage
    /pedidos -> PedidosPage
    /Contabilidade -> ContabilidadePage


### Notas de implementação

A autenticação é verificada dentro de alguns handlers (CadastrarProdutoPage, EstoquePage, FornecedoresPage, ControleDePontoPage, ContabilidadePage) usando Session e Cookie.
Tratamento de erros: alguns handlers capturam std::exception e retornam HTTP 500 com mensagem de erro interno do servidor.
O servidor usa um diretório base para recursos estáticos: C:\backend cpp\static (no Windows). Pode ajustar o caminho base no código.
Como compilar

Exemplo de comando: g++ *.cpp -o server -lPocoNet -lPocoUtil -lPocoFoundation -lpqxx -lpq
Certifique-se de que as dependências do Poco estejam instaladas e o PQXX (para PostgreSQL) esteja disponível se o projeto usar banco de dados.
Ajuste caminhos de include conforme sua estrutura de diretórios, se necessário.
Como rodar

Execute o binário gerado (server): ./server
O servidor ficará ativo na porta 9980. Acessos via navegador ou cliente HTTP para as rotas acima.

## Projeto Não Finalizado

Não vou finalizar esse projeto por problemas pessoais, mas ele está bem adiantado
estou bem cansado para terminar ele.