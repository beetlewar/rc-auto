const ApiClient = require("./apiClient");

// максимальный угол поворота руля
const MAX_ROTATION_ANGLE = 90;
// скорость возврата руля в нейтральное положение, градусов в секунду
const RETURN_ROTATION_TO_ZERO_SPEED = 180;

module.exports = class Wheel {
    init(apiClient) {
        this.apiClient = apiClient;
        this.pressed = false;
        this.dragAngle = 0;
        this.wheelRotationAngle = 0;

        this.wheelDocument = document.getElementById("wheel");
        this.wheelDocument.ondragstart = e => this.ondragstart(e);
        this.wheelDocument.ontouchstart = e => this.ontouchstart(e);
        this.wheelDocument.ontouchmove = e => this.ontouchmove(e);
        this.wheelDocument.ontouchend = e => this.ontouchend(e);
    }

    ondragstart(e) {
        return false;
    }

    ontouchstart(e) {
        this.pressed = true;

        var touch = this.findWheelTouch(e.touches);

        var angle = this.getWheelAngle(touch.clientX, touch.clientY);

        if (angle == NaN) {
            return;
        }

        this.dragAngle = angle;

        e.preventDefault();
    }

    findWheelTouch(touches) {
        for (var i = 0; i < touches.length; i++) {
            if (touches[i].target == this.wheelDocument) {
                return touches[i];
            }
        }

        return undefined;
    }

    getWheelAngle(screenX, screenY) {
        var wheelRect = this.wheelDocument.getBoundingClientRect();
        var wheelCenterX = wheelRect.left + wheelRect.width / 2;
        var wheelCenterY = wheelRect.top + wheelRect.height / 2;

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

    ontouchmove(e) {
        e.preventDefault();

        var touch = this.findWheelTouch(e.touches);

        var angle = this.getWheelAngle(touch.clientX, touch.clientY);

        if (angle == NaN) {
            return;
        }

        var a1 = angle - this.dragAngle;
        var a2 = 360 + angle - this.dragAngle;
        var a3 = angle - this.dragAngle - 360;

        if (Math.abs(a1) < Math.abs(a2) && Math.abs(a1) < Math.abs(a3)) {
            this.rotateWheel(a1);
        }
        else if (Math.abs(a2) < Math.abs(a3) && Math.abs(a2) < Math.abs(a1)) {
            this.rotateWheel(a2);
        }
        else {
            this.rotateWheel(a3);
        }

        this.dragAngle = angle;
    }

    rotateWheel(angle) {
        this.wheelRotationAngle = Math.min(MAX_ROTATION_ANGLE, Math.max(-MAX_ROTATION_ANGLE, this.wheelRotationAngle + angle));
        this.wheelDocument.style.transform = "rotate(" + this.wheelRotationAngle + "deg)";

        var wheelValue = this.wheelRotationAngle / MAX_ROTATION_ANGLE;

        // wheelValue = Math.round(wheelValue * 100) / 100;

        this.apiClient.sendWheel(wheelValue);
    }

    ontouchend() {
        this.pressed = false;
        this.animateReturnToZero(Date.now());
    }

    animateReturnToZero(prevTimeStamp) {
        setTimeout(() => {
            if (this.pressed) {
                return;
            }

            if (this.wheelRotationAngle == 0) {
                return;
            }

            var currentTime = Date.now();
            var elapsed = currentTime - prevTimeStamp;

            var angle = Math.min(Math.abs(this.wheelRotationAngle), RETURN_ROTATION_TO_ZERO_SPEED / elapsed);

            if (angle == 0) {
                return;
            }

            if (this.wheelRotationAngle > 0) {
                angle = -angle;
            }

            this.rotateWheel(angle);

            this.animateReturnToZero(currentTime);
        }, 20);
    }
}