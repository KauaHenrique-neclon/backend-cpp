import React, { useState, useEffect } from 'react';
import '../../styles/compras/aprovarPedidoo.css';

const AprovarPedido = () => {
    const [dadosPedidosAprovar, setDadosPedidosAprovar] = useState([]);
    const [error, setError] = useState(null);
    const [loading, setLoading] = useState(true);

    const [abertoId, setAbertoId] = useState(null);
    const [pedidoSelecionado, setPedidoSelecionado] = useState(null);

    const [statusPorPedido, setStatusPorPedido] = useState({});

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
                setDadosPedidosAprovar(data.dadosPedidos || []);
            } catch (err) {
                setError(err.message);
            } finally {
                setLoading(false);
            }
        };

        fetchPedidos();
    }, [apiUrl]);

    const toggleCard = (id) => {
        setAbertoId((prev) => (prev === id ? null : id));
        setPedidoSelecionado(id);
    };

    const handleSubmit = async (idPedido, statusPedido) => {
        try {
            const response = await fetch(`${apiUrl}/aprovarPedido`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    idPedido,
                    status: statusPedido,
                }),
            });
            const data = await response.json();
            if (!response.ok) {
                setError(data.error || 'Erro ao enviar');
            } else {
                setError(null);
            }
        } catch (err) {
            setError('Erro de conexão com o servidor');
        }
    };

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;

    return (
        <div className="aprovar-pedido-all">
            <div className="h1-title">
                <h1>Aprovação de Pedidos</h1>
            </div>
            <div className="card">
                {dadosPedidosAprovar.length === 0 ? (
                    <p>Sem pedidos disponíveis</p>
                ) : (
                    dadosPedidosAprovar.map((pedido) => (
                        <div key={pedido.id} className="card-pedido">
                            <h2 onClick={() => toggleCard(pedido.id)}>
                                {pedido.nomeProduto}
                            </h2>
                            {abertoId === pedido.id && (
                                <div className="detalhes-pedido">
                                    <p><strong>Status:</strong> {pedido.status}</p>
                                    <p><strong>Produto:</strong> {pedido.idProduto}</p>
                                    <p><strong>Fornecedor:</strong> {pedido.idFornecedor}</p>
                                    <p><strong>Data:</strong> {pedido.datapedido}</p>

                                    <select value={statusPorPedido[pedido.id] || ''} onChange={(e) => setStatusPorPedido({
                                             ...statusPorPedido, [pedido.id]: e.target.value })}>
                                        <option value="">Selecione</option>
                                        <option value="negado">Negado</option>
                                        <option value="aprovada">Aprovada</option>
                                    </select>
                                    <button onClick={() => handleSubmit(pedido.id , statusPorPedido[pedido.id])}>
                                        Enviar
                                    </button>
                                </div>
                            )}
                        </div>
                    ))
                )}
            </div>
        </div>
    );
};

export default AprovarPedido;