var wheel = document.getElementById("wheel");

pressed = false;
x = 0;
rotation = 0;

function releaseWheel() {
    pressed = false;
}

function putRotation() {
    var rotationContent = "rotation=" + rotation;
    console.info("putting rotation: " + rotationContent);

    var request = new XMLHttpRequest();
    request.open("PUT", "/api/rotation", true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(rotationContent);
}

function dragWheel(mouseX) {
    if (!pressed) {
        pressed = true;
        x = mouseX;
    }
}

function rotateWheel(mouseX) {
    if (pressed) {
        var dx = mouseX - x;
        x = mouseX;

        var dRot = dx * 0.01;
        rotation = Math.max(-1, Math.min(rotation + dRot, 1));

        var rotationDeg = rotation * 180;
        wheel.style.transform = "rotate(" + rotationDeg + "deg)";

        putRotation();
    }
}

wheel.ondragstart = () => {
    return false;
}

wheel.onmousedown = e => {
    dragWheel(e.pageX);
}

wheel.onmousemove = e => {
    rotateWheel(e.pageX);
}

wheel.ontouchstart = e => {
    dragWheel(e.touches[0].pageX);
    e.preventDefault();
}

wheel.ontouchmove = e => {
    rotateWheel(e.touches[0].pageX);
    e.preventDefault();
}

wheel.ontouchend = () => {
    releaseWheel();
}