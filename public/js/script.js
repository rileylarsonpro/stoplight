const RPI_IP = "10.4.9.190:8080"

function redClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/red_on");
    xhr.send()
}
function yellowClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/yellow_on");
    xhr.send()
}
function greenClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/green_on");
    xhr.send()
}
function allOff() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/all_off");
    xhr.send()
}
function auto() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/auto");
    xhr.send()
    document.getElementById("auto-btn").hidden = true;
    document.getElementById("manual-btn").hidden = false;
}
function manual() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/manual");
    xhr.send()
    document.getElementById("auto-btn").hidden = false;
    document.getElementById("manual-btn").hidden = true;
}
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