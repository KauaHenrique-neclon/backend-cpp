import React, { useState } from 'react'
import VerPonto from '../../componentes/empresa/verPonto';

const VisualizarPonto = () => {
    const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

    const [formCpfFuncionario, setFormCpfFuncionario] = useState({
        cpfusuario: '',
    })

    const [dadosFuncionario, setDadosFuncionario] = useState(null);

    const handeleChange = (e) =>{

        const {name, value} = e.target;
        setFormCpfFuncionario({
            ...formCpfFuncionario,
            [name]: value,
        });
    }

    const handeleSubmit = async (e) =>{
        e.preventDefault();
        try{
            const response = await fetch(`${apiUrl}/`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formCpfFuncionario),
            })
            if(response.ok){
               const data = await response.json();
               setDadosFuncionario(data);
               console.log('Dados do funcionário:', data);
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
        <h1>Visualizar Ponto de Funcionario</h1>
        <form>
        <div className="input-cpf-funcionario">
            <input 
               type="number"
               name="cpfusuario"
               id="cpfusuario"
               value={formDataEntrada.cpfusuario}
               onChange={handeleChange}
               required
            />
        </div>
        <button type="submit">Pesquisar</button>
        </form>
        {dadosFuncionario && <VerPonto dados={dadosFuncionario} />}
    </div>
  )
}

export default VisualizarPonto;