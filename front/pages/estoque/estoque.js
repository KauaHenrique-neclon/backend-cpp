//import Link from 'next/link';
import React, { useEffect, useState } from 'react'
import '../styles/estoque/estoque.css'
import CadastroProduto from '../../componentes/estoque/cadastroProduto';
import EstoqueProduto from '../../componentes/estoque/estoqueProduto';
import RemoverProduto from '../../componentes/estoque/remover';


const estoque = () => {
    const [showCadastro, setShowCadastro] = useState(false);
    const [showEstoque, setShowEstoque] = useState(false);
    const [showRemover, setShowRemover] = useState(flase);

    const handleCadastroClick = () =>{
        setShowCadastro(true);
        setShowEstoque(false);
        setShowRemover(false);
    }

    const handleEstoqueClick = () =>{
        setShowEstoque(true);
        setShowCadastro(false);
        setShowRemover(false);
    }
    
    const handleRemoverClick = () =>{
        setShowRemover(true);
        setShowEstoque(false);
        setShowCadastro(false);
    }
    
  return (
    <div className="all-Estoque">
        <nav>
            <button onClick={handleCadastroClick}>Cadastrar Produto</button>
            <button onClick={handleEstoqueClick}>Estoque</button>
            <button onClick={handleRemoverClick}>remover Produto</button>
        </nav>
        {showCadastro && (
            <div className="janela-cadastro">
                <CadastroProduto />
            </div>
        )}
        {showEstoque && (
            <div className="janela-estoque">
                <EstoqueProduto />
            </div>
        )}
        {showRemover && (
            <div className="janela-remover">
                <RemoverProduto />
            </div>
        )}
    </div>
  )
}

export default estoque;