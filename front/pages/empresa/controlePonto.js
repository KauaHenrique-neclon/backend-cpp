import React, { useState } from 'react'
import '../../styles/empresa/ControlePonto.css'
import EntradaPonto from '../../componentes/empresa/entradaPonto';
import SaidaPonto from '../../componentes/empresa/saidaPonto';

const ControlePonto = () => {
    
    const [showEntrada, setShowEntrada] = useState(false);
    const [showSaida, setShowSaida] = useState(false);

    const handleEntradaClick = () =>{
        setShowEntrada(true);
        setShowSaida(false);
    }

    const handleSaidaClick = () =>{
        setShowSaida(true);
        setShowEntrada(false);
    }

  return (
    <div className='ControlePonto'>
        <h1>Bater Ponto</h1>
        <nav>
            <button onClick={handleEntradaClick}>Entrada</button>
            <button onClick={handleSaidaClick}>Saida</button>
        </nav>
        {showEntrada && (
            <div>
                <EntradaPonto />
            </div>
        )}
        {showSaida && (
            <div>
                <SaidaPonto />
            </div>
        )}
    </div>
  )
}

export default ControlePonto;