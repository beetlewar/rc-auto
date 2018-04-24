const path = require("path");

var connect = require('connect');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');

connect()
    .use(bodyParser.urlencoded({ extended: false }))
    .use(serveStatic(path.resolve(__dirname, "bin")))
    .use((req, res) => {
        console.log("method: " + req.method + ", url: " + req.url + ", body: " + JSON.stringify(req.body));
        res.end();
    })
    .listen(8080, function () {
        console.info('Server running on 8080...');
    });