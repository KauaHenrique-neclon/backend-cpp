


create table pedido(
    id SERIAL PRIMARY KEY,
    idproduto int not null,
    idfornecedor int not null,
    status varchar(20) not null,
    datapedido DATE not null,
    item varchar(256) not null,
    CONSTRAINT fk_idproduto FOREIGN KEY(idproduto) REFERENCES produtos(id),
    CONSTRAINT fk_idfornecedor FOREIGN KEY(idfornecedor) REFERENCES fornecedores(id)
);