var rotation = document.getElementById("rotation");

rotation.oninput = () => {
    var rotationContent = "rotation=" + rotation.value;
    console.info("putting rotation: " + rotationContent);

    var request = new XMLHttpRequest();
    request.open("PUT", "/api/rotation", true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(rotationContent);
}