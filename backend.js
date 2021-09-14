// Require express and define app object
const express = require('express')
let app = express()
let cors = require('cors')

let auto = false

// Get files from public folder     
app.use(express.static(__dirname + '/public'))

// Allow use of JSON and cors
app.use(express.json())
app.use(cors())


// Start up on port 8080 
const server = app.listen(8080, () => {
    console.log("Started server on port 8080")
})

// Next few lines adapted from https://www.w3schools.com/nodejs/nodejs_raspberrypi_blinking_led.asp
var Gpio = require('onoff').Gpio; //include onoff to interact with the GPIO
var RED_LED = new Gpio(17, 'out'); //use GPIO pin 4, and specify that it is output
var YELLOW_LED = new Gpio(27, 'out'); //use GPIO pin 4, and specify that it is output
var GREEN_LED = new Gpio(22, 'out'); //use GPIO pin 4, and specify that it is output

// [GET] /color_on endpoints
app.get('/red_on', cors(), (req,res) => {
    if (RED_LED.readSync() === 0) { //check the pin state, if the state is 0 (or off)
        RED_LED.writeSync(1); //set pin state to 1 (turn LED on)

        YELLOW_LED.writeSync(0); //set other two to off
        GREEN_LED.writeSync(0);
      } else {
        RED_LED.writeSync(0); 
    }
    res.status(200).send()
})

app.get('/yellow_on', cors(), (req,res) => {
    if (YELLOW_LED.readSync() === 0) { 
        YELLOW_LED.writeSync(1); 

        RED_LED.writeSync(0); 
        GREEN_LED.writeSync(0);
      } else {
        YELLOW_LED.writeSync(0); 
    }
    res.status(200).send()
})

app.get('/green_on', cors(), (req,res) => {
    if (GREEN_LED.readSync() === 0) { 
        GREEN_LED.writeSync(1); 

        RED_LED.writeSync(0); 
        YELLOW_LED.writeSync(0); 
      } else {
        GREEN_LED.writeSync(0); 
    }
    res.status(200).send()
})

app.get('/all_off', cors(), (req,res) => {
    GREEN_LED.writeSync(0); 
    RED_LED.writeSync(0); 
    YELLOW_LED.writeSync(0); 

    res.status(200).send()
})
// Function from this SO Question: https://stackoverflow.com/questions/14249506/how-can-i-wait-in-node-js-javascript-l-need-to-pause-for-a-period-of-time
function sleep(ms) {
    return new Promise((resolve) => {
      setTimeout(resolve, ms);
    });
  }

app.get('/auto', cors(), async (req,res) => {
    GREEN_LED.writeSync(0); 
    RED_LED.writeSync(0); 
    YELLOW_LED.writeSync(0); 
    auto = !auto
    while (auto){
        RED_LED.writeSync(1); 
        await sleep(2000);
        RED_LED.writeSync(0); 
        YELLOW_LED.writeSync(1); 
        await sleep(2000);
        YELLOW_LED.writeSync(0); 
        GREEN_LED.writeSync(1); 
        await sleep(2000);
        GREEN_LED.writeSync(0); 
    }
   
    res.status(200).send()
})
