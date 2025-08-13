import React from 'react'
import '../../styles/home/Rotas.css'
import Link from 'next/link'

const MenuLateral = () => {
  return (
      <nav className="navbar">
          <Link href="/home">Home</Link>
          <Link href="/cadastrar">Cadastrar</Link>
          <Link href="/login">Login</Link>
          <Link href="/estoque/estoque">Estoque</Link>
          <Link href="/estoque/removerProduto">Remover Produto</Link>
      </nav>
  )
}

export default MenuLateral;