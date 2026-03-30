INSERT INTO produtos (nome, descricao, codigo, unidademedida) VALUES
('Arroz', 'Arroz branco tipo 1', 1001, 'kg'),
('Feijao', 'Feijao carioca', 1002, 'kg'),
('Leite', 'Leite integral', 1003, 'litro'),
('Acucar', 'Acucar refinado', 1004, 'kg'),
('Cafe', 'Cafe torrado e moido', 1005, 'kg');


INSERT INTO estoque (idproduto, quantidade, localizacao, datavalidade) VALUES
(1, 100, 'Prateleira A1', '2026-12-31'),
(2, 80, 'Prateleira A2', '2026-10-15'),
(3, 50, 'Geladeira B1', '2026-04-20'),
(4, 120, 'Prateleira C1', '2027-01-10'),
(5, 60, 'Prateleira C2', '2026-08-05');

INSERT INTO movimentacoes (idproduto, tipomovimentacao, quantidade, datamovimentacao) VALUES
(1, 'ENTRADA', 100, '2026-03-01'),
(2, 'ENTRADA', 80, '2026-03-02'),
(3, 'ENTRADA', 50, '2026-03-03'),
(1, 'SAIDA', 20, '2026-03-10'),
(2, 'SAIDA', 10, '2026-03-12'),
(3, 'SAIDA', 5, '2026-03-15'),
(4, 'ENTRADA', 120, '2026-03-05'),
(5, 'ENTRADA', 60, '2026-03-06');