const login = document.getElementById("login"); // get by id

if (login) {
  login.addEventListener('submit', function (event) {
    event.preventDefault(); // Avoid default shipment

    const name = login.elements['username'].value;
    const email = login.elements['password'].value;

    if (name && email) { // Check if exists
      window.location.href = 'index.html'; // redirection
      //window.location.href = 'form_solicitar_vacaciones.html'; // Redirige a otra página
    } else {
      alert('Por favor complete todos los campos'); // 
    }
  });
}


function populateRequestContainer() {
  // Get Container
  var requestContainer = document.getElementById("request-container");


  /**TODO: Read from filesystem what request have the employee reader.Then, from their
   * requests, craft the divs and populate them to the container. The actual implemention just
   * populate three static requests. The actual employee is Marta.
   */

  // Populate with Solicitudes' Div
  requestContainer.appendChild(createSolicitudDiv("Marta", "Constancia Salarial", "APROBADO"));
  requestContainer.appendChild(createSolicitudDiv("Marta", "Vacaciones", "RECHAZADO"));
  requestContainer.appendChild(createSolicitudDiv("Marta", "Comprobante de Pago", "REVISION"));
}

/**
 * This method make 'Solicitud' div. The idea is call this method when
 * you want craft a 'Solicitud'.
 * @param {*string} nombre Employee name
 * @param {*string} solicitud type of 'solicitud'
 * @param {*string} estado staus about  
 * 
 * TO DO: Change estado and solicitud to ENUM
 * @returns 
 */
function createSolicitudDiv(nombre, solicitud, estado) {
  // Create the main div
  const solicitudDiv = document.createElement('div');
  solicitudDiv.classList.add('solicitud');

  const solicitudBody = document.createElement('div');
  solicitudBody.classList.add('solicitud_body');
  // Create the title with the name
  const title = document.createElement('h3');
  title.textContent = `Solicitud de ${nombre}`;
  solicitudBody.appendChild(title);
  // Create the solicitud name
  const solicitudName = document.createElement('p');
  solicitudName.textContent = `Nombre de solicitud: ${solicitud}`;
  solicitudBody.appendChild(solicitudName);

  // Create the estado element with its color
  const estadoElement = document.createElement('p');
  estadoElement.textContent = `Estado: ${estado}`;
  if (estado === 'APROBADO') {
    estadoElement.classList.add('aprobado');
  } else if (estado === 'REVISION') {
    estadoElement.classList.add('revision');
  } else if (estado === 'RECHAZADO') {
    estadoElement.classList.add('rechazado');
  }
  solicitudBody.appendChild(estadoElement);

  // Create the button
  const button = document.createElement('button');
  button.textContent = 'Detalles';
  button.classList.add('detalles-btn'); 
  button.classList.add('submit-btn')
  solicitudDiv.appendChild(solicitudBody);
  solicitudDiv.appendChild(button);

  return solicitudDiv;
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


