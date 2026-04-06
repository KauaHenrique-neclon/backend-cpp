import React, { useState } from 'react'
import "../styles/login/login.css"

const Login = () => {
  const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;
  const [resposta, setResposta] = useState(null);
  const [erro, setErro] = useState(null);

  const [formDados, setFormDados] = useState({
    email: '',
    senha: '',
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormDados({
      ...formDados,
      [name]: value,
    });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();

    try {
      const response = await fetch(`${apiUrl}/login`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(formDados),
      });

      const data = await response.json();
      if (response.ok) {
        setResposta(data);
        setErro(null);
      } else {
        setErro(data);
        setResposta(null);
      }
    } catch (error) {
      setErro({ mensagem: 'Erro de conexão com o servidor' });
      setResposta(null);
    }
  };

  return (
    <div className='login-all'>
      <h1>Login Usuario</h1>
      <form onSubmit={handleSubmit}>
        <div className='inputs-tudo'>
          <label>Email</label>
          <input 
            type="text"
            name="email" 
            value={formDados.email}
            onChange={handleChange} 
            required 
          />

          <label>Senha</label>
          <input 
            type="password" 
            name="senha" 
            value={formDados.senha} 
            onChange={handleChange} 
            required 
          />
        </div>

        <div className="buttonSubmit">
          <button type="submit">Entrar</button>
        </div>
      </form>
      {resposta && (
        <div style={{ color: 'green', marginTop: '10px' }}>
          <strong>Sucesso:</strong>
          <pre>{JSON.stringify(resposta, null, 2)}</pre>
        </div>
      )}
      {erro && (
        <div style={{ color: 'red', marginTop: '10px' }}>
          <strong>Erro:</strong>
          <pre>{JSON.stringify(erro, null, 2)}</pre>
        </div>
      )}
    </div>
  )
}

export default Login;