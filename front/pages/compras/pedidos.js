import React, { useEffect, useState } from 'react';
import '../../styles/compras/pedidos.css';


const Pedidos = () => {
  const [dadosFornecedor, setDadosFornecedor] = useState([]);
  const [dadosEstoque, setDadosEstoque] = useState([]);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(true);
  const [resposta, setResposta] = useState(null);

  const [formDataPedidos, setFormDataPedidos] = useState({
    idproduto: '',
    idfornecedor: '',
    dataPedido: '',
    statusPedidos: '',
    itemPedido: '',
    quantidade: '',
  });

  const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormDataPedidos({
      ...formDataPedidos,
      [name]: value,
    });
  };

  useEffect(() => {
    const fetchDadosPedidos = async () => {
      try {
        const response = await fetch(`${apiUrl}/pedidos`, {
          method: 'GET',
          credentials: 'include',
        });
        if (!response.ok) {
          throw new Error('Erro ao buscar dados');
        }
        const data = await response.json();
        setDadosFornecedor(data.dadosFornecedor || []);
        setDadosEstoque(data.dadosEstoque || []);
      } catch (error) {
        setError(error.message);
        console.log(error);
      } finally {
        setLoading(false);
      }
    };
    fetchDadosPedidos();
  }, [apiUrl]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await fetch(`${apiUrl}/pedidos`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formDataPedidos),
      });
      const data = await response.json();
      if (response.ok) {
        setResposta(data);
        setError(null);
      } else {
        setError(data.error || 'Erro ao enviar');
        setResposta(null);
      }
    } catch (error) {
      setError('Erro de conexão com o servidor');
      setResposta(null);
    }
  };

  if (loading) return <p>Carregando...</p>;
  if (error) return <p>Erro: {error}</p>;

  return (
    <div className="Pedidos-all">
      <h1>Pedidos de Compras</h1>
      <form onSubmit={handleSubmit}>
        <select name="idproduto" value={formDataPedidos.idproduto} onChange={handleChange}>
          <option value="">Selecione um produto</option>
          {dadosEstoque.map((produto) => (
            <option key={produto.id} value={produto.id}>
              {produto.nome}
            </option>
          ))}
        </select>
        <select name="idfornecedor" value={formDataPedidos.idfornecedor} onChange={handleChange}>
          <option value="">Selecione o fornecedor</option>
          {dadosFornecedor.map((fornecedor) => (
            <option key={fornecedor.id} value={fornecedor.id}>
              {fornecedor.nome}
            </option>
          ))}
        </select>
        <input type="date" name="dataPedido" value={formDataPedidos.dataPedido} onChange={handleChange} />
        <input type="text" name="itemPedido" placeholder="Item do pedido" value={formDataPedidos.itemPedido} onChange={handleChange} />
        <input type="number" name="quantidade" placeholder="Quantidade" value={formDataPedidos.quantidade} onChange={handleChange} />
        <button type="submit">Cadastrar Pedido</button>
      </form>
      {resposta && <p>{resposta.message}</p>}
    </div>
  );
};

export default Pedidos;