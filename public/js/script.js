const RPI_IP = "10.4.9.190:8080"
function redClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/red_on");
}
function yellowClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/yello_on");
}
function greenClicked() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "http://" + RPI_IP + "/green_on");
}
function allOff() {
    console.log("all off")
}
function toggleAuto() {
    console.log("toggle auto")
}