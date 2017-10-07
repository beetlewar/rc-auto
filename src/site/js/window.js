window.addEventListener("contextmenu", function (e) { e.preventDefault(); return false; })

this.onmouseup = () => {
    releaseGas();
    releaseWheel();
}