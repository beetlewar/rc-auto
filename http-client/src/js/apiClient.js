module.exports = class ApiClient {
    init(httpClient) {
        this.gasValue = 0;
        this.gasValueOnServer = 0;
        this.puttingGas = false;

        this.wheelValue = 0;
        this.wheelValueOnServer = 0;
        this.puttingWheel = false;

        this.puttingKeepAlive = false;

        this.httpClient = httpClient;
    }

    sendGas(value) {
        this.gasValue = value;

        if (this.puttingGas) {
            console.info("already putting gas");
            return;
        }

        if (this.gasValue == this.gasValueOnServer) {
            console.info("same gas");
            return;
        }

        this.puttingGas = true;

        var gasContent = "gas=" + value;

        this.httpClient.putAsync("/api/gas", gasContent, code => {
            this.gasValueOnServer = value;

            this.puttingGas = false;

            if (this.gasValue != this.gasValueOnServer) {
                this.sendGas(this.gasValue);
            }
        });
    }

    sendWheel(value) {
        this.wheelValue = value;

        if (this.puttingWheel) {
            console.info("already putting wheel");
            return;
        }

        if (this.wheelValue == this.wheelValueOnServer) {
            console.info("same wheel");
            return;
        }

        this.puttingWheel = true;

        var wheelContent = "wheel=" + value;

        this.httpClient.putAsync("/api/wheel", wheelContent, code => {
            this.wheelValueOnServer = value;

            this.puttingWheel = false;

            if (this.wheelValue != this.wheelValueOnServer) {
                this.sendWheel(this.wheelValue);
            }
        });
    }

    sendKeepAlive() {
        if (this.puttingKeepAlive) {
            console.info("already putting keepAlive");
            return;
        }

        this.puttingKeepAlive = true;

        this.httpClient.putAsync("/api/keepAlive", "", code => this.puttingKeepAlive = false);
    }
}