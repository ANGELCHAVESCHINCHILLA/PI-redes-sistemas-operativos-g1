const login = document.getElementById("login");

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


const realizarSolicitudBtn = document.getElementById('realizar-solicitud-btn'); // get by id
if (realizarSolicitudBtn) {
  realizarSolicitudBtn.addEventListener('click', function () {
    window.location.href = 'form_solicitar_vacaciones.html'; // redirect
  });
}



