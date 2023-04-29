const login = document.getElementById("login"); // get by id

if (login) {
  login.addEventListener('submit', function (event) {
    event.preventDefault(); // Avoid default shipment

    const name = login.elements['username'].value;
    const email = login.elements['password'].value;

    if (name && email) { // Check if exists
      window.location.href = 'pagina_principal.html'; // redirection
      //window.location.href = 'form_solicitar_vacaciones.html'; // Redirige a otra página
    } else {
      alert('Por favor complete todos los campos'); // 
    }
  });
}



/**
 * TO DO: Make a file only for button functions
 */

function regresar() {
  window.history.back();
}

function cancelar() {
  /** Nothing for now ;) */
}


