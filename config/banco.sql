




CREATE TABLE frequencia (
    id INTEGER PRIMARY KEY,
    funcionario_id INTEGER,
    data DATE,
    hora_entrada TIME,
    hora_saida TIME,
    FOREIGN KEY (funcionario_id) REFERENCES funcionarios(id)
);