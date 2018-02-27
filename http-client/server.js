const path = require("path");

var connect = require('connect');
var serveStatic = require('serve-static');

connect()
    .use(serveStatic(path.resolve(__dirname, "bin")))
    .use((req, res) => res.end())     //stub /api requests
    .listen(8080, function () {
        console.info('Server running on 8080...');
    });