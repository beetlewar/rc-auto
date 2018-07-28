module.exports = class HttpClient {
    post(uri, content, onDone) {
        console.debug("POST: " + uri + ", content: " + content);

        var request = new XMLHttpRequest();
        request.onreadystatechange = () => {
            if (request.readyState == XMLHttpRequest.DONE) {
                onDone(request.status);
            }
        }

        request.open("POST", uri, true);
        request.setRequestHeader("Content-Type", "application/json");
        request.withCredentials = true;
        request.send(content);
    }
}