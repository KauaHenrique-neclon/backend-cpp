import React, { useState, useEffect } from 'react';
import '../../styles/componentes/estoque/estoqueProduto.css';

const EstoqueProduto = () => {
  const [dadosEstoque, setDadosEstoque] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

  useEffect(() => {
    const fetchDadosEstoque = async () => {
      try {
        console.log(apiUrl);
        const response = await fetch(`${apiUrl}/Estoque`,{
            method: 'GET',
            credentials: 'include',
        });
        if (!response.ok) {
          throw new Error('Erro ao buscar dados estoque');
        }
        const data = await response.json();
        console.log(data);
        setDadosEstoque(data.dados || []);
      } catch (error) {
        setError(error.message);
        console.log(Error);
      } finally {
        setLoading(false);
      }
    };

    fetchDadosEstoque();
  }, [apiUrl]);

  if (loading) return <p>Carregando...</p>;
  if (error) return <p>Erro: {error}</p>;

  return (
    <div className="tabelaEstoque">
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Nome</th>
            <th>Código</th>
            <th>Unidade de medida</th>
          </tr>
        </thead>
        <tbody>
          {dadosEstoque.length === 0 ? (
            <tr>
              <td colSpan="4">Nenhuma mercadoria no estoque</td>
            </tr>
          ) : (
            dadosEstoque.map((estoque) => (
              <tr key={estoque.id}>
                <td>{estoque.id}</td>
                <td>{estoque.nome}</td>
                <td>{estoque.codigo}</td>
                <td>{estoque.unidademedida}</td>
              </tr>
            ))
          )}
        </tbody>
      </table>
    </div>
  );
};

export default EstoqueProduto;