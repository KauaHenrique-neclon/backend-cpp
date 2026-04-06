create table produtos(
    id SERIAL PRIMARY KEY,
	nome varchar(30) not null,
	descricao varchar(256) not null,
	codigo int not null,
	unidademedida varchar(20) not null,
	ativo boolean not null
);
create table estoque(
    id SERIAL PRIMARY KEY,
	idproduto int not null,
	quantidade int not null,
	localizacao varchar(256) not null,
	datavalidade DATE not null,
	CONSTRAINT fk_idproduto FOREIGN KEY(idproduto) REFERENCES produtos(id)
);
create table movimentacoes(
    id SERIAL PRIMARY KEY,
	idproduto int not null,
	tipomovimentacao varchar(50) not null,
	quantidade int not null,
	datamovimentacao DATE not null,
	CONSTRAINT fk_idproduto FOREIGN KEY(idproduto) REFERENCES produtos(id)
)