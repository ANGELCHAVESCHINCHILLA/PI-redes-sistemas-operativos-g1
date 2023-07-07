document.addEventListener('DOMContentLoaded', function () {
    var buscarBtn = document.getElementById('buscarBtn');
    buscarBtn.addEventListener('click', buscarConstancia);
});

async function buscarConstancia() {
    const constanciaId = document.getElementById('constanciaId').value;
    const url = `/consultRequestsByID?id=${constanciaId}`;
     fetch(url, {
        method: 'GET',
    }).then(async response => {
        console.log("Status: " + response.status)
        if (response.status == 200) {

            const newWindow = window.open('');
            const pageHTML = await formatResponseInfo(await response.json());

            const divContainer = newWindow.document.createElement('div');
            divContainer.classList.add('constancy_container');
            divContainer.style.display = 'flex';
            divContainer.style.justifyContent = 'center';
            divContainer.style.alignItems = 'center';

            const styleLink = newWindow.document.createElement('link');
            styleLink.rel = 'stylesheet';
            styleLink.href = '.././styles/styles.css';

            const contentDiv = newWindow.document.createElement('div');
            contentDiv.innerHTML = pageHTML;

            divContainer.appendChild(contentDiv);
            newWindow.document.head.appendChild(styleLink);
            newWindow.document.body.appendChild(divContainer);
        } else {
            const errorText = await response.text();
            document.write(errorText);
        }
    }).catch(error => {
        console.log(error);
    })

}
function parseState(stateNumber) {
    let stateST = "ESTADO DESCONOCIDO"
    if (stateNumber === 1) {
        stateSt = "APROBADO";
    } else if (stateNumber === 2) {
        stateSt = "DENEGADO";
    } else if (stateNumber === 3) {
        stateSt = "EN REVISIÓN";
    }
    return stateSt;
}

async function formatResponseInfo(responseJSON) {
    console.log(responseJSON);
    const stateNumber = responseJSON.state;
    const stateStr = parseState(stateNumber);
    let userInfo;
    const url = `/data/personal_data?user=${responseJSON.user}`;
    try {
        const response = await fetch(url, {
            method: 'GET',
        });
        const text = await response.text();
        console.log(text);
        const json = JSON.parse(text);
        userInfo = json;
    } catch (error) {
        console.error('Error fetching personal data:', error);
        userInfo = null;
    }
    console.log(userInfo);
    const text =
        `San José, Costa Rica <br>San Pedro, 7001<br><br>
    CONSTANCIA <br>
    <br>
    <br>
    Por medio de la presente, Guachis Company, hace constar que: <br>
    Nombre del titular: ${userInfo.employee_name}<br>
    Cargo:  Empleado<br>
    <br>
    <br>
    Para la constancia o solicitud de tipo: <strong> ${responseJSON.request_type}</strong>, se encuentra en categoría de
    <strong> ${stateStr} </strong>.Las labores y responsabilidades desempeñadas por ${userInfo.employee_name} incluyeron las actividades típicas
    del puesto:  ${userInfo.job_name}.  <br> Dicha solicitud, en caso de ser aprobada o denegada, recibió la retroalimentación por parte de altos
    cargos, a continuación presente:   " ${responseJSON.feedback} ".<br>
    A lo largo de su tiempo en nuestra institución/empresa, el titular se mostró como un colaborador dedicado y comprometido,
    aportando de manera significativa a nuestro equipo y a nuestros objetivos organizacionales.Sin embargo pedimos comprensión hacia el estado o retroalimentación recibida <br>
    Extendemos la presente constancia a petición del interesado(a) para los fines que el titular considere necesarios. <br>
    <br>
    Sin otro particular, nos despedimos cordialmente,<br><br>

        Atentamente,<br>
        <br>
        Altos cargos de la jefatura. <br>
        ID: ${responseJSON.ID}<br>
        Fecha y hora local: ${new Date()}
    `;
    return text;
}

