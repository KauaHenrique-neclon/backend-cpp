"use client";
import React, { useEffect, useState } from 'react'
import '../../styles/home/home.css';
import Dashboard from '../../componentes/home/dashboard';
import MenuLateral from '../../componentes/home/menu';


const HomePage = () => {
  const [dadosDoHome, setDadosHome] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const apiUrl = process.env.NEXT_PUBLIC_BASE_URL;

  useEffect(() => {
    const fetchDadosHome = async () => {
      try{
        const response = await fetch(`${apiUrl}/home`, {
          method: 'GET',
          credentials: 'include',
        })
        if(!response.ok){
          throw new Error('Erro ao buscar dados do home');
        }
        const data = await response.json();
        console.log(data);
        setDadosHome(data.dados || []);
      }catch(error){
        setError(error.message);
        console.log(Error);
      }finally {
        setLoading(false);
      }
    };
    fetchDadosHome();
  }, [apiUrl]);

  if (loading) return <p>Carregando...</p>;
  if (error) return <p>Erro: {error}</p>;

  return (
    <div className="home-all">
      <div>
        <MenuLateral />
      </div>
      <div>
        <Dashboard />
      </div>
    </div>
  )
}

export default HomePage;