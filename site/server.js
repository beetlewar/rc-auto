const path = require("path");

var connect = require('connect');
var serveStatic = require('serve-static');
connect().use(serveStatic(path.resolve(__dirname, "bin"))).listen(8080, function(){
    console.log('Server running on 8080...');
});