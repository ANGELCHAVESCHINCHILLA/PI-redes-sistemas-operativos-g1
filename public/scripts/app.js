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
                      <link rel="stylesheet" href="../styles/form_solicitar_vacaciones.css">
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
 * Formats a date from num to string
 * @param {*int} numDate The num in format ddmmyy as a integer, e.g. 230523
 * @returns The date in format dd-mm-yy as a string, e.g. "23-05-23"
 */
function formatDate(numDate) {
  // numDate = 230523

  // Obtener los componentes de la fecha
  const year = Math.floor(numDate / 10000);
  const month = Math.floor((numDate % 10000) / 100);
  const day = numDate % 100;

  // Crear un objeto Date con los componentes de la fecha
  const date = new Date(year, month - 1, day);

  // Obtener los componentes de la date formateados con ceros a la izquierda
  const daysFormat = String(date.getDate()).padStart(2, '0');
  const montFormat = String(date.getMonth() + 1).padStart(2, '0');
  const yearFormat = String(date.getFullYear()).slice(2);

  // Crear la cadena de fecha con el formato deseado
  const dateFormat = `${daysFormat}-${montFormat}-${yearFormat}`;

  return dateFormat
}

/**
 * Open PAGE_REQUESTS page
 */
function openSolicitudesPage() {
  window.location.href = PAGE_REQUESTS;
}

/**
 * Reload the requests. It used to reload requests into a requests container.
 * Used in PAGE_REQUESTS page. It calls populateRequestContainer() and reloadDetailsBtns()
 */
function reloadRequests() {
  populateRequestContainer();
}

/**
 * Popoulate a request-container with requests divs.
 */
