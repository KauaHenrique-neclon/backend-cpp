import React, { useEffect, useState } from 'react';
import '../../../styles/compras/pedidosAceitos.css';


const PedidosAceitos = () => {
    const [dadosPedidoEspera, setDadosPedidoEspera] = useState([]);
    const [error, setError] = useState(null);
    const [loading, setLoading] = useState(true);

    const [abertoId, setAbertoId] = useState(null);
    const [pedidoSelecionado, setPedidoSelecionado] = useState(null);

    const [statusPorPedido, setStatusPorPedido] = useState({});
    const [motivoPorPedido, setMotivoPorPedido] = useState({});

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    useEffect(() => {
        const fetchPedidosReceber = async () => {
            try {
                const response = await fetch(`${apiUrl}/pedidosAceitos`, {
                    method: 'GET',
                    credentials: 'include',
                });
                if (!response.ok) {
                    throw new Error('Erro ao buscar dados');
                }
                const data = await response.json();
                console.log(data);
                setDadosPedidoEspera(data.dadosPedidoAceito || []);
            } catch (error) {
                setError(error.message);
            } finally {
                setLoading(false);
            }
        };

        fetchPedidosReceber();
    }, [apiUrl]);

    const toggleCard = (id) => {
        setAbertoId((prev) => (prev === id ? null : id));
        setPedidoSelecionado(id);
    };

    const handleStatusChange = (id, value) => {
        setStatusPorPedido({
            ...statusPorPedido,
            [id]: value
        });
        if (value !== 'CANCELADO') {
            setMotivoPorPedido({
                ...motivoPorPedido,
                [id]: ''
            });
        }
    };

    const handleSubmit = async (id, status) => {
        if (!status) {
            alert('Selecione um status');
            return;
        }

        if (status === 'CANCELADO' && !motivoPorPedido[id]) {
            alert('Informe o motivo do cancelamento');
            return;
        }
        const dadosEnviar = {
            idPedido: id,
            status,
            motivo: status === 'CANCELADO' ? motivoPorPedido[id] : null
        };
        try {
            const response = await fetch(`${apiUrl}/pedidosAceitos`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                credentials: 'include',
                body: JSON.stringify(dadosEnviar)
            });
            if (!response.ok) {
                throw new Error('Erro ao atualizar pedido');
            }
            alert('Pedido atualizado com sucesso');
            setDadosPedidoEspera((prev) =>
                prev.filter((pedido) => pedido.id !== id)
            );

        } catch (error) {
            alert(error.message);
        }
    };

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;

    return (
        <div className="receber-pedido">
            <div className="h1-title">
                <h1>Recebimento de Pedidos</h1>
            </div>

            <div className="card">
                {dadosPedidoEspera.length === 0 ? (
                    <p>Sem pedidos para receber</p>
                ) : (
                    dadosPedidoEspera.map((pedido) => (
                        <div key={pedido.id} className="card-pedido">
                            <h2 onClick={() => toggleCard(pedido.id)}>
                                {pedido.nomeProduto}
                            </h2>
                            {abertoId === pedido.id && (
                                <div className="detalhes-pedido">
                                    <p><strong>Status:</strong> {pedido.status}</p>
                                    <p><strong>Produto:</strong> {pedido.idProduto}</p>
                                    <p><strong>Fornecedor:</strong> {pedido.nomeForn}</p>
                                    <p><strong>Data:</strong> {pedido.datapedido}</p>
                                    <select value={statusPorPedido[pedido.id] || ''} onChange={(e) => handleStatusChange(pedido.id, e.target.value)}>
                                        <option value="">Selecione</option>
                                        <option value="CANCELADO">Cancelado</option>
                                        <option value="ENTREGUE">Entregue</option>
                                    </select>
                                    {statusPorPedido[pedido.id] === 'CANCELADO' && (
                                        <textarea
                                            placeholder="Informe o motivo do cancelamento"
                                            value={motivoPorPedido[pedido.id] || ''}
                                            onChange={(e) =>
                                                setMotivoPorPedido({
                                                    ...motivoPorPedido,
                                                    [pedido.id]: e.target.value
                                                })
                                            }
                                        />
                                    )}
                                    <button onClick={() =>handleSubmit(pedido.id, statusPorPedido[pedido.id])}>Enviar</button>
                                </div>
                            )}
                        </div>
                    ))
                )}
            </div>
        </div>
    );
};

export default PedidosAceitos;