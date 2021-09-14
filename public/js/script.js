const RPI_IP = "10.4.9.190:8080"

function redClicked() {
    manual()
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/red_on");
    xhr.send()
}
function yellowClicked() {
    manual()
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/yellow_on");
    xhr.send()
}
function greenClicked() {
    manual()
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/green_on");
    xhr.send()
}
function allOff() {
    manual()
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/all_off");
    xhr.send()
}
// Start auto mode and show manual button
function auto() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/auto");
    xhr.send()
    document.getElementById("auto-btn").hidden = true;
    document.getElementById("manual-btn").hidden = false;
}
// Show Automatic button
function manual() {
    document.getElementById("auto-btn").hidden = false;
    document.getElementById("manual-btn").hidden = true;
}
// Check if stoplight is in auto state
function getAutoStatus() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/auto_status");
    xhr.addEventListener("load", (e) => {
        // Handle the response
        const response = JSON.parse(e.target.responseText);
        response.status
        if (response.status) {// If in auto state
            document.getElementById("auto-btn").hidden = true;
            document.getElementById("manual-btn").hidden = false;
        }
        else {
            document.getElementById("auto-btn").hidden = false;
            document.getElementById("manual-btn").hidden = true;
        }
    })
    xhr.send()
}