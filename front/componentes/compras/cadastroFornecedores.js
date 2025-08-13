import React, { useState } from 'react'
import '../styles/compras/cadastroFornecedores.css'

const CadastroFornecedores = () => {

    const [formDados, SetFormDados] = useState({
        nome: '',
        endereco: '',
        telefone: '',
        email: '',
    });
    
    const handeleChange = (e) =>{
        const { name, value } = e.target;
        SetFormDados({
            ...formDados,
            [name]: value,
        });
    };

    const handeleSubmit = async (e) =>{
        e.preventDefault();

        try{
            const response = await fetch('',{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDados),
            })
            if(response.ok){
                const data = await response.json();
                console.log("Dados enviado para cadastrar fornecedor");
            }else{
                const data = await response.json();
                console.log("Fornecedor não cadastrado");
            }
        }catch (error){
            console.error('Erro na requisição:', error)
        }
    }

  return (
    <div className="cadastroFornecedores">
        <h1>Cadastrar Fornecedores</h1>
        <form onSubmit={handeleSubmit}>
        <div className="cadastroFornecedores-inputs">
            <labe>nome: </labe>
            <input type="text" id="nome" name="nome" value={formDados.nome} onChange={handeleChange} />
            <label>Endereço: </label>
            <input type="text" id="endereco" name="endereco" value={formDados.endereco} onChange={handeleChange} />
            <label>Telefone: </label>
            <input type="tel" id="telefone" name="telefone" value={formDados.telefone} onChange={handeleChange} />
            <label>Email: </label>
            <input type="email" id="email" name="email" value={formDados.email} onChange={handeleChange} />
        </div>
        <button type="submit">Cadastrar Fornecedor</button>
        </form>
    </div>
  )
}

export default CadastroFornecedores;