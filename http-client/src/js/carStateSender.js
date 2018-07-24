module.exports = class CarStateSender {
    init(httpClient, carState) {
        this.httpClient = httpClient;
        this.carState = carState;
    }

    start() {
        setTimeout(
            () => {
                let me = this;
                let content = "gas=" + this.carState.getGas() + "&wheel=" + this.carState.getWheel();
                this.httpClient.post("/api/state", content, () => me.start());
            }, 100);
    }
}