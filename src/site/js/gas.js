var gasEnabled = false;

var gas = document.getElementById("gas");

function putGas(value) {
    var gasContent = "gas=" + value;
    console.info("putting gas: " + gasContent);

    var request = new XMLHttpRequest();
    request.open("PUT", "/api/gas", true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(gasContent);
}

function showGas(gasOn) {
    if (gasOn) {
        gas.classList.remove("gas-off");
    }
    else {
        gas.classList.add("gas-off");
    }
}

function gasOn() {
    if (!gasEnabled) {
        showGas(true);
        putGas(1);
        gasEnabled = true;
    }
}

function releaseGas() {
    if (gasEnabled) {
        showGas(false);
        putGas(0);
        gasEnabled = false;
    }
}

gas.ondragstart = () => {
    return false;
}

gas.onmousedown = () => {
    gasOn();
}

gas.ontouchstart = e => {
    gasOn();
    e.preventDefault();
}

gas.ontouchend = () => {
    releaseGas();
}