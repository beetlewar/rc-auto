const HttpClient = require("./httpClient");
const Gas = require("./gas");
const Wheel = require("./wheel");
const WindowHandler = require("./windowHandler");
const CarState = require("./carState");
const CarStateSender = require("./carStateSender");

window.onload = () => {
    let httpClient = new HttpClient();
    let carState = new CarState();
    let carStateSender = new CarStateSender();
    let gas = new Gas();
    let wheel = new Wheel()
    let windowHandler = new WindowHandler();

    windowHandler.init();
    carState.init();
    gas.init(carState);
    wheel.init(carState);
    carStateSender.init(httpClient, carState);

    carStateSender.start();
}