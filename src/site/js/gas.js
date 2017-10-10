var gasElement = document.getElementById("gas");

dragY = 0;
gasValue = 0;
puttingGas = false;
gasPressed = false;
gasValueOnServer = 0;

const FULL_GAS_TOUCH_MOVE = 150;

updateGasTable();

function updateGasTable() {
    var table = document.getElementById("gasTable");

    table.style.visibility = gasPressed ? "visible" : "hidden";

    var numVisibleCells = table.rows.length * gasValue;

    for (var i = 0; i < table.rows.length; i++) {
        var rowIndex = table.rows.length - i - 1;

        var cell = table.rows[rowIndex].cells[0];
        if (i < numVisibleCells) {
            cell.classList.remove("transparent-cell");
        }
        else {
            cell.classList.add("transparent-cell");
        }
    }
}

gasElement.ondragstart = () => {
    return false;
}

gasElement.ontouchstart = e => {
    gasPressed = true;

    var touch = findGasTouch(e.touches);

    dragY = touch.clientY;

    gasValue = 0;

    updateGasTable();

    showGas(true);

    e.preventDefault();

    return false;
}

function findGasTouch(touches) {
    for (var i = 0; i < touches.length; i++) {
        if (touches[i].target == gasElement) {
            return touches[i];
        }
    }
    return null;
}

function showGas(gasOn) {
    if (gasOn) {
        gasElement.classList.remove("gas-off");
    }
    else {
        gasElement.classList.add("gas-off");
    }
}

gasElement.ontouchmove = e => {
    var touch = findGasTouch(e.touches);

    var dY = dragY - touch.clientY;

    dragY = touch.clientY;

    var dGas = dY / FULL_GAS_TOUCH_MOVE;

    gasValue = Math.max(0, Math.min(1.0, gasValue + dGas));

    updateGasTable();

    putGas();

    e.preventDefault();

    return false;
}

function putGas(value) {
    if (puttingGas) {
        console.log("putting gas");
        return;
    }
    if (gasValue == gasValueOnServer) {
        console.log("same gas");
        return;
    }

    puttingGas = true;

    var pendingGas = gasValue;
    var gasContent = "gas=" + pendingGas;
    console.info("putting gas: " + gasContent);

    var request = new XMLHttpRequest();
    request.onreadystatechange = () => {
        if (request.readyState == XMLHttpRequest.DONE) {
            gasValueOnServer = pendingGas;

            puttingGas = false;

            putGas();
        }
    }

    request.open("PUT", "/api/gas", true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(gasContent);
}

gasElement.ontouchend = e => {
    gasPressed = false;
    gasValue = 0;
    showGas(false);
    putGas();
    updateGasTable();

    e.preventDefault();

    return false;
}