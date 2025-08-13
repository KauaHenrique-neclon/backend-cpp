import React, { useState } from 'react'
import '../../styles/componentes/empresa/entradaPonto.css'

const EntradaPonto = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    const [formDataEntrada, setFormDataEntrada] = useState({
        cpfusuario: '',
        tipo: 'entrada',
    });

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
                console.log('Ponto cadastrado com sucesso');
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
        <button>Cadastrar Entrada</button>
        </form>
    </div>
  )
}

export default EntradaPonto;