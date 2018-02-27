module.exports = class HttpClient {
    putAsync(uri, content, onDone) {
        console.debug("PUT: " + uri + ", content: " + content);

        var request = new XMLHttpRequest();
        request.onreadystatechange = () => {
            if (request.readyState == XMLHttpRequest.DONE) {
                onDone(request.status);
            }
        }

        request.open("PUT", uri, true);
        request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        request.withCredentials = true;
        request.send(content);
    }
}