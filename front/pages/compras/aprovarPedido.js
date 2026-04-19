import React, { useState, useEffect } from 'react';
import '../../styles/compras/aprovarPedido.css';

const AprovarPedido = () => {
    const [dadosPedidosAprovar, setDadosPedidosAprovar] = useState([]);
    const [error, setError] = useState(null);
    const [loading, setLoading] = useState(true);
    const [abertoId, setAbertoId] = useState(null);

    const [pedidoSelecionado, setPedidoSelecionado] = useState(null);
    const [status, setStatus] = useState('');
    const [resposta, setResposta] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    useEffect(() => {
        const fetchPedidos = async () => {
            try {
                const response = await fetch(`${apiUrl}/aprovarPedido`, {
                    method: 'GET',
                    credentials: 'include',
                });
                if (!response.ok) {
                    throw new Error('Erro ao buscar dados');
                }
                const data = await response.json();
                setDadosPedidosAprovar(data.dadosPedido || []);
            } catch (err) {
                setError(err.message);
            } finally {
                setLoading(false);
            }
        };

        fetchPedidos();
    }, [apiUrl]);


    const toggleCard = (id) => {
        setAbertoId(abertoId === id ? null : id);
        setPedidoSelecionado(id);
    };


    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await fetch(`${apiUrl}/pedidos`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    idPedido: pedidoSelecionado,
                    status: status,
                }),
            });
            const data = await response.json();
            if (response.ok) {
                setResposta(data);
                setError(null);
            } else {
                setError(data.error || 'Erro ao enviar');
            }
        } catch (err) {
            setError('Erro de conexão com o servidor');
        }
    };

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;


    return (
        <div className="aprovar-pedido-all">
            <h1>Aprovação de Pedidos</h1>
            {dadosPedidosAprovar.length === 0 ? (
                <p>Sem pedidos disponíveis</p>
            ) : (
                dadosPedidosAprovar.map((pedido) => (
                    <div key={pedido.id} className="card-pedido" onClick={() => toggleCard(pedido.id)}>
                        <h2>{pedido.item}</h2>
                        {abertoId === pedido.id && (
                            <div className="detalhes-pedido">
                                <p><strong>Status:</strong> {pedido.status}</p>
                                <p><strong>Produto:</strong> {pedido.idproduto}</p>
                                <p><strong>Fornecedor:</strong> {pedido.idfornecedor}</p>
                                <p><strong>Data:</strong> {pedido.datapedido}</p>
                                <select value={status} onChange={(e) => setStatus(e.target.value)} >
                                    <option value="">Selecione</option>
                                    <option value="negado">Negado</option>
                                    <option value="aprovada">Aprovada</option>
                                </select>
                                <button onClick={handleSubmit}>Enviar</button>
                            </div>
                        )}
                    </div>
                ))
            )}
        </div>
    );
};

export default AprovarPedido;