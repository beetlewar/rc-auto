module.exports = class CarStateSender {
    init(httpClient, carState) {
        this.httpClient = httpClient;
        this.carState = carState;
    }

    start() {
        setTimeout(
            () => {
                let me = this;

                let obj = {
                    gas: this.carState.getGas(),
                    wheel: this.carState.getWheel(),
                };

                let json = JSON.stringify(obj);

                this.httpClient.post("/api/state", json, () => me.start());
            }, 100);
    }
}