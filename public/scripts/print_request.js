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
const DEFAUL_PAGE = 'http://127.0.0.1:8001/';
const ADD_ANNOTATION = "supervisory/add_annotation_html";

// common html head used. Used for quick html pages creation
const HTML_HEAD = `<title>Información de solicitud</title>
                      <meta charset="UTF-8">
                      <link rel="stylesheet" href="../styles/styles.css">
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

const requestId = localStorage.getItem('requestID');

if (requestId) {
  // send to server to get the request by ID
  const response = await fetch(`/consultRequestsByID?id=${requestId}`, {
    method: 'GET'
  });

  if(!response.ok) {
    alert("No es posible acceder a la constancia en este momemto");
    window.location.href = PAGE_PRINCIPAL;
  }
  // wait the JSON response
  const request = await response.json();
  if (request.state === 1) {
    if(request.request_type === "Constancia de Salarios") {
      createConstanciaSalaria(request);
    } else if(request.request_type === "Constancia Laboral") {
      createConstanciaLaboral(request);
    }
    console.log("Ya fue aprobada la solicitud");
  } else {
    console.log("No ha sido aprobada");
  }
} else {
  console.log("No existe la request el local storage");
}

function formatOrderDate(date, format) {
  const map = {
      dd: date.getDate(),
      mm: date.getMonth() + 1,
      yy: date.getFullYear().toString().slice(-2),
      yyyy: date.getFullYear()
  }

  return format.replace(/dd|mm|yy|yyy/gi, matched => map[matched])
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

async function createConstanciaLaboral(request) {
  // Obtén una referencia al elemento request-container
  const requestContainer = document.getElementById('request-container');

  // Crea los elementos HTML y asigna los valores de los datos
  const constanciaLaboral = document.createElement('div');
  constanciaLaboral.classList.add('constancia-salarial');

  const requestTitle = document.createElement('h2');
  requestTitle.textContent = "Constancia Laboral";

  const nombreEmpleado = document.createElement('h3');
  nombreEmpleado.textContent = "Nombre de empleado: " + request.user;

  const fecha = document.createElement('h3');
  const tiempoTranscurrido = Date.now();
  const today = new Date(tiempoTranscurrido);
  fecha.textContent = `Fecha de emisión: ${formatOrderDate(today, 'dd/mm/yy')}`;

  const formalidad = document.createElement('p');
  formalidad.textContent = `Por este medio se hace constar que el señor ${request.user},
  se encuentra laborando para la empresa Guachimanes S.A.`;

  const formalText = document.createElement('p');
  formalText.textContent = `Se extiende la presente constancia a solicitud de 
  la parte interesada y para los fines que se estime conveniente, en la ciudad
  de San José el día ${today.getDate()} del mes ${today.getMonth() + 1} del año
  ${today.getFullYear()}`;

  // Agrega los elementos al contenedor
  constanciaLaboral.appendChild(requestTitle);
  constanciaLaboral.appendChild(nombreEmpleado);
  constanciaLaboral.appendChild(fecha);
  constanciaLaboral.appendChild(formalidad);
  constanciaLaboral.appendChild(formalText);
  requestContainer.appendChild(constanciaLaboral);
}

async function createConstanciaSalaria(request) {
  // Obtén una referencia al elemento request-container
  const requestContainer = document.getElementById('request-container');

  // Crea los elementos HTML y asigna los valores de los datos
  const constanciaSalarial = document.createElement('div');
  constanciaSalarial.classList.add('constancia-salarial');

  const requestTitle = document.createElement('h2');
  requestTitle.textContent = "Constancia Salarial";

  const nombreEmpleado = document.createElement('h3');
  nombreEmpleado.textContent = "Nombre de empleado: " + request.user;

  const fecha = document.createElement('h3');
  const tiempoTranscurrido = Date.now();
  const today = new Date(tiempoTranscurrido);
  fecha.textContent = `Fecha de emisión: ${formatOrderDate(today, 'dd/mm/yy')}`;

  const formalidad = document.createElement('p');
  formalidad.textContent = `Por este medio se hace constar que el señor ${request.user},
  se encuentra laborando para la empresa Guachimanes S.A. con un salario de:`;

  const salaryInfo = await fetch(`/consultSalaryByUser?user=${request.user}`, {
    method: 'GET'
  });
  if(!salaryInfo.ok) {
    alert("No es posible acceder a la constancia en este momemto");
    window.location.href = PAGE_PRINCIPAL;
  }
  // wait the JSON response
  const salaries = await salaryInfo.json();

  const salarioContainer = document.createElement('div');

  for (const salaryKey in salaries.salaries) {
    if (salaries.salaries.hasOwnProperty(salaryKey)) {
      const salary = salaries.salaries[salaryKey];

      const salaryStrGross = numeroALetras.convertir(salary.gross_salary);
      const salaryStrNet = numeroALetras.convertir(salary.net_salary);
      
      const salaryElement = document.createElement('div');
      salaryElement.innerHTML = `Salario base: ${salary.gross_salary.toLocaleString('en-US', { style: 'currency', currency: 'USD' })} (${salaryStrGross})<br>
      Salario neto: ${salary.net_salary.toLocaleString('en-US', { style: 'currency', currency: 'USD' })} (${salaryStrNet})<br>
      Fecha de inicio del salario: ${formatDate(salary.salary_start_date)}`;

      salarioContainer.appendChild(salaryElement);
    }
  }

  const formalText = document.createElement('p');
  formalText.textContent = `Se extiende la presente constancia a solicitud de 
  la parte interesada y para los fines que se estime conveniente, en la ciudad
  de San José el día ${today.getDate()} del mes ${today.getMonth() + 1} del año
  ${today.getFullYear()}`;

  // Agrega los elementos al contenedor
  constanciaSalarial.appendChild(requestTitle);
  constanciaSalarial.appendChild(nombreEmpleado);
  constanciaSalarial.appendChild(fecha);
  constanciaSalarial.appendChild(formalidad);
  constanciaSalarial.appendChild(salarioContainer);
  constanciaSalarial.appendChild(formalText);
  requestContainer.appendChild(constanciaSalarial);
}