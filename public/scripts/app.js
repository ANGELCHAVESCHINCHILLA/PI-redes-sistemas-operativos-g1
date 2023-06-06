import {NAL} from "../scripts/libs/NumeroALetras.js";
import {FormBuilder} from "../scripts/formbuilder.js";
// const NumeroALetras = require('./libs/NumeroALetras');
// back button
const backbtn = document.querySelector("back-btn");
// library to parse number to letters
const numeroALetras = new NAL();
// principal page
const PAGE_PRINCIPAL = "index.html";
// login page
const PAGE_LOGIN = "login.html";
// requests page
const PAGE_REQUESTS = "solicitudes.html";
const DEFAUL_PAGE = 'http://127.0.0.1:8080/';

// common html head used. Used for quick html pages creation
const HTML_HEAD = `<title>Información de solicitud</title>
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
                      <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">`;

if (backbtn) {
    backbtn.addEventListener("click", function (event) {
        window.history.back();
    });
}

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
    requestContainer.appendChild(
        createSolicitudDiv("Marta", "Constancia Salarial", "APROBADO", 0)
    );
    requestContainer.appendChild(
        createSolicitudDiv("Marta", "Vacaciones", "RECHAZADO", 1)
    );
    requestContainer.appendChild(
        createSolicitudDiv("Marta", "Comprobante de Pago", "REVISION", 2)
    );
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
    const solicitudDiv = document.createElement("div");
    solicitudDiv.classList.add("solicitud");

    const solicitudBody = document.createElement("div");
    solicitudBody.classList.add("solicitud_body");
    // Create the title with the name
    const title = document.createElement("h3");
    title.textContent = `Solicitud de ${nombre}`;
    solicitudBody.appendChild(title);
    // Create the solicitud name
    const solicitudName = document.createElement("p");
    solicitudName.textContent = `Nombre de solicitud: ${solicitud}`;
    solicitudBody.appendChild(solicitudName);
    // Manage the ID
    const idField = document.createElement("p");
    idField.textContent = `ID: ${id}`;
    solicitudDiv.setAttribute("data-id", id);
    solicitudBody.appendChild(idField);

    // Create the estado element with its color
    const estadoElement = document.createElement("p");
    estadoElement.textContent = `Estado: ${estado}`;
    if (estado === "APROBADO") {
        estadoElement.classList.add("aprobado");
    } else if (estado === "REVISION") {
        estadoElement.classList.add("revision");
    } else if (estado === "RECHAZADO") {
        estadoElement.classList.add("rechazado");
    }
    solicitudBody.appendChild(estadoElement);

    // Create the button
    const button = document.createElement("button");
    button.textContent = "Detalles";
    button.classList.add("detalles-btn");
    button.classList.add("submit-btn");
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
            requestInfo =
                "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Marta Viquez, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nMarta Viquez";
            break;
        case "1":
            requestInfo =
                "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Lobo Lopez, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nLobo Lopez";

            break;
        case "2":
            requestInfo =
                "Me dirijo a usted para solicitar formalmente mis vacaciones anuales correspondientes. Soy Jonathan Beltran, empleada de esta empresa desde hace [número de años/trimestres/meses].\nMe gustaría solicitar un período de vacaciones desde el [fecha de inicio] hasta el [fecha de finalización] para poder disfrutar de un merecido descanso y pasar tiempo con mi familia y amigos. Durante mi ausencia, he tomado las medidas necesarias para garantizar que mi trabajo sea cubierto y que los plazos y responsabilidades se cumplan sin problemas. Por favor, háganme saber si hay algún problema o si necesitan que realice alguna tarea adicional antes de irme.\nAgradezco de antemano su consideración y espero poder disfrutar de un descanso reparador. Si necesita más información o detalles adicionales, no dude en ponerse en contacto conmigo.\n Atentamente,\nJonathan Beltran";
            break;
        default:
            "Texto no disponible. Llame a soporte";
    }
    console.log(`En request: ${requestId}`);
    return requestInfo;
}

/**
 * Add listener event to new details buttons.
 *  TODO: Maybe this method could be more abstract.
 */
