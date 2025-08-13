import React from 'react'

const EstoqueProduto = () => {

    const [dadosEstoque, setDadosEstoque] = useState([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);
    
    
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;
    
    useEffect(() => {
        const fetcDadosEstoque = async () => {
            try{
                const response = await fetch(`${apiUrl}/`);
                if(!response.ok){
                    throw new Error('Erro ao buscar dados estoque');
                }
                const data = await response.json();
                setDadosEstoque(data.dados || [] );
            }catch (error) {
                setError(error.message);
            } finally {
                setLoading(false);
            }
        };
        fetcDadosEstoque();
    }, []);
    
  return (
    <div className="tabelaEstoque">
        <table>
            <thead>
                <tr>
                    <th>Testeccc</th>
                    <th>Testeccc</th>
                    <th>Testeccc</th>
                    <th>Testeccc</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <th>Teste</th>
                    <th>Teste</th>
                    <th>Teste</th>
                    <th>Teste</th>
                </tr>
            </tbody>
        </table>
    </div>
  )
}

export default EstoqueProduto;