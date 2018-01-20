module.exports = class KeepAlive {
    init() {
        this.puttingKeepAlive = false;

        setInterval(() => {
            if (this.puttingKeepAlive) {
                console.log("still putting keepAlive...");
                return;
            }

            this.puttingKeepAlive = true;

            var request = new XMLHttpRequest();
            request.onreadystatechange = () => {
                if (request.readyState == XMLHttpRequest.DONE) {
                    this.puttingKeepAlive = false;
                }
            }

            request.open("PUT", "/api/keepAlive", true);
            request.send();
        }, 333);
    }

    sendKeepAlive(){
        
    }
}