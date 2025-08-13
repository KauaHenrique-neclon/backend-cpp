import React from 'react'
import '../../styles/home/home.css';
import Dashboard from '../../componentes/home/dashboard';
import MenuLateral from '../../componentes/home/menu';


const HomePage = () => {
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