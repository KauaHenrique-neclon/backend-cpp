import React, {useEffect, useState} from 'react'

const tabelaUser = () => {
    const [dadosUsuarios, setDadosUsuarios] = useState([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    useEffect(() => {
        const fetchDadosUsuarios = async () => {
            try{
                const response = await fetch(`${apiUrl}/tabelaUser`, {
                    method: 'GET',
                    credentials: 'include',
                })
                if(!response.ok){
                     throw new Error('Erro ao buscar dados de usuarios');
                }
                const data = await response.json();
                setDadosUsuarios(data.dados || []);
            }catch(error) {
                setError(error.message);
                console.log(Error);
            }finally {
                setLoading(false);
            }
        };
        fetchDadosUsuarios();
    }, [apiUrl]);

    if (loading) return <p>Carregando...</p>;
    if (error) return <p>Erro: {error}</p>;


  return (
    <div className="tabela-user">
        <h1>Usuarios Cadastrados</h1>
        <table>
            <thead>
                <tr>
                    <th>Nome</th>
                    <th>Username</th>
                    <th>Data de Nascimento</th>
                    <th>Email</th>
                    <th>Cidade</th>
                </tr>
            </thead>
            <tbody>
                {dadosUsuarios.length === 0 ? (
                    <tr>
                        <td colSpan="4">Nenhum usuario achado</td>
                    </tr>
                ) : (
                    dadosUsuarios.map((user) => (
                        <tr key={user.id}>
                            <td>{user.nome}</td>
                            <td>{user.username}</td>
                            <td>{user.dataNascimento}</td>
                            <td>{user.email}</td>
                            <td>{user.cidade}</td>
                        </tr>
                    ))
                )}
            </tbody>
        </table>
    </div>
  )
}

export default tabelaUser;