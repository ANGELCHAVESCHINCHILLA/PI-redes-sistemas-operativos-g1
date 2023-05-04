import { NAL } from '../scripts/libs/NumeroALetras.js';
// const NumeroALetras = require('./libs/NumeroALetras');

const backbtn = document.querySelector("back-btn");
const numeroALetras = new NAL();
const PAGE_PRINCIPAL = "index.html";
const PAGE_LOGIN = "login.html";
const PAGE_REQUESTS = "solicitudes.html";

if (backbtn) {
  backbtn.addEventListener('click', function (event) {
    window.history.back();
  });
};

/**
 * Reload the requests. It used to reload requests into a requests container.
 * Used in PAGE_REQUESTS page. It calls populateRequestContainer() and reloadDetailsBtns()
 */
function reloadRequests() {
  populateRequestContainer();
  reloadDetailsBtns();
}
/**
 * Popoulate a request-container with requests divs.
 */
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
  solicitudBody.appendChild(idField);

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
  button.classList.add('submit-btn');
  solicitudDiv.appendChild(solicitudBody);
  solicitudDiv.appendChild(button);

  return solicitudDiv;
}

/**
 * This method *MUST* be into a FileSystemAPI. Is used here just for an example, but NEVER 
 * could exists on frontend orient JS file.
 * @param {*} requestId 
 * @returns 
 */
function searchRequest(requestId) {
  // TODO: search in FileSystem by request id the requestInfo
  // The actual implemention is weird. Just ids from zero to two.
  // Used to static actual implementation
  // return requestInfo;
  let requestInfo = "";
  console.log(requestId);
  switch (requestId) {
    case "0":
      requestInfo = "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Marta Viquez, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nMarta Viquez";
      break;
    case "1":
      requestInfo = "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Lobo Lopez, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nLobo Lopez";

      break;
    case "2":
      requestInfo = "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Jonathan Beltran, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nJonathan Beltran";
      break;
    default: "Texto no disponible. Llame a soporte"
  }
  console.log(`En request: ${requestId}`);
  return requestInfo;
}

/**
 * Add listener event to new details buttons.
 *  TODO: Maybe this method could be more abstract. 
 */
function reloadDetailsBtns() {
  const detailsBtns = document.querySelectorAll('.detalles-btn'); // get by class
  if (detailsBtns) {
    detailsBtns.forEach(function (btn) {
      btn.addEventListener('click', function () {
        let requestDiv = btn.parentNode;
        let requestId = requestDiv.getAttribute('data-id');
        // let requestInfo = searchRequest.info;
        // let requestTitle = searchRequest.title;
        let requestInfo = searchRequest(requestId);
        let requestTitle = "Solicitud de Vacaciones";
        createTextBlankPage(requestTitle, requestInfo);
      });
    });
  }
}

function showBaseSalary() {
  // TODO: search 'employee' data in database calling a method in FileSystem API
  let salary = 5000000;
  let salaryStr = numeroALetras.convertir(salary);
  let title = "Salario Base";
  const content = `Su salario base es de: CRC${salary} (${salaryStr})<br><br>
            [Nombre y cargo del representante de la empresa] <br>
            [Nombre de la empresa]<br>
            [Fecha de emisión]<br>`;

  createTextBlankPage(title, content);
}

function showVacationsBalance() {
  console.log("asd")
  // TODO: search 'employee' data in database calling a method in FileSystem API
  let vacations = 15;
  let vacationsStr = numeroALetras.convertir(15);
  let title = "Saldo de Vacaciones";
  const content = `Su saldo de vacaciones es de: ${vacations} (${vacationsStr}) días.<br><br>
            [Nombre y cargo del representante de la empresa] <br>
            [Nombre de la empresa]<br>
            [Fecha de emisión]<br>`;

  createTextBlankPage(title, content);
}

function showExpedientAnotations() {
  // TODO: search 'employee' data in database calling a method in FileSystem API
  let title = "Anotaciones al expediente";
  const content = `- El [fecha], el empleado llegó tarde al trabajo sin previo aviso y sin una justificación válida. Se le ha recordado la política de puntualidad de la empresa y se le ha informado que otra falta similar podría resultar en una medida disciplinaria. <br><br>
  - El [fecha], se recibió una queja de un cliente que afirma que el empleado fue poco amable y no pudo solucionar su problema de manera efectiva. Se ha hablado con el empleado y se le ha recordado la importancia de mantener un servicio al cliente de alta calidad. <br><br>
  - El [fecha], el empleado tuvo una reunión con su supervisor para discutir su desempeño. Se discutieron áreas en las que el empleado ha mostrado fortalezas y áreas que necesitan mejorar. Se acordó un plan de acción para ayudar al empleado a alcanzar sus objetivos de desempeño. <br><br>
  - El [fecha], el empleado recibió un reconocimiento por su excelente desempeño en la finalización de un proyecto importante. Se le agradeció por su dedicación y esfuerzo en la empresa.<br><br>
            [Nombre y cargo del representante de la empresa] <br>
            [Nombre de la empresa]<br>
            [Fecha de emisión]<br>`;

  createTextBlankPage(title, content);
}

/**
 * Open PAGE_REQUESTS page
 */
function openSolicitudesPage() {
  window.location.href = PAGE_REQUESTS;
}

/**
 * Create a simple blan page, just title and content
 * @param {*} title title of the page
 * @param {*} content content to be showed in div 'text-container'
 */
function createTextBlankPage(title, content) {
  let newPage = window.open();
  newPage.document.write(`<!DOCTYPE html>
  <html>
    <head>
      <title>Información de solicitud</title>
      <meta charset="UTF-8">
      <link rel="stylesheet" href=".././styles/styles.css">
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
      <div id="page-blank-container">
        <h2>${title}</h2>
        <button id="regresar" onclick="window.close()"></button>
        <div id="text-container"><p> ${content} </p></div>
        <button class="submit-btn imprimir-btn">IMPRIMIR</button>
      </div>
      <script src=".././scripts/scripts.js"></script>
    </body>

  </html>
`);
}

/**
 * TODO: Make a file only for button functions
 */

/**
 * Back to page
 */
function toBackPage() {
  window.history.back();
}
function cancelar() {
  /** Nothing for now ;) */
}

export {
  openSolicitudesPage,
  showExpedientAnotations,
  showVacationsBalance,
  showBaseSalary,
  reloadRequests,
  toBackPage
};