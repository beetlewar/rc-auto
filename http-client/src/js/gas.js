const FULL_GAS_TOUCH_MOVE = 100;

module.exports = class Gas {
    init(carState) {
        this.carState = carState;
        this.dragY = 0;
        this.gasPressed = false;
        this.gasValue = 0;

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
    }

    ondragstart(e) {
        return false;
    }

    ontouchstart(e) {
        this.gasPressed = true;

        var touch = this.findGasTouch(e.touches);

        this.dragY = touch.clientY;

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
        return undefined;
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

        this.carState.setGas(this.gasValue);

        this.updateGasTable();

        e.preventDefault();

        return false;
    }

    ontouchend(e) {
        this.gasPressed = false;
        this.gasValue = 0;

        this.carState.setGas(this.gasValue);
        
        this.showGas(false);
        this.updateGasTable();

        e.preventDefault();

        return false;
    }
}