const FULL_GAS_TOUCH_MOVE = 150;

module.exports = class Gas {
    init() {
        this.dragY = 0;
        this.gasValue = 0;
        this.puttingGas = false;
        this.gasPressed = false;
        this.gasValueOnServer = 0;

        this.gasElement = document.getElementById("gas");

        this.gasElement.ondragstart = e => this.ondragstart(e);
        this.gasElement.ontouchstart = e => this.ontouchstart(e);
        this.gasElement.ontouchmove = e => this.ontouchmove(e);
        this.gasElement.ontouchend = e => this.ontouchend(e);

        this.updateGasTable();
    }

    isRowVisible(table, index) {
        var middle = table.rows.length / 2;

        var numVisibleCells = middle * Math.abs(this.gasValue);

        if (this.gasValue < 0) {
            if (index < middle) {
                return false;
            }
            else {
                var negativeIndex = index - middle;
                return negativeIndex < numVisibleCells;
            }
        }
        else {
            if (index >= middle) {
                return false;
            }
            else {
                var positiveIndex = middle - index - 1;
                return positiveIndex < numVisibleCells;
            }
        }

        return index % 2 == 0;
    }

    updateGasTable() {
        var table = document.getElementById("gasTable");

        table.style.visibility = this.gasPressed ? "visible" : "hidden";

        for (var i = 0; i < table.rows.length; i++) {
            var cell = table.rows[i].cells[0];
            if (this.isRowVisible(table, i)) {
                cell.classList.remove("transparent-cell");
            }
            else {
                cell.classList.add("transparent-cell");
            }
        }

        // for (var i = 0; i < table.rows.length; i++) {
        //     var rowIndex = table.rows.length - i - 1;

        //     var cell = table.rows[rowIndex].cells[0];
        //     if (i < numVisibleCells) {
        //         cell.classList.remove("transparent-cell");
        //     }
        //     else {
        //         cell.classList.add("transparent-cell");
        //     }
        // }
    }

    ondragstart(e) {
        return false;
    }

    ontouchstart(e) {
        this.gasPressed = true;

        var touch = this.findGasTouch(e.touches);

        this.dragY = touch.clientY;

        this.gasValue = 0;

        this.updateGasTable();

        this.showGas(true);

        e.preventDefault();

        return false;
    }

    findGasTouch(touches) {
        for (var i = 0; i < touches.length; i++) {
            if (touches[i].target == this.gasElement) {
                return touches[i];
            }
        }
        return null;
    }

    showGas(gasOn) {
        if (gasOn) {
            this.gasElement.classList.remove("gas-off");
        }
        else {
            this.gasElement.classList.add("gas-off");
        }
    }

    ontouchmove(e) {
        var touch = this.findGasTouch(e.touches);

        var dY = this.dragY - touch.clientY;

        this.dragY = touch.clientY;

        var dGas = dY / FULL_GAS_TOUCH_MOVE;

        this.gasValue = Math.max(-1, Math.min(1.0, this.gasValue + dGas));

        this.updateGasTable();

        this.putGas();

        e.preventDefault();

        return false;
    }

    putGas() {
        if (this.puttingGas) {
            console.log("putting gas");
            return;
        }
        if (this.gasValue == this.gasValueOnServer) {
            console.log("same gas");
            return;
        }

        this.puttingGas = true;

        var pendingGas = this.gasValue;
        var gasContent = "gas=" + pendingGas;
        console.info("putting gas: " + gasContent);

        var request = new XMLHttpRequest();
        request.onreadystatechange = () => {
            if (request.readyState == XMLHttpRequest.DONE) {
                this.gasValueOnServer = pendingGas;

                this.puttingGas = false;

                if (this.gasValue != this.gasValueOnServer) {
                    this.putGas();
                }
            }
        }

        request.open("PUT", "/api/gas", true);
        request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        request.send(gasContent);
    }

    ontouchend(e) {
        this.gasPressed = false;
        this.gasValue = 0;
        this.showGas(false);
        this.putGas();
        this.updateGasTable();

        e.preventDefault();

        return false;
    }
}