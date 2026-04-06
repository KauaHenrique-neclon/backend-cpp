import React, {useState, useEffect} from 'react'

const RemoverProduto = () => {
    const [dadosEstoque, setDadosRemover] = useState([]);
    const [idproduto, setIdProduto] = useState('');
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    
    const handleSubmit = async (idproduto) => {
        try{
            const response = await fetch(`${apiUrl}/removerProduto`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ id: idproduto }),
            });
            if(!response.ok){
                const errorData = await response.json();
                console.error('Erro ao remover produto:', errorData);
                return;
            }
            console.log('Produto removido com sucesso');
            setDadosRemover((prev) => prev.filter(p => p.id !== idproduto));
        }catch(error){
            console.error('Erro na requisição:', error);
        }
    };

    useEffect(() => {
        const fetcDadosRemover = async () => {
        try{
            const response = await fetch(`${apiUrl}/removerProduto`, {
                method: 'GET',
                credentials: 'include',
            });
            console.log(response);
            if(!response.ok){
                throw new Error('Erro ao buscar dados estoque');
            }
            const data = await response.json();
            setDadosRemover(data.dados || [] );
        }catch (error) {
            setError(error.message);
        } finally {
            setLoading(false);
        }
        };
        fetcDadosRemover();
    }, []);

  return (
    <div className="removerproduto">
        <div className="tabelaEstoque">
            <table>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Nome</th>
                        <th>Quantidade</th>
                        <th>Remover</th>
                    </tr>
                </thead>
                <tbody>
                    {dadosEstoque.length === 0 ? (
                        <tr>
                            <td colSpan={4}>Nenhum dado encontrado</td>
                        </tr>
                    ) : (
                        <>
                        {dadosEstoque.map((produto) => (
                            <tr key={produto.id}>
                                <td>{produto.id}</td>
                                <td>{produto.nome}</td>
                                <td>{produto.quantidade}</td>
                                <td>
                                    <button onClick={() => handleSubmit(produto.id)}>Remover</button>
                                </td>
                            </tr>
                        ))}
                    </>
                    )}
                </tbody>
            </table>
        </div>
    </div>
  )
}

export default RemoverProduto;