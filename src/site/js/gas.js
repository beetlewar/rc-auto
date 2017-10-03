var gasEnabled = true;

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
    gasEnabled = gasOn;

    if (gasEnabled) {
        gas.classList.remove("gas-off");
    }
    else {
        gas.classList.add("gas-off");
    }
}

gas.ondragstart = () => {
    return false;
}

gas.onmousedown = () => {
    if (!gasEnabled) {
        putGas(1);
        showGas(true);
    }
}

this.onmouseup = () => {
    if (gasEnabled) {
        putGas(0);
        showGas(false);
    }
}