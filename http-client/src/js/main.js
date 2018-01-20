const Gas = require("./gas");
const Wheel = require("./wheel");
const KeepAlive = require("./keepAlive");
const WindowHandler = require("./windowHandler");

window.onload = () => {
    new WindowHandler().init();
    new KeepAlive().init();
    new Gas().init();
    new Wheel().init();
}