import React, { useState } from 'react'
import '../../styles/componentes/empresa/SaidaPonto.css'


const SaidaPonto = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    const [formDataSaida, setFormDataSaida] = useState({
        cpfusuarioSaida: '',
        tipo: 'saida',
    });

    const handeleChange = (e) =>{
        
        const {name,value} = e.target;
        setFormDataSaida({
            ...formDataSaida,
            [name]: value,
        });
    }

    const handeleSubmit = async (e) =>{
        e.preventDefault();
        try{
            const response = await fetch(`${apiUrl}/`,{
                method: 'POST',
                headers:{
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formDataSaida),
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
    <div>
        <h1>Saida Ponto</h1>
        <div>
            <label>Digite seu CPF</label>
            <input 
               type="number"
               name="cpfusuarioSaida"
               id="cpfusuarioSaida"
               value={formDataSaida.cpfusuarioSaida}
               onChange={handeleChange}
               required
            />
        </div>
        <button>Cadastrar Saida</button>
    </div>
  )
}

export default SaidaPonto;