const path = require("path");

module.exports = {
    entry: "./js/main.js",
    output: {
        filename: "bundle.js",
        path: path.resolve(__dirname, "bundle")
    },
    // resolve: {
    //     extensions: ["", ".js"]
    // },
    module: {
        loaders: [
            {
                test: /\.js?$/,
                loader: "babel-loader",
                exclude: /node_modules/,
                // query: {
                //     cacheDirectory: true,
                //     presets: ["es2015"]
                // }
            }
        ]
    }
};