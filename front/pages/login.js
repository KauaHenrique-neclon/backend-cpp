import React, { useState } from 'react'

const login = () => {

  const [formDados, SetFormDados] = useState({
    email: '',
    senha:'',
  });

  const handleChange = (e) => {

    const { name , value } = e.target;
    SetFormDados({
      ...formDados,
      [name]: value ,
    });
  };

  const handeleSubmit = async (e) => {
    e.preventDefault();

    try{
      const response = await fetch('http://localhost:8080/login',{
        method:'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(formDados),
      })
      if(response.ok){
        const data = await response.json();
        console.log('cadastrado com sucesso');
      }else{
        const errorData = await response.json();
        console.error('Erro ao longar', errorData);
      }
    }catch(error){
      console.error('Erro na requisição:', error)
    }

  }

  return (
    <div className='login-all'>
      <h1>Login Usuario</h1>
      <form onSubmit={handeleSubmit}>
        <div className='inputs-tudo'>
          <label>Email</label>
          <input 
              type="text"
              id="email" 
              name="email" 
              value={formDados.email}
              onChange={handleChange} 
          required />
          <label>Senha</label>
          <input 
              type="password" 
              id="password" 
              name="passwrod" 
              value={formDados.senha} 
              onChange={handleChange} 
          required />
        </div>
        <div className="buttonSubmit">
          <button type="submit">Entrar</button>
        </div>
      </form>
    </div>
  )
}

export default login;