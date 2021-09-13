// Require express and define app object
const express = require('express')
let app = express()
let cors = require('cors')

// Get files from public folder     
app.use(express.static(__dirname + '/public'))

// Allow use of JSON and cors
app.use(express.json())
app.use(cors())

// Next two lines from https://www.w3schools.com/nodejs/nodejs_raspberrypi_blinking_led.asp
var Gpio = require('onoff').Gpio; //include onoff to interact with the GPIO
var LED = new Gpio(11, 'out'); //use GPIO pin 4, and specify that it is output

// Start up on port 8080 
const server = app.listen(8080, () => {
    console.log("Started server on port 8080")
})
// [GET] /joke endpoint
app.get('/joke', cors(), (req,res) => {
    if (LED.readSync() === 0) { //check the pin state, if the state is 0 (or off)
        LED.writeSync(1); //set pin state to 1 (turn LED on)
      } else {
        LED.writeSync(0); //set pin state to 0 (turn LED off)
    }
    res.status(200).send()
})


// [POST] /joke endpoint
app.get('/', cors(), (req,res) => {
    res.status(200).send(response)
})