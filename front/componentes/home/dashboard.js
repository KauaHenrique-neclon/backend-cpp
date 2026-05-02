import React, {useEffect, useState } from 'react'
//import '../../styles/home/dashboard.css'
import '../../styles/home/dash.css'
import Link from 'next/link'

const Dashboard = () => {
    const [dadosDoHome, setDadosHome] = useState([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    useEffect(() => {
         const fetchDadosHome = async () => {
        try{
            const response = await fetch(`${apiUrl}/home`, {
                method: 'GET',
                credentials: 'include',
            })
            if(!response.ok){
                throw new Error('Erro ao buscar dados do home');
            }
            const data = await response.json();
            console.log(data);
            setDadosHome(data.dados?.[0] || {});
        }catch(error){
            setError(error.message);
            console.log(Error);
        }finally {
            setLoading(false);
        }
        };
       fetchDadosHome();
    }, [apiUrl]);

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;
  return (
    <div className="Dashboard">
        <span>
            <p>Total de item no estoque</p>
            <p>{dadosDoHome.totalItemEstoque}</p>
            <Link href="/estoque/estoque">Ir para Esotque</Link>
        </span>
        <span>
            <p>Total de pessoas cadastradas</p>
            <p>{dadosDoHome.totalPessoasCadastrada}</p>
            <Link href="user/tabelaUser">Ir Tabela</Link>
        </span>
        <span>
            <p>Total de Pedidos ativos</p>
            <p>{dadosDoHome.totalPedidosAtivos}</p>
            <Link href="/compras/aprovarPedido">Ver Pedidos</Link>
        </span>
        <span>
            <p>Total de fornecedores</p>
           <p>{dadosDoHome.totalFornecedores}</p>
           <Link href="/compras/fornecedores">Ver Fornecedores</Link>
        </span>
        <span>
            <p>Pontos de enteda e saida</p>
            <p>300</p>
            <Link href="/empresa/visualizarPonto">Ver Pontos</Link>
        </span>
        <span>
            <p>Total de Produtos</p>
            <p>{dadosDoHome.totalProdutos}</p>
            <h2>cadastrados</h2>
        </span>
    </div>
  )
}

export default Dashboard;