const PAGE_PRINCIPAL = "/index.html";
const PAGE_QUERIES = "/supervisory_queries";

const send_annotation_btn = document.getElementById("send-annotation");
const cancel_btn = document.getElementById("cancel");
const back_btn = document.getElementById('regresar');
const reload_request_btn = document.getElementById("reload-requests");
const aprove_query_btn = document.getElementById("approve-query-btn");
const deny_btn = document.getElementById("deny-btn");

if (send_annotation_btn) {
    send_annotation_btn.addEventListener("submit", function (event) {
        // event.preventDefault();

        // Obtener los valores de los campos
        const username = document.getElementById("username").value;
        const annotation = document.getElementById("annotation").value;

        if (username && annotation) {
            // TODO(future's david): when DB has a function to add an annotation, finish this :*
            alert("Enviado!")
        }
        document.getElementById("username").value = "";
        document.getElementById("anotacion").value = "";
    });

}

if (cancel_btn) {
    cancel_btn.addEventListener("click", function (event) {
        window.location.href = PAGE_PRINCIPAL;
    });
}

if (back_btn) {
    back_btn.addEventListener("click", function (event) {
        window.location.href = PAGE_PRINCIPAL;
    })
}

if (reload_request_btn) {
    reload_request_btn.addEventListener("click",function (event) {
        reloadRequests();
    } )
}

function reloadRequests() {
    populateRequestContainer();
}

async function populateRequestContainer() {
    const status = ["APROBADO", "REVISION", "RECHAZADO"];
    const area = 'SanJose';

    try {
        const response = await fetch(`/consultRequestsByArea?area=${area}`, {
            method: 'GET'
        });

        const responseText = await response.text();
        console.log(responseText);
        const requests = JSON.parse(responseText);


        const requestContainer = document.getElementById("request-container");
        while (requestContainer.firstChild) {
            requestContainer.removeChild(requestContainer.firstChild);
        }
        for (const requestKey in requests) {
            if (requests.hasOwnProperty(requestKey)) {
                const request = requests[requestKey];
                requestContainer.appendChild(
                    createSolicitudDiv(request.user, request.request_type, status[request.state], request.ID)
                );
            }
        }
        reloadDetailsBtns();

    } catch (error) {
        console.error(error);
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

                if (!response.ok) {
                    alert("Ha ocurrido un error en la comunicación. Rediriguiendo a la página principal")
                    window.location.href = PAGE_PRINCIPAL;
                }

                // wait the JSON response
                const requests = await response.json();
                console.log(requests);
                // build request info for be put in page
                let requestInfo = `Nombre: ${request.user}<br>
        Area: ${request.area}<br><br>
        Información: ${request.information}<br><br>`
                // TODO: si la request es de vacaciones, se debe agregar la informacion
                requestInfo += `Observación: ${request.feedback}<br>`;

                // The title is the request type, e.g. Constancia Salarial
                let requestTitle = `${request.request_type}`;
                createAcceptDenyPage(requestTitle, requestInfo,request);
            });
        });
    }
}

if (aprove_query_btn) {
    aprove_query_btn.addEventListener("click", function () {
        const request_div = document.getElementById("request_id");
        const request_str = (request_div.getAttribute("request_id"));
        console.log(request_str);
        const request = JSON.parse(request_str);

        const fetchInfo = {
            request_id: request.ID,
            state: 1,
            feedback: "Solicitud aprobada por el supervisor del área"
        }
        fetch('/checkRequest', {
            method: 'POST',
            body: JSON.stringify(fetchInfo)
        }).then(response => {
            if (!response.ok) {
                alert("Ha ocurrido un error en la comunicación. Rediriguiendo a la página de consultas")
            } else {
                alert("Solicitud APROBADA correctamente. Rediriguiendo a la página de consultas")
            }
            window.location.href = PAGE_QUERIES;
        })
    })
}
if (deny_btn) {
    deny_btn.addEventListener("click", function () {
        const request_div = document.getElementById("request_id");
        const request_int = parseInt(request_div.getAttribute("request_id"));
        console.log(request_str);
        const request = JSON.parse(request_str);

        const fetchInfo = {
            request_id: request.ID,
            state: 2,
            feedback: "Solicitud denegada por el supervisor del área"
        }
        fetch('/checkRequest', {
            method: 'POST',
            body: JSON.stringify(fetchInfo)
        }).then(response => {
            if (!response.ok) {
                alert("Ha ocurrido un error en la comunicación. Rediriguiendo a la página de consultas")
            } else {
                alert("Solicitud DENEGADA correctamente. Rediriguiendo a la página de consultas")
            }
            window.location.href = PAGE_QUERIES;
        })
    })
}

function createAcceptDenyPage(title, content, request) {
    let newPage = window.open();
    newPage.document.write(`<!DOCTYPE html>
  <html>
    <head>
      <title>${title}</title>
      <link rel="stylesheet" href=".././styles/styles.css" />
      <link
        href="https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@100&family=Public+Sans:wght@100&family=Roboto:wght@300;400&display=swap"
        rel="stylesheet" />
      <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    </head>
    <body id="consultas">
      <div id="holder">
        <div id="body">
          <div class="w3-container w3-light-blue">
            <h1>Revisión de Consultas</h1>
          </div>
          <div id="page-blank-container">
            <h2>${title}</h2>
            <button id="regresar" onclick="window.close()"></button>
            <div id="text-container"> ${content} </div>
            <div id="request_id"></div>
            <div class="btn-form-container">
            <button type="submit" id="approve-query-btn" class="button.index-btn">ACEPTAR</button>
            <button type="submit" id="deny-btn" class="deny-btn">DENEGAR</button>
            </div>
    </div>
          </div>
        </div>
        <footer style="bottom: 0px">
          Sistema de Gestión de Recursos Humanos
        </footer>
      </div>
      <script type="module" src="../../../scripts/supervisory.js"></script>
    </body>
  </html>
  `);
    const request_Div = document.getElementById("request_id");
    request_Div.setAttribute("REQUEST", JSON.stringify(request));
}



