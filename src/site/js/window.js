document.body.style.webkitTouchCallout = 'none';

document.addEventListener("touchmove", function (e) {
    e.preventDefault();
    return false;
});

window.addEventListener("contextmenu", function (e) {
    e.preventDefault();
    return false;
});


// document.documentElement.requestFullScreen();
//document.documentElement.webkitRequestFullScreen();
//document.documentElement.requestFullScreen();