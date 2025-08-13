import React, { useState } from 'react'
import '../../styles/componentes/empresa/entradaPonto.css'

const EntradaPonto = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    const [formDataEntrada, setFormDataEntrada] = useState({
        cpfusuario: '',
        tipo: 'entrada',
    });

    const [dadosOkEnvio, setdadosOkEnvio] = useState(null);
    const [error, setError] = useState(null);


    const handeleChange = (e) =>{

        const {name, value} = e.target;
        setFormDataEntrada({
            ...formDataEntrada,
            [name]:  value,
        });
    }

    const handeleSubmit = async (e) =>{
        e.preventDefault();
        try{
            const response = await fetch(`${apiUrl}/`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDataEntrada),
            });
            if(response.ok){
                const data = await response.json();
                setdadosOkEnvio(data);
                setError(null);
                console.log('Ponto cadastrado com sucesso', data);
            }else{
                const errorData = await response.json();
                console.error('Erro ao cadastrar ponto:', errorData);
            }
        }catch(error){
            const errorData = await response.json();
            console.error('Erro ao cadastrar ponto:', errorData);
        }
    }

  return (
    <div className='entradaPontoJs'>
        <h1>Entrada Ponto</h1>
        <form onSubmit={handeleSubmit}>
        <div className='baterPontoEntrada'>
            <label>Digite seu CPF</label>
            <input 
               type="number"
               name="cpfusuario"
               id="cpfusuario"
               value={formDataEntrada.cpfusuario}
               onChange={handeleChange}
               required
            />
        </div>
        <button type="submit">Cadastrar Entrada</button>
        </form>
        {dadosOkEnvio && (
            <div>
                <h1>Ponto cadastrado com sucesso!</h1>
                {formDataEntrada}
            </div>
        )}
        {error && (
            <div>
                <h1>Erro ao cadastrar ponto:</h1>
                <p>{error}</p>
            </div>
        )}
    </div>
  )
}

export default EntradaPonto;