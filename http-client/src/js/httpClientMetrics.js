module.exports = class HttpClientMetrics {
    init(httpClient) {
        this.httpClient = httpClient;
    }

    putAsync(uri, content, onDone) {
        var startTime = new Date().getTime();

        this.httpClient.putAsync(uri, content, code => {
            var endTime = new Date().getTime();

            var duration = endTime - startTime;

            console.debug(duration);

            onDone();

            this.postMetrics(duration, uri, content, code);
        })
    }

    postMetrics(duration, uri, content, statusCode) {
        var metricsContent = `{
    "duration": ${duration},
    "uri": "${uri}",
    "content": "${content}",
    "code": ${statusCode}
}`;

        var request = new XMLHttpRequest();
        request.open("POST", "http://192.168.1.100:9000/api/metrics", true);
        request.setRequestHeader("Content-Type", "application/json");
        request.send(metricsContent);
    }
}