/*
{
  "request1": {
    "user": "Juan",
    "ID": 3,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi constancia salarial?",
    "feedback": "   ",
    "request_type": "ConstanciaSalarial",
    "vacation_days": 0,
    "vacation_start_date": 0,
    "vacation_end_date": 0,
    "area": "Cartago"
  },
  "request2": {
    "user": "Juan",
    "ID": 7,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi 13 dias de vacaciones?",
    "feedback": "   ",
    "request_type": "Vacaciones",
    "vacation_days": 13,
    "vacation_start_date": 11223,
    "vacation_end_date": 151223,
    "area": "Cartago"
  },
}
*/
async function populateRequestContainer() {
  const status = ["APROBADO", "REVISION", "RECHAZADO"];
  const username = localStorage.getItem('username');

  // send request to server
  const response = await fetch(`/consultRequestsByUser?user=${username}`, {
    method: 'GET'
  });

  if(!response.ok) {
    window.location.href = PAGE_PRINCIPAL;
  }
  // wait the JSON response
  const requests = await response.json();

  // Get Container
  var requestContainer = document.getElementById("request-container");
  // remove first
  while (requestContainer.firstChild) {
    requestContainer.removeChild(requestContainer.firstChild);
  }

  // Utilizando un bucle for...in
  for (const requestKey in requests) {
    if (requests.hasOwnProperty(requestKey)) {
      const request = requests[requestKey];
      // Populate with Solicitudes' Div
      requestContainer.appendChild(
        createSolicitudDiv(request.user, request.request_type
          , status[request.state], request.ID)
      );
    }
  }

  reloadDetailsBtns();
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
  console.log(`Request type: ${solicitud}`);
  console.log(`User: ${nombre}`);
  console.log(`ID: ${id}`);
  console.log(`estado: ${estado}`);
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
  // const idField = document.createElement("p");
  // idField.textContent = `ID: ${id}`;
  solicitudDiv.setAttribute("data-id", id);
  // solicitudBody.appendChild(idField);

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
 * Add listener event to new details buttons.
 *
 */
/*
{
  "user": "Juan",
  "ID": 3,
  "state": 0,
  "padding": "          ",
  "information": "Hola, por favor puedo tener mi constancia salarial?",
  "feedback": "   ",
  "request_type": "ConstanciaSalarial",
  "vacation_days": 0,
  "vacation_start_date": 0,
  "vacation_end_date": 0,
  "area": "Cartago"
}
*/
function reloadDetailsBtns() {
  // const detailsBtns = document.getElementsByClassName(".detalles-btn");
  const detailsBtns = document.querySelectorAll(".detalles-btn"); // get by class
  if (detailsBtns) {
    detailsBtns.forEach(function (btn) {
      btn.addEventListener("click", async () => {
        let requestDiv = btn.parentNode;
        let requestId = requestDiv.getAttribute("data-id");

        // send to server to get the request by ID
        const response = await fetch(`/consultRequestsByID?id=${requestId}`, {
          method: 'GET'
        });
      
        if(!response.ok) {
          window.location.href = PAGE_PRINCIPAL;
        }
      
        // wait the JSON response
        const request = await response.json();
        // build request info for be put in page
        let requestInfo = `Nombre: ${request.user}<br>
        Area: ${request.area}<br><br>
        Información: ${request.information}<br><br>`
        // TODO: si la request es de vacaciones, se debe agregar la informacion
        requestInfo += `Observación: ${request.feedback}<br>`;

        // The title is the request type, e.g. Constancia Salarial
        let requestTitle = `${request.request_type}`;
        createTextBlankPage(requestTitle, requestInfo);
      });
    });
  }
}

/*
asi se ve el json de respuesta que da el servidor para la parte de salarios
const json = {
  "name": "Carlos Montoya",
  "company_name": "Apple",
  "salaries": {
    "salary1": {
      "gross_salary": 2000,
      "net_salary": 3000,
      "salary_start_date": 230323
    },
    "salary2": {
      "gross_salary": 3000,
      "net_salary": 4000,
      "salary_start_date": 230523
    }
  }
};
*/
/**
 * Show the result of consult salary base
 */
async function showBaseSalary() {
  const username = localStorage.getItem('username');

  // Send request to server
  const response = await fetch(`/consultSalaryByUser?user=${username}`, {
    method: 'GET'
  });

  if(!response.ok) {
    window.location.href = PAGE_PRINCIPAL;
  }

  // wait the JSON response
  const salaryInfo = await response.json()

  // Construct page
  const title = "Información salarial";

  let content = `Nombre: ${salaryInfo.name} <br>
  Compañía: ${salaryInfo.company_name}<br><br>`;

  let salaryCount = 1;

  for (const salaryKey in salaryInfo.salaries) {
    if (salaryInfo.salaries.hasOwnProperty(salaryKey)) {
      const salary = salaryInfo.salaries[salaryKey];

      const salaryStrGross = numeroALetras.convertir(salary.gross_salary);
      const salaryStrNet = numeroALetras.convertir(salary.net_salary);

      content += `Salario ${salaryCount}<br>
      Salario base: CRC${salary.gross_salary} (${salaryStrGross})<br>
      Salario neto: CRC${salary.net_salary} (${salaryStrNet})<br>
      Fecha de inicio del salario: ${formatDate(salary.salary_start_date)} <br><br>`;
      salaryCount++;
    }
  }

  createTextBlankPage(title, content);
}

/**
 * Show my vacations balance
 */
async function showVacationsBalance() {
  const username = localStorage.getItem('username');

  // sent request to server
  const response = await fetch(`/consultVacationBalanceByUser?user=${username}`, {
    method: 'GET'
  });

  if(!response.ok) {
    window.location.href = PAGE_PRINCIPAL;
  }
  // wait the JSON response
  const vacations = await response.json();
  // construct the page
  const title = "Saldo de Vacaciones";

  let vacationsStr = numeroALetras.convertir(vacations.vacationBalance);

  const content = `Su saldo de vacaciones es de: ${vacations.vacationBalance}
   (${vacationsStr}) días.<br><br>`;

  createTextBlankPage(title, content);
}

/*
{
  "name": "Miranda Jop",
  "company_name": "Amazon",
  "annotations": {
    "annotation1": "Miranda chocó el carro en el parqueo de la compañía el día 22/3/23",
    "annotation2": "Miranda se robó una computadora el día 23/3/23",
  }
}
*/
/**
 * Show my annotations to expedient
 */
async function showExpedientAnotations() {
  const username = localStorage.getItem('username');

  // sent request to server
  const response = await fetch(`/consultAnnotationsByUser?user=${username}`, {
    method: 'GET'
  });

  if(!response.ok) {
    window.location.href = PAGE_PRINCIPAL;
  }
  // wait the JSON response
  const annotations = await response.json();

  let title = "Anotaciones al expediente";

  let content = `Nombre: ${annotations.name}<br>
  Empresa: ${annotations.company_name}<br><br>`;

  let annotCount = 1;
  // Recorrer las anotaciones utilizando un bucle for...in
  for (const annotationKey in annotations.annotations) {
    if (annotations.annotations.hasOwnProperty(annotationKey)) {
      const annotation = annotations.annotations[annotationKey];
      content += `Anotación ${annotCount}: ${annotation}<br>`;
      annotCount++;
    }
  }

  // Create page
  createTextBlankPage(title, content);
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
            <button id="regresar">Regresar</button>
            <div id="form-container"></div>
            <button id="enviar">Enviar solicitud</button>
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
    newPage.document.getElementById("enviar").addEventListener("click", makeRequest.bind(null, form, title));
    return newPage;
}

/*
{
  "user": "CamiloSua",
  "request_type": "Vacation",
  "information": "Deseo pedir vacaciones por favor",
  "area": "San Jose",
  "vacation_days": 14,
  "vacation_start_date": 10623,
  "vacation_end_date": 150623
}
*/

async function makeRequest(form, reqType) {
  let formJson = Object.values(form).reduce((obj,field) => { obj[field.name] = field.value; return obj }, {});
  console.log(formJson);
  let body = {
    user: formJson.user,
    request_type: reqType,
    information: formJson.information,
    // TODO: get area from local storage, this below is just a dummy value
    area: "San Jose",
    vacation_days: formJson.vacationDays ?? 0,
    vacation_start_date: formJson.vacationStartDate ?? 0,
    vacation_end_date: formJson.vacationEndDate ?? 0
  }

  fetch('/makeRequest', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(body)
  })
  .then(function (response) {
    return response.status;
  })
  .then(function (status) {
    if (status === 401) {
      window.location.href = DEFAUL_PAGE;
    }
  })
  .catch(function (error) {
      // Manejar el error en caso de que la solicitud falle
      alert('Error al enviar la solicitud:', error);
  });
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
    let user = localStorage.getItem('username');
    form
        .addReadOnlyText("user", "Usuario:", user)
        .addTextField("information", "Información de la solicitud:", true)
    createFormPage(title, form.build());
}

