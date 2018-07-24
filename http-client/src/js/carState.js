module.exports = class CarState {
    init() {
        this.gas = 0;
        this.wheel = 0;
    }

    getGas() { return this.gas; }
    getWheel() { return this.wheel; }

    setGas(gas) {
        if (gas < -1) {
            gas = -1;
        }
        else if (gas > 1) {
            gas = 1;
        }

        this.gas = gas;
    }

    setWheel(wheel) {
        if (wheel < -1) {
            wheel = -1;
        }
        else if (wheel > 1) {
            wheel = 1;
        }

        this.wheel = wheel;
    }
}
