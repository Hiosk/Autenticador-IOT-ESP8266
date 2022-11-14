const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
    res.send('Hello indústria 4.0!')
})

app.listen(port, () => {
    console.log(`Autenticador IOT ESP8266 listado na porta ${port}`)
})