const Gas = require("./gas");
const Wheel = require("./wheel");
const WindowHandler = require("./windowHandler");

window.onload = () => {
    new WindowHandler().init();
    new Gas().init();
    new Wheel().init();
}