create table fornecedores(
    id SERIAL PRIMARY KEY,
    nome varchar(256) not null,
    endereco varchar(256) not null,
    telefone varchar(20) not null,
    email varchar(256) not null
)


# inserindo dados no fornecedor
INSERT INTO fornecedores (nome, endereco, telefone, email) VALUES
('Fornecedor A', 'Rua das Flores, 123', '(27) 99999-1111', 'contato@fornecedora.com'),
('Fornecedor B', 'Av. Central, 456', '(27) 98888-2222', 'vendas@fornecedorb.com'),
('Fornecedor C', 'Rua do Comércio, 789', '(27) 97777-3333', 'suporte@fornecedorc.com'),
('Fornecedor D', 'Av. Brasil, 1010', '(27) 96666-4444', 'email@fornecedord.com');