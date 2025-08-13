import React from 'react'
//import '../../styles/home/dashboard.css'
import '../../styles/home/dash.css'
import Link from 'next/link'

const Dashboard = () => {
  return (
    <div className="Dashboard">
        <span>
            <p>Total de item no estoque</p>
            <p>300</p>
            <Link href="/estoque/estoque">Ir para Esotque</Link>
        </span>
        <span>
            <p>Total de pessoas cadastradas</p>
            <p>400</p>
            <Link href="/cadastrar">Ir Tabela</Link>
        </span>
        <span>
            <p>Total de Pedidos ativos</p>
            <p>30</p>
            <Link href="/compras/pedidos">Ver Pedidos</Link>
        </span>
        <span>
            <p>Total de fornecedores</p>
           <p>90</p>
           <Link href="/compras/fornecedores">Ver Fornecedores</Link>
        </span>
    </div>
  )
}

export default Dashboard;