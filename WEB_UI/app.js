const login = document.getElementById("login"); // get by id
const backbtn = document.querySelector("back-btn")
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
if (backbtn) {
  backbtn.addEventListener('click', function (event) {
    console.log("yah");
    window.history.back();
  });
}


function reloadRequests() {
  populateRequestContainer();
  reloadDetailsBtns();
}


function populateRequestContainer() {
  // Get Container
  var requestContainer = document.getElementById("request-container");
  /**TODO: Read from filesystem what request have the employee reader.Then, from their
   * requests, craft the divs and populate them to the container. The actual implemention just
   * populate three static requests. The actual employee is Marta.
   */

  // Populate with Solicitudes' Div
  requestContainer.appendChild(createSolicitudDiv("Marta", "Constancia Salarial", "APROBADO", 0));
  requestContainer.appendChild(createSolicitudDiv("Marta", "Vacaciones", "RECHAZADO", 1));
  requestContainer.appendChild(createSolicitudDiv("Marta", "Comprobante de Pago", "REVISION", 2));
}

/**
 * This method make 'Solicitud' div. The idea is call this method when
 * you want craft a 'Solicitud'.
 * @param {*string} nombre Employee name
 * @param {*string} solicitud type of 'solicitud'
 * @param {*string} estado staus about 
 * @param {*string} id request id   
 * 
 * TO DO: Change estado and solicitud to ENUM
 * @returns 
 */
function createSolicitudDiv(nombre, solicitud, estado, id) {
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
  // Manage the ID 
  const idField = document.createElement('p');
  idField.textContent = `ID: ${id}`;
  solicitudDiv.setAttribute('data-id', id);
  solicitudBody.appendChild(idField)

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

function searchRequest(requestId) {
  // TODO: search in FileSystem by request id the requestInfo
  // The actual implemention is weird. Just ids from zero to two.
  // Used to static actual implementation
  // return requestInfo;
  let requestInfo = "";
  console.log(requestId);
  switch (requestId) {
    case "0":
      requestInfo = "Es cero"
      break;
    case "1":
      requestInfo = "Es uno"
      break;
    case "2":
      requestInfo = "Es dos"
      break;
    default: "Default Of course"
  }
  console.log(`En request: ${requestId}`);
  return requestInfo;
}

function reloadDetailsBtns() {
  const detailsBtns = document.querySelectorAll('.detalles-btn'); // get by class
  if (detailsBtns) {
    detailsBtns.forEach(function (btn) {
      btn.addEventListener('click', function () {
        let requestDiv = btn.parentNode;
        let requestId = requestDiv.getAttribute('data-id');
        // let requestInfo = searchRequest;
        let requestInfo = searchRequest(requestId);
        createTextBlankPage(requestInfo);
      });
    });
  }
}

function createTextBlankPage(text) {
  let newPage = window.open();
  newPage.document.write(`<!DOCTYPE html>
  <html>
    <head>
      <title>Información de solicitud</title>
      <meta charset="UTF-8">
      <link rel="stylesheet" href="index.css">
      <link rel="preconnect" href="https://fonts.googleapis.com">
      <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
      <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@100&display=swap" rel="stylesheet">
      <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300&display=swap" rel="stylesheet">
      <link href="https://fonts.googleapis.com/css2?family=Public+Sans:wght@100&family=Roboto:wght@300&display=swap"
        rel="stylesheet">
      <link
        href="https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@100&family=Public+Sans:wght@100&family=Roboto:wght@300;400&display=swap"
        rel="stylesheet">
    </head>
    <body>
      <div id="text-container">${text}</div>
      <button onclick="window.close()">Regresar</button>
    </body>
  </html>
`);
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


