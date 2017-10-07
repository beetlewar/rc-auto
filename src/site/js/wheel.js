var wheel = document.getElementById("wheel");

pressed = false;
dragAngle = 0;
wheelRotationAngle = 0;
puttingRotation = false;
wheelRotationOnServer = 0;

const MAX_ROTATION_ANGLE = 180;
const RETURN_ROTATION_TO_ZERO_SPEED = 180; // градусов в секунду

wheel.ondragstart = () => {
    return false;
}

wheel.ontouchstart = e => {
    e.preventDefault();

    pressed = true;

    var touch = findWheelTouch(e.touches);

    var angle = getWheelAngle(touch.clientX, touch.clientY);

    if (angle == NaN) {
        return;
    }

    dragAngle = angle;
}

function getWheelAngle(screenX, screenY) {
    var wheelRect = wheel.getBoundingClientRect();
    var wheelCenterX = wheelRect.left + wheelRect.width / 2;
    var wheelCenterY = wheelRect.top + wheel.height / 2;

    var dx = screenX - wheelCenterX;
    var dy = (screenY - wheelCenterY) * -1;

    if (dx == 0) {
        if (dy == 0) {
            return NaN;
        }

        if (dy > 0) {
            return 0;
        }

        return 180;
    }

    var angle = Math.atan(dx / dy) * 180 / Math.PI;

    if (dx < 0 && dy < 0) {
        return angle - 180;
    }

    if (dx > 0 && dy < 0) {
        return angle + 180;
    }

    return angle;
}

wheel.ontouchmove = e => {
    e.preventDefault();

    var touch = findWheelTouch(e.touches);

    var angle = getWheelAngle(touch.clientX, touch.clientY);

    if (angle == NaN) {
        return;
    }

    var a1 = angle - dragAngle;
    var a2 = 360 + angle - dragAngle;
    var a3 = angle - dragAngle - 360;

    if (Math.abs(a1) < Math.abs(a2) && Math.abs(a1) < Math.abs(a3)) {
        rotateWheel(a1);
    }
    else if (Math.abs(a2) < Math.abs(a3) && Math.abs(a2) < Math.abs(a1)) {
        rotateWheel(a2);
    }
    else {
        rotateWheel(a3);
    }

    dragAngle = angle;
}

function rotateWheel(angle) {
    wheelRotationAngle = Math.min(MAX_ROTATION_ANGLE, Math.max(-MAX_ROTATION_ANGLE, wheelRotationAngle + angle));
    wheel.style.transform = "rotate(" + wheelRotationAngle + "deg)";

    putWheel();
}

function putWheel() {
    if (puttingRotation) {
        console.log("putting rot");
        return;
    }
    if (wheelRotationOnServer == wheelRotationAngle) {
        console.log("same rot");
        return;
    }

    puttingRotation = true;

    var pendingWheelRotation = wheelRotationAngle;
    var wheelContent = "wheel=" + wheelRotationAngle / MAX_ROTATION_ANGLE;
    console.info("putting wheel: " + wheelContent);

    var request = new XMLHttpRequest();
    request.onreadystatechange = function () {
        if (request.readyState == XMLHttpRequest.DONE) {
            wheelRotationOnServer = pendingWheelRotation;

            puttingRotation = false;

            putWheel();
        }
    }

    request.open("PUT", "/api/wheel", true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(wheelContent);
}

wheel.ontouchend = () => {
    pressed = false;
}

function findWheelTouch(touches) {
    for (var i = 0; i < touches.length; i++) {
        if (touches[i].target == wheel) {
            return touches[i];
        }
    }
    return null;
}

setInterval(function () {
    if (pressed) {
        return;
    }

    var angle = Math.min(Math.abs(wheelRotationAngle), RETURN_ROTATION_TO_ZERO_SPEED / 20.0);

    if (angle == 0) {
        return;
    }

    if (wheelRotationAngle > 0) {
        angle = -angle;
    }

    rotateWheel(angle);
}, 20);