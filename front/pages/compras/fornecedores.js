import React, { useState } from 'react';
import CadastroFornecedores from '../../componentes/compras/cadastroFornecedores';
import ListaFornecedores from '../../componentes/compras/listaFornecedores';
import '../../styles/compras/fornecedores.css'

const Fornecedores = () => {
  const [showCadastro, setShowCadastro] = useState(false);
  const [showLista, setShowLista] = useState(false);

  const handleCadastroClick = () => {
    setShowCadastro(true);
    setShowLista(false);
  };

  const handleListaClick = () => {
    setShowLista(true);
    setShowCadastro(false);
  };

  return (
    <div className="fornecedores">
      <nav>
        <button onClick={handleCadastroClick}>Cadastrar Fornecedores</button>
        <button onClick={handleListaClick}>Ver Fornecedores</button>
      </nav>
      {showCadastro && (
        <div className="janela-cadastro">
          <CadastroFornecedores />
        </div>
      )}
      {showLista && (
        <div className="janela-lista">
          <h2>Lista de Fornecedores</h2>
          < ListaFornecedores />
        </div>
      )}
    </div>
  );
};

export default Fornecedores;
