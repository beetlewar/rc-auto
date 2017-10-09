document.body.style.webkitTouchCallout = 'none';

document.addEventListener("touchmove", () => {
    return false;
});

window.addEventListener("contextmenu", e => {
    e.preventDefault();
    return false;
});