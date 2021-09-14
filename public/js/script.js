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
}
function manaul() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/manaul");
    xhr.send()
}
function getAutoStatus() {
    fetch("http://" + RPI_IP + "/auto_status")
        .then(response => response.json())
        .then(data => console.log(data));
}