const FULL_GAS_TOUCH_MOVE = 150;

module.exports = class Gas {
    constructor() {
        this.dragY = 0;
        this.gasValue = 0;
        this.puttingGas = false;
        this.gasPressed = false;
        this.gasValueOnServer = 0;
    }

    init() {
        this.gasElement = document.getElementById("gas");

        this.gasElement.ondragstart = this.ondragstart;
        this.gasElement.ontouchstart = e => { alert("click!") };
        this.gasElement.ontouchmove = this.ontouchmove;
        this.gasElement.ontouchend = this.ontouchend;

        this.updateGasTable();
    }

    updateGasTable() {
        var table = document.getElementById("gasTable");

        table.style.visibility = this.gasPressed ? "visible" : "hidden";

        var numVisibleCells = table.rows.length * this.gasValue;

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

    ondragstart() {
        return false;
    }

    ontouchstart(e) {
        gasPressed = true;

        var touch = this.findGasTouch(e.touches);

        dragY = touch.clientY;

        gasValue = 0;

        updateGasTable();

        this.showGas(true);

        e.preventDefault();

        return false;
    }

    findGasTouch(touches) {
        for (var i = 0; i < touches.length; i++) {
            if (touches[i].target == gasElement) {
                return touches[i];
            }
        }
        return null;
    }

    showGas(gasOn) {
        if (gasOn) {
            gasElement.classList.remove("gas-off");
        }
        else {
            gasElement.classList.add("gas-off");
        }
    }

    ontouchmove(e) {
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

    putGas(value) {
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

    ontouchend(e) {
        gasPressed = false;
        gasValue = 0;
        showGas(false);
        putGas();
        updateGasTable();

        e.preventDefault();

        return false;
    }
}