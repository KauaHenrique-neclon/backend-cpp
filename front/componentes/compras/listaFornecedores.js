import React, { useEffect, useState } from 'react'
import '../../styles/compras/listaFornecedores.css'

const ListaFornecedores = () => {
    const [dadosFornecedores, setDadosFornecedores] = useState('');
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    useEffect(() => {
        const fetchFornecedores = async () => {
            try{
                const response = await fetch(`${apiUrl}/listaFornecedores`,{
                    method: 'GET',
                    credentials: 'include',
                });
                if(!response.ok){
                    throw new Error('Erro ao buscar fornecedores');
                }
                const data = await response.json();
                console.log(data);
                setDadosFornecedores(data.dados || [] );
            }catch(error){
                console.log("Erro ao request");
            }finally {
                setLoading(false);
            }
        }
        fetchFornecedores();
    }, [apiUrl]);

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;

  return (
    <div className="lista-fornecedores">
        {dadosFornecedores.length === 0 ? (
            <p>Sem dados sobre fornecedores</p>
        ) : (
        dadosFornecedores.map((fornecedor) => (
            <div key={fornecedor.id} className="card-fornecedores">
                <h2>{fornecedor.nome}</h2>
                <p>Endereço: {fornecedor.endereco}</p>
                <p>Telefone: {fornecedor.telefone}</p>
                <p>Email: {fornecedor.email}</p>
            </div>
           ))
        )}
    </div>
  )
}

export default ListaFornecedores;