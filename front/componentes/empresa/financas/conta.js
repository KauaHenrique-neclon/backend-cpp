import React, { useState } from 'react'

const ContaInserir = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    const [formDataConta, setFormDataConta] = useState({
        nome: '',
        tipo: '',
        preco: '',
        status: '',
        vencimento: '',
        codigo: '',
    });

    const [dadosOkEnvio, setdadosOkEnvio] = useState(null);
    const [error, setError] = useState(null);


    const handeleChange = (e) =>{
        const {name, value} = e.target;
        setFormDataConta({
            ...formDataConta,
            [name]: value,
        });
    };

    const handeleSubmit = async (e) =>{
        e.preventDefault();
        try{
            const response = await fetch(`${apiUrl}/`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDataConta),
            });
            if(response.ok){
                const data = await response.json();
                setdadosOkEnvio(data);
                setError(null);
                console.log('Conta cadastrada com sucesso', data);
            }else{
                const errorData = await response.json();
                console.error('Erro ao cadastrar conta:', errorData);
            }
        }catch(error){
            const errorData = await response.json();
            console.error('Erro ao cadastrar ponto:', errorData);
        }
    };

  return (
    <div className="all-inserirConta">
        <h1>Inserir Conta</h1>
        <form>
        <div className="entrarConta">
            <label>Inserir Nome da Conta</label>
            <input 
               type="text"
               name="nome-conta"
               id="nome-conta"
               value={formDataConta.nome}
               onChange={handeleChange}
               required
            />
            <label>Inserir Tipo</label>
            <input 
               type="text"
               name="tipo-conta"
               id="tipo-conta"
               value={formDataConta.tipo}
               onChange={handeleChange}
               required
            />
            <label>Inserir Preço</label>
            <input 
               type="number"
               name="preco"
               id="preco"
               value={formDataConta.preco}
               onChange={handeleChange}
               required
            />
            <label>Status da conta</label>
            <select name="status" id="status" value={formDataConta.status} onChange={handeleChange}>
                <option value="paga">Paga</option>
                <option value="nao-paga">Não Paga</option>
            </select>
            <label>Vencimento</label>
            <input 
               type="date"
               name="vencimento"
               id="vencimento"
               value={formDataConta.vencimento}
               onChange={handeleChange}
               required
            />
            <input 
               type="number"
               name="codigo"
               id="codigo"
               value={formDataConta.codigo}
               onChange={handeleChange}
               required
            />
        </div>
        <button type="submit">Inserir Conta</button>
        </form>
        {dadosOkEnvio && (
            <div>
                <h1>Conta cadastrada com sucesso!</h1>
                {formDataConta}
            </div>
        )}
        {error && (
            <div>
                <h1>Erro ao cadastrar Conta:</h1>
                <p>{error}</p>
            </div>
        )}
    </div>
  )
}

export default ContaInserir;