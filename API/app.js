const express = require('express')
const app = express()
const port = 3000

const db = require('./queries');

app.use(express.urlencoded({
    extended: true
}))

app.get('/', (req, res) => {
    res.send('Hi indústria 4.0')
})

app.post('/autenticar', (req, res) => {
    console.log(req.body)
    db.autenticar(req, res);
})

app.listen(port, () => {
    console.log(`Autenticador IOT ESP8266 listado na porta ${port}`)
})