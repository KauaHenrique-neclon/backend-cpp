import React from 'react'

const VerPonto = ({dados}) => {
  return (
    <div className="totalPonto">
        <div>
            <h1>Nome: {dados.nome}</h1>
            <h1>Id: {dados.id}</h1>
            <h1>Data: {dados.data}</h1>
            <h1>Hora de Entrada: {dados.horaentrada}</h1>
            <h1>Hora Saida: {dados.horasaida}</h1>
        </div>
    </div>
  )
}

export default VerPonto;