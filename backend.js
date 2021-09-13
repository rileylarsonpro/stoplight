// Require express and define app object
const express = require('express')
const fs = require('fs')
    let app = express()
    let cors = require('cors')
// Get files from public folder     
app.use(express.static(__dirname + '/public'))
// Allow use of JSON and cors
app.use(express.json())
app.use(cors())
// Start up on port 8080 
const server = app.listen(8080, () => {
    console.log("Started server on port 8080")
})

// Random number function
function getRandInt(max) {
    return Math.floor( Math.random() * Math.floor(max))
}
// [GET] /joke endpoint
app.get('/joke', cors(), (req,res) => {
        let file = JSON.parse(fs.readFileSync(__dirname + '/jokes.json'))
        let error = { "error": "There are no jokes :("}
        console.log(file)
        if (file.length == 0) {
            console.log("made it")
            res.status(404).send(JSON.stringify(error))
        }
        else {
            let jokeToReturn = file[getRandInt(file.length)]
            res.send(jokeToReturn)
        }
})

// [POST] /joke endpoint
app.post('/joke', cors(), (req,res) => {
    // Get request body
    let reqBody = req.body
    // Get current jokes in file
    let file = JSON.parse(fs.readFileSync(__dirname + '/jokes.json'))
    // Add new joke to the end
    file.push(reqBody)
    // Write new data to file 
    fs.writeFileSync(__dirname + '/jokes.json', JSON.stringify(file))
    // Send confirmation 
    let response = { message: "Added a Joke to the Bank"}
    res.status(200).send(response)
}