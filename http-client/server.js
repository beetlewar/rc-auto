const path = require("path");

var connect = require('connect');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');

defaultState = { engineForwardPower: "40", engineBackwardPower: "10" };
state = {};

Object.assign(state, defaultState);

connect()
    .use(bodyParser.urlencoded({ extended: false }))
    .use(serveStatic(path.resolve(__dirname, "bin")))
    .use("/api/settings/reset", (req, res) => {
        if (req.method == "POST") {
            console.log("Resetting state");

            Object.assign(state, defaultState);

            res.writeHead(200, { "Content-Type": "application/json" });
            let json = JSON.stringify(state);
            res.end(json);
        }
    })
    .use("/api/settings", (req, res) => {
        if (req.method == "GET") {
            let json = JSON.stringify(state);

            console.log("Returning state: " + json);

            res.writeHead(200, { "Content-Type": "application/json" });
            res.end(json);
        }
        else if (req.method == "POST") {
            let json = JSON.stringify(req.body);

            console.log("Applying state: " + json);

            Object.assign(state, req.body);
            res.writeHead(200);
            res.end();
        }
    })
    .use((req, res) => {
        console.log("method: " + req.method + ", url: " + req.url + ", body: " + JSON.stringify(req.body));
        res.end();
    })
    .listen(8080, function () {
        console.info('Server running on 8080...');
    });