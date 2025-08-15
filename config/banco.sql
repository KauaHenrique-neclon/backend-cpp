




CREATE TABLE frequencia (
    id SERIAL PRIMARY KEY,
    funcionario_id INTEGER,
    data DATE,
    hora_entrada TIME,
    hora_saida TIME,
    FOREIGN KEY (funcionario_id) REFERENCES funcionarios(id)
);

CREATE TABLE contas (
    id SERIAL PRIMARY KEY,
    nome_conta VARCHAR(50),
    tipo_conta VARCHAR(20),
    preco DECIMAL(10, 2),
    status VARCHAR(20);
    vancimento DATE;
    dia_lancamento DATE;
);

CREATE TABLE orcamento(
    id SERIAL PRIMARY KEY,
    nome_orcamento VARCHAR(50),
    preco DECIMAL(10, 2),
    status VARCHAR(20),
    datapedido DATE,
    descricao VARCHAR(256),
);