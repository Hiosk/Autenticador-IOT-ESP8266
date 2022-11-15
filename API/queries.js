const Pool = require('pg').Pool
const pool = new Pool({
    user: 'auth_esp8266',
    host: '209.126.13.74',
    database: 'auth_esp8266',
    password: 'esp8266hsk0603',
    port: 5432,
})

const autenticar = (req, res) => {
    if(req.body.cpf.length == 12) {
        req.body.cpf = req.body.cpf.slice(0, -1)
    }
    const cpf = parseInt(req.body.cpf)
    const senha = parseInt(req.body.senha)

    pool.query('SELECT * FROM usuarios WHERE nu_cpf = $1 AND nu_senha = $2', [cpf, senha], (error, results) => {
        if (error) {
            throw error
        }
        if(results.rows.length > 0) {
            res.status(200).send(results.rows[0].nm_usuario)
        } else {
            res.status(200).send("Senha invalida")
        }
    })
}

const createUsuario = (req, res) => {
    const {
        cpf,
        senha
    } = req.body

    pool.query('INSERT INTO usuarios (nu_cpf, nu_senha) VALUES ($1, $2) RETURNING *', [cpf, senha], (error, results) => {
        if (error) {
            throw error
        }
        res.status(201).send(`User adicionado`)
    })
}

const deleteUsuario = (req, res) => {
    const cpf = parseInt(req.body.cpf)

    pool.query('DELETE FROM usuarios WHERE nu_cpf = $1', [cpf], (error, results) => {
        if (error) {
            throw error
        }
        res.status(200).send(`User deletado`)
    })
}

module.exports = {
    autenticar,
    createUsuario,
    deleteUsuario
}