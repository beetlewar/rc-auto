const path = require("path");
var CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
    entry: "./src/js/main.js",
    output: {
        filename: "app.js",
        path: path.resolve(__dirname, "bin")
    },
    module: {
        loaders: [
            {
                test: /\.js?$/,
                loader: "babel-loader",
                exclude: /node_modules/
            }
        ]
    },
    plugins: [
        new CopyWebpackPlugin([
            { from: "src/images", to: "images" },
            { from: "src/Index.html" }
        ])
    ]
};