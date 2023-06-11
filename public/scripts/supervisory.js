
document.getElementById("send-annotation").addEventListener("submit", function(event) {
    // event.preventDefault();

    // Obtener los valores de los campos
    const username = document.getElementById("username").value;
    const annotation = document.getElementById("annotation").value;

    if (username && annotation) {
        // TODO(future's david): when DB has a function to add an annotation, finish this :*
        alert("Enviado!")
    }
    document.getElementById("username").value = "";
    document.getElementById("anotacion").value = "";
});

document.getElementById("cancel").addEventListener("click",function(event) {
    console.log("asd");
    window.location.href = "/index.html";
});




