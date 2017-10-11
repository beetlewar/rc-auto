const path = require("path");
const CopyWebpackPlugin = require('copy-webpack-plugin');
const CleanWebpackPlugin = require('clean-webpack-plugin');

let buildPath = path.resolve(__dirname, "bin");

module.exports = {
    entry: "./src/js/main.js",
    output: {
        filename: "app.js",
        path: buildPath
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
        new CleanWebpackPlugin(buildPath),
        new CopyWebpackPlugin([
            { from: "src/images", to: "images" },
            { from: "src/Index.html" }
        ])
    ]
};