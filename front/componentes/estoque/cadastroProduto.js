import React from 'react'
import '../../styles/componentes/estoque/cadastroProduto.css'

const CadastroProduto = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;
    
    const [formDataCadastro, setFormDataCadastro] = useState({
        nome: '',
        quantidade: '',
        tipo: '',
    });
    
    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormDataCadastro({
            ...formDataCadastro,
            [name]: value,
        });
    };
    
    const handleSubmit = async (e) => {
        e.preventDefault();
        try{
            const response = await fetch(`${apiUrl}/cadastrarProduto`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDataCadastro),
            });
            if(response.ok){
                const data = await response.json();
                console.log('Cadastrado produto com sucesso');
            }else{
                const errorData = await response.json();
                console.error('Erro ao cadastrar produto:', errorData);
            }
        }catch(error){
            console.error('Erro na requisição:', error);
        }
        console.log('Dados cadastrados:', formData);
    };
    
  return (
    <div className="cadastrarProduto">
        <nav>
            <Link>Estoque</Link>
            <h1>Cadastrar Produto</h1>
            <h1>Usuario</h1>
        </nav>
        <div className="box-cadastro">
          <form onSubmit={handleSubmit}>
            <label>Nome: </label>
            <input type="text" id="nome" name="nome" value={formDataCadastro.nome} onChange={handleChange} required />
            <label>Quantidade: </label>
            <input type="number" id="quantidade" name="quantidade" value={formDataCadastro.quantidade} onChange={handleChange} required />
            <label>Escolha o Tipo: </label>
            <select id="tipo" name="tipo" value={formDataCadastro.tipo} required >
                <option value="">selecione</option>
                <optin value="perigoso">Perigoso</optin>
                <optin value="livre">Livre</optin>
            </select>
            <button>Cadastrar Produto</button>
          </form>
        </div>
    </div>
  )
}

export default CadastroProduto;