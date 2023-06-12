/**
 * Reload the requests. It used to reload requests into a requests container.
 * Used in PAGE_REQUESTS page. It calls populateRequestContainer() and reloadDetailsBtns()
 */

populateRequestContainer();
reloadDetailsBtns();

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

  // Utilizando un bucle for...in
  for (const requestKey in requests) {
    if (requests.hasOwnProperty(requestKey)) {
      const request = requests[requestKey];
      // console.log(`Request type: ${request.request_type}`);
      // console.log(`User: ${request.user}`);
      // console.log(`ID: ${request.ID}`);
      // console.log(`estado: ${request.state}: ${status[request.state]}`);
      // Populate with Solicitudes' Div
      requestContainer.appendChild(
        createSolicitudDiv(request.user, request.request_type
          , status[request.state], request.ID)
      );
    }
  }
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
function reloadDetailsBtns() {
  console.log("voy a re cargar detalles")
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
        console.log(request);

        // The title is the request type, e.g. Constancia Salarial
        let requestTitle = `${request.request_type}`;
        createTextBlankPage(requestTitle, requestInfo);
      });
    });
  }
}