const HttpClientMetrics = require("./httpClientMetrics");
const HttpClient = require("./httpClient");
const ApiClient = require("./apiClient");
const Gas = require("./gas");
const Wheel = require("./wheel");
const KeepAlive = require("./keepAlive");
const WindowHandler = require("./windowHandler");

window.onload = () => {
    let httpClient = new HttpClient();

    let apiClient = new ApiClient();
    apiClient.init(httpClient);

    // let httpClientMetrics = new HttpClientMetrics();
    // httpClientMetrics.init(httpClient);

    // let apiClient = new ApiClient();
    // apiClient.init(httpClientMetrics);

    new WindowHandler().init();
    new KeepAlive().init(apiClient);
    new Gas().init(apiClient);
    new Wheel().init(apiClient);
}