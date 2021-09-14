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
function toggleAuto() {
    console.log("toggle auto")
}