function openEmploymentCertificateForm() {
    let title = "Constancia laboral";
    let form = new FormBuilder();
    // TODO: get employee name via localStorage
    let user = localStorage.getItem('username');
    form
        .addReadOnlyText("user", "Usuario:", user)
        .addTextField("information", "Información de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false);
    createFormPage(title, form.build());
}

function openVacationsForm() {
    let title = "Solicitud de Vacaciones";
    let form = new FormBuilder();
    // TODO: get employee name via localStorage
    let user = localStorage.getItem('username');
    form
        .addReadOnlyText("user", "Usuario:", user)
        .addTextField("information", "Información de la solicitud:", true)
        .addNumericField("dias-vacaciones", "Especifique la cantidad de días", true)
        .addDateField("inicio-vacaciones", "Fecha de inicio de las vacaciones")
        .addDateField("final-vacaciones", "Fecha final de las vacaciones");
    createFormPage(title, form.build());
}

function openPaymentProofForm() {
    let title = "Constancia de Pago";
    let form = new FormBuilder();
    // TODO: get employee name via localStorage
    let user = localStorage.getItem('username');
    form
        .addReadOnlyText("user", "Usuario:", user)
        .addTextField("information", "Información de la solicitud:", true)
        .addTextField("informacion-adicional", "Información Adicional:", false);
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
