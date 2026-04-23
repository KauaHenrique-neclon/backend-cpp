CREATE TABLE pedido (
    id SERIAL PRIMARY KEY,
    idproduto INT NOT NULL,
    idfornecedor INT NOT NULL,
    status VARCHAR(20) NOT NULL,
    motivo_cancelamento TEXT,
    datapedido DATE NOT NULL,
    CONSTRAINT fk_idproduto FOREIGN KEY (idproduto) REFERENCES produtos(id),
    CONSTRAINT fk_idfornecedor FOREIGN KEY (idfornecedor) REFERENCES fornecedores(id),
    CONSTRAINT chk_motivo_cancelamento
        CHECK (
            status <> 'CANCELADO'
            OR motivo_cancelamento IS NOT NULL
        )
);

INSERT INTO pedido (idproduto, idfornecedor, status, motivo_cancelamento, datapedido) VALUES
(1, 1, 'PENDENTE', NULL, '2026-01-10'),
(2, 2, 'ENVIADO', NULL, '2026-01-12'),
(3, 3, 'ENTREGUE', NULL, '2026-01-15'),
(4, 1, 'CANCELADO', 'Cliente desistiu', '2026-01-18'),
(5, 4, 'PENDENTE', NULL, '2026-01-20'),
(1, 2, 'ENTREGUE', NULL, '2026-02-01'),
(2, 3, 'ENVIADO', NULL, '2026-02-05'),
(3, 4, 'PENDENTE', NULL, '2026-02-08'),
(4, 2, 'ENTREGUE', NULL, '2026-02-10'),
(5, 1, 'CANCELADO', 'Produto indisponível', '2026-02-12'),
(1, 3, 'PENDENTE', NULL, '2026-03-01'),
(2, 4, 'ENTREGUE', NULL, '2026-03-03'),
(3, 1, 'ENVIADO', NULL, '2026-03-05'),
(4, 3, 'PENDENTE', NULL, '2026-03-07'),
(5, 2, 'ENTREGUE', NULL, '2026-03-10');

INSERT INTO pedido (idproduto, idfornecedor, status, motivo_cancelamento, datapedido) VALUES
(1, 1, 'ENVIADO', NULL, '2026-01-10'),
(2, 1, 'ENVIADO', NULL, '2026-01-12'),
(3, 2, 'ENVIADO', NULL, '2026-01-15'),
(4, 2, 'ENVIADO', NULL, '2026-01-18'),
(5, 3, 'ENVIADO', NULL, '2026-01-20'),
(1, 3, 'ENVIADO', NULL, '2026-02-01'),
(2, 4, 'ENVIADO', NULL, '2026-02-05'),
(3, 4, 'ENVIADO', NULL, '2026-02-08'),
(4, 1, 'ENVIADO', NULL, '2026-02-10'),
(5, 2, 'ENVIADO', NULL, '2026-02-15');




INSERT INTO pedido (idproduto, idfornecedor, status, motivo_cancelamento, datapedido) VALUES
(1, 1, 'APROVADA', NULL, '2026-01-10'),
(2, 2, 'APROVADA', NULL, '2026-01-12'),
(3, 3, 'APROVADA', NULL, '2026-01-15'),
(5, 4, 'APROVADA', NULL, '2026-01-20'),
(1, 2, 'APROVADA', NULL, '2026-02-01'),
(2, 3, 'APROVADA', NULL, '2026-02-05'),
(3, 4, 'APROVADA', NULL, '2026-02-08'),
(4, 2, 'APROVADA', NULL, '2026-02-10'),
(1, 3, 'APROVADA', NULL, '2026-03-01'),
(2, 4, 'APROVADA', NULL, '2026-03-03'),
(3, 1, 'APROVADA', NULL, '2026-03-05'),
(4, 3, 'APROVADA', NULL, '2026-03-07'),
(5, 2, 'APROVADA', NULL, '2026-03-10');