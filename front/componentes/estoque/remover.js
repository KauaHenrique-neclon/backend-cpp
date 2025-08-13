import React from 'react'

const RemoverProduto = () => {
    const [dadosEstoque, setDadosRemover] = useState([]);
    const [idproduto, setIdProduto] = useState('');
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    
    const handleSubmit = async (idproduto) => {
        e.preventDefault();

        const formDataId = new FormData();
        formDataId.append('idproduto',idproduto);
        try{
            const response = await fetch(`${apiUrl}/removerProduto`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDataId),
            })
            if(!response.ok){
                const errorData = await response.json();
                console.error('Erro ao cadastrar produto:', errorData);
            }
            const data = await response.json();
            console.log('Dados removido com sucesso');
        }catch  (error){
            console.error('Erro na requisição:', error);
        }
        console.log('Dados removido com sucesso.');
    }

    useEffect(() => {
        const fetcDadosRemover = async () => {
        try{
            const response = await fetch(`${apiUrl}/`);
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
                        <th>Tipo</th>
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
                                <td>{produto.nome}</td>
                                <td>{produto.quantidade}</td>
                                <td>{produto.tipo}</td>
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