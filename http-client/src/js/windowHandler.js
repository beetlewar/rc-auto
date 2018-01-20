module.exports = class WindowHandler {
    init() {
        document.body.style.webkitTouchCallout = 'none';

        document.addEventListener("touchmove", e => {
            e.preventDefault();
            return false;
        });

        window.addEventListener("contextmenu", e => {
            e.preventDefault();
            return false;
        });
    }
}