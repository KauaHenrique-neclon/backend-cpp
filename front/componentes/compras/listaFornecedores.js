import React, { useEffect, useState } from 'react'
import '../styles/compras/listaFornecedores.css'

const ListaFornecedores = () => {

    const [dadosFornecedores, setDadosFornecedores] = useState('');

    useEffect(() => {
        const fetchFornecedores = async () => {
            try{
                const response = await fetch('');
                if(!response.ok){
                    throw new Error('Erro ao buscar publicações');
                }
                const data = await response.json();
                setDadosFornecedores(data.fornecedores || [] );
            }catch(error){
                console.log("Erro ao request");
            }
        }
        fetchFornecedores();
    }, []);

  return (
    <div className="lista-fornecedores">
        {dadosFornecedores.length === 0 ? (
            <p>Sem dados sobre fornecedores</p>
        ) : (
        dadosFornecedores.map(dados => (
            <div key={dados.id} className="card-fornecedores">
                <h2>{dados.nome}</h2>
                <p>Endereço: {dados.endereco}</p>
                <p>Telefone: {dados.telefone}</p>
                <p>Email: {dados.email}</p>
            </div>
           ))
        )}
    </div>
  )
}

export default ListaFornecedores;