function reloadDetailsBtns() {
    const detailsBtns = document.querySelectorAll(".detalles-btn"); // get by class
    if (detailsBtns) {
        detailsBtns.forEach(function (btn) {
            btn.addEventListener("click", function () {
                let requestDiv = btn.parentNode;
                let requestId = requestDiv.getAttribute("data-id");
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
  var sessionId = localStorage.getItem('logged');

  fetch('/consultSalaryByUser', {
      method: 'POST',
      headers: {
          'Content-Type': 'application/json'
      },
      body: JSON.stringify({sessionId: sessionId})
  })
    .then(function (response) {
        if (response.ok) {
          return response.json();
        } else {
          window.location.href = PAGE_PRINCIPAL;
        }
    })
    .then(function (data) {
      console.log(data);
      console.log(data.name);
      console.log(data.company_name);
      console.log(data.salaries[0]);  // Gross Salary
      console.log(data.salaries[1]);  // Net Salary
      console.log(data.salaries[2]);  // Salary Start Date
    
      // TODO: search 'employee' data in database calling a method in FileSystem API
      let salaryStr = numeroALetras.convertir(data.salaries[0]);
      let title = "Salario Base";
      const content = `Su salario base es de: CRC${data.salaries[0]} (${salaryStr})<br><br>
              [Nombre y cargo del representante de la empresa] <br>
              Compañía: ${data.company_name}<br>
              [Fecha de emisión]<br>`;

      createTextBlankPage(title, content);
    })
    .catch(function (error) {
      // Manejar el error en caso de que la solicitud falle
      console.error('Error al enviar la solicitud:', error);
    });
}

function showVacationsBalance() {
    console.log("asd");
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
      ${HTML_HEAD}
      <title>${title}</title>
    </head>
    <body id="consultas">
      <div id="holder">
        <div id="body">
          <div class="w3-container w3-light-blue">
            <h1>Consulta</h1>
          </div>
          <div id="page-blank-container">
            <h2>${title}</h2>
            <button id="regresar" onclick="window.close()"></button>
            <div id="text-container"> ${content} </div>
            <button class="submit-btn imprimir-btn">IMPRIMIR</button>
          </div>
        </div>
        <footer style="bottom: 0px">
          Sistema de Gestión de Recursos Humanos
        </footer>
      </div>
    </body>

  </html>
`);
    return newPage;
}

/**
 * Create a simple blan page, just title and content
 * @param {*} title title of the page
 * @param {*} form content to be showed in div 'text-container'
 */
function createFormPage(title, form) {
    let newPage = window.open();
    newPage.document.write(`<!DOCTYPE html>
  <html>
    <head>
      ${HTML_HEAD}
      <title>${title}</title>
    </head>
    <body id="consultas">
      <div id="holder">
        <div id="body">
          <div class="w3-container w3-light-blue">
            <h1>Consulta</h1>
          </div>
          <div id="page-blank-container">
            <h2>${title}</h2>
            <button id="regresar" onclick="window.close()"></button>
            <div id="form-container"></div>
          </div>
        </div>
        <footer style="bottom: 0px">
          Sistema de Gestión de Recursos Humanos
        </footer>
      </div>
    </body>

  </html>
`);
    const textContainer = newPage.document.getElementById("form-container");
    textContainer.appendChild(form);
    // textContainer.innerHTML = form;
    return newPage;
}

function createAcceptDenyPage(title, content) {
    let newPage = window.open();
    newPage.document.write(`<!DOCTYPE html>
  <html>
    <head>
      ${HTML_HEAD}
      <title>${title}</title>
    </head>
    <body id="consultas">
      <div id="holder">
        <div id="body">
          <div class="w3-container w3-light-blue">
            <h1>Consulta</h1>
          </div>
          <div id="page-blank-container">
            <h2>${title}</h2>
            <button id="regresar" onclick="window.close()"></button>
            <div id="text-container"> ${content} </div>
            <button class="submit-btn deny-btn">DENEGAR</button>
            <button class="submit-btn accept-btn">APROBAR</button>
          </div>
        </div>
        <footer style="bottom: 0px">
          Sistema de Gestión de Recursos Humanos
        </footer>
      </div>
    </body>
  </html>
  `);
}

function createUserRegistrationPage() {
    let title = "Registrar Usuario";
    let form = new FormBuilder()
        .addTextField("nomnre", "Nombre:", true)
        .addTextField("apellido-1", "Primer Apellido:", true)
        .addTextField("apellido-2", "Segundo Apellido:", true)
        .addTextField("cedula", "Cédula:", true)
        .addTextField("numero", "Número telefónico:", true)
        .addTextField("residencia", "Residencia:", true)
        .addTextField("iban", "Número IBAN:", true)
        .addDateField("fecha-nacimiento", "Fecha de Nacimiento:")
        .build();

    return createFormPage(title, form);
}

function openSalaryConstanceForm() {
    let title = "Constancia de Salarios";
    let form = new FormBuilder();
    // TODO: get employee name via backend
    let employeeName = "Marta Gonzalez Beltrán";
    form
        .addReadOnlyText("empleado", "Empleado:", employeeName)
        .addTextField("motivo", "Motivo de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false)
        .addSubmitlButton("enviar", "Enviar")
        .addCancelButton("cancelar", "Cancelar");
    createFormPage(title, form.build());
}

function openEmploymentCertificateForm() {
    let title = "Constancia laboral";
    let form = new FormBuilder();
    // TODO: get employee name via backend
    let employeeName = "Marta Gonzalez Beltrán";
    form
        .addReadOnlyText("empleado", "Empleado:", employeeName)
        .addTextField("motivo", "Motivo de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false)
        .addSubmitlButton("enviar", "Enviar")
        .addCancelButton("cancelar", "Cancelar");
    createFormPage(title, form.build());
}

function openVacationsForm() {
    let title = "Solicitud de Vacaciones";
    let form = new FormBuilder();
    // TODO: get employee name via backend
    let employeeName = "Marta Gonzalez Beltrán";
    form
        .addReadOnlyText("empleado", "Empleado:", employeeName)
        .addNumericField("dias-vacaciones", "Especifique la cantidad de días", true)
        .addDateField("inicio-vacaciones", "Fecha de inicio de las vacaciones")
        .addDateField("final-vacaciones", "Fecha final de las vacaciones")
        .addTextField("motivo", "Motivo de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false)
        .addSubmitlButton("enviar", "Enviar")
        .addCancelButton("cancelar", "Cancelar");
    createFormPage(title, form.build());
}

function openPaymentProofForm() {
    let title = "Constancia de Pago";
    let form = new FormBuilder();
    // TODO: get employee name via backend
    let employeeName = "Marta Gonzalez Beltrán";
    form
        .addReadOnlyText("empleado", "Empleado:", employeeName)
        .addTextField("motivo", "Motivo de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false)
        .addSubmitlButton("enviar", "Enviar")
        .addCancelButton("cancelar", "Cancelar");
    createFormPage(title, form.build());
}

function openRequestForm(id) {
    // TODO: Check if the employee make another request in the past 24 hours
    // if true, decline the access to the form
    switch (id) {
        case "salarial-btn":
            openSalaryConstanceForm();
            break;
        case "laboral-btn":
            openEmploymentCertificateForm();
            break;
        case "pago-btn":
            openPaymentProofForm();
            break;
        case "vacaciones-btn":
            openVacationsForm();
            break;
        default:
            console.error(`Error: the button with id ${id} couldn't be handled`);
    }
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

document.addEventListener('DOMContentLoaded', function () {
    var data = localStorage.getItem('logged');

    fetch('/validate', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({data: data})
    })
        .then(function (response) {
            return response.status;
        })
        .then(function (status) {
            console.log(status)
            if (status === 401) {
                window.location.href = DEFAUL_PAGE;
            }
        })
            .catch(function (error) {
                // Manejar el error en caso de que la solicitud falle
                console.error('Error al enviar la solicitud:', error);
            });
});


export {
    openSolicitudesPage,
    showExpedientAnotations,
    showVacationsBalance,
    showBaseSalary,
    openRequestForm,
    reloadRequests,
    toBackPage,
};
