const form = document.getElementById("login");

form.addEventListener('submit', function(event) {
  event.preventDefault(); // Evita que se envíe el formulario de forma predeterminada
  
  const name = form.elements['username'].value;
  const email = form.elements['password'].value;
  
  if (name && email) { // Verifica si los campos del formulario están completos
    window.location.href = 'form_solicitar_vacaciones.html'; // Redirige a otra página
  } else {
    alert('Por favor complete todos los campos'); // Muestra una alerta si el formulario no está completo
  }
});

