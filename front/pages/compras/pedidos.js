import React, { useEffect, useState } from 'react'

const Pedidos = () => {
  const [dadosFornecedor, setDadosFornecedor] = useState('');
  const [error, setError] = useState(null);

  const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

  useEffect(() => {
    const fetchDadosPedidos = async () => {
      try{
        const response = await fetch(`${apiUrl}/estoque`, {
          method: 'GET',
          credentials: 'include',
        });
        if(!response.ok){
          throw new Error('Erro ao buscar dados para o pedido');
        }
        const data = await response.json();
        setDadosFornecedor(data.dadosFornecedor || []);
      }catch(error){
        setError(error.message);
        console.log(Error);
      }
    };
    fetchDadosPedidos();
  }, [apiUrl]);

  if (loading) return <p>Carregando...</p>;
  if (error) return <p>Erro: {error}</p>;

  return (
    <div className="Pedidos-all">
      <h1>Pedidos de Produtos</h1>
      
    </div>
  )
}

export default Pedidos;