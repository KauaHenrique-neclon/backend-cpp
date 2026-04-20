


create table pedido(
    id SERIAL PRIMARY KEY,
    idproduto int not null,
    idfornecedor int not null,
    status varchar(20) not null,
    datapedido DATE not null,
    CONSTRAINT fk_idproduto FOREIGN KEY(idproduto) REFERENCES produtos(id),
    CONSTRAINT fk_idfornecedor FOREIGN KEY(idfornecedor) REFERENCES fornecedores(id)
);

INSERT INTO pedido (idproduto, idfornecedor, status, datapedido) VALUES
(1, 1, 'PENDENTE', '2026-01-10'),
(2, 2, 'ENVIADO', '2026-01-12'),
(3, 3, 'ENTREGUE', '2026-01-15'),
(4, 1, 'CANCELADO', '2026-01-18'),
(5, 4, 'PENDENTE', '2026-01-20'),
(1, 2, 'ENTREGUE', '2026-02-01'),
(2, 3, 'ENVIADO', '2026-02-05'),
(3, 4, 'PENDENTE', '2026-02-08'),
(4, 2, 'ENTREGUE', '2026-02-10'),
(5, 1, 'CANCELADO', '2026-02-12'),
(1, 3, 'PENDENTE', '2026-03-01'),
(2, 4, 'ENTREGUE', '2026-03-03'),
(3, 1, 'ENVIADO', '2026-03-05'),
(4, 3, 'PENDENTE', '2026-03-07'),
(5, 2, 'ENTREGUE', '2026-03-10');