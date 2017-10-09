var gasElement = document.getElementById("gas");

dragY = 0;
gasValue = 0;
puttingGas = false;
gasValueOnServer = 0;

const FULL_GAS_TOUCH_MOVE = 70;
const MIN_GAS_HEIGHT = 60;
const MAX_GAS_HEIGHT = 70;
const MIN_ENGINE_VOLUME = 0.3;

updateGasTable();

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

function showGas(gasOn) {
    if (gasOn) {
        gasElement.classList.remove("gas-off");
    }
    else {
        gasElement.classList.add("gas-off");
    }
}

function updateGasTable() {
    var table = document.getElementById("gasTable");

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

function findGasTouch(touches) {
    for (var i = 0; i < touches.length; i++) {
        if (touches[i].target == gasElement) {
            return touches[i];
        }
    }
    return null;
}

function setGasHeight() {
    var height = MIN_GAS_HEIGHT + (MAX_GAS_HEIGHT - MIN_GAS_HEIGHT) * gasValue;

    gasElement.setAttribute("height", height + "%");
}

gasElement.ondragstart = () => {
    return false;
}

gasElement.ontouchstart = e => {
    var touch = findGasTouch(e.touches);

    dragY = touch.clientY;

    gasValue = 0;

    showGas(true);

    e.preventDefault();

    return false;
}

gasElement.ontouchmove = e => {
    var touch = findGasTouch(e.touches);

    var dY = dragY - touch.clientY;

    dragY = touch.clientY;

    var dGas = dY / FULL_GAS_TOUCH_MOVE;

    gasValue = Math.max(0, Math.min(1.0, gasValue + dGas));

    setGasHeight();

    updateGasTable();

    putGas();

    e.preventDefault();

    return false;
}

gasElement.ontouchend = e => {
    gasValue = 0;
    setGasHeight();
    showGas(false);
    putGas();
    updateGasTable();

    e.preventDefault();

    return false;
}