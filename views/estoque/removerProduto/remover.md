#### Documentação do Remover

    class do Remover
        
        - Class RemoverProduto
                -- Public
                    - handleRequest()
                -- Private
                    - Get()
                    - Post


        handleRequest recebe o method do request, onde vai verificar se o method é do tipo Get ou Post, onde vai encaminhar uma das funções

#### Função Get()

    Ela retorna dados do banco de dados, onde busca dados do Produto para inserir na tabela pelo react

#### Função Post()

    Recebe Id do produto para desativar do banco de dados, onde na tabela, tem a coluna "ativo", onde tudo é true, e com id, ele muda essa coluna para false