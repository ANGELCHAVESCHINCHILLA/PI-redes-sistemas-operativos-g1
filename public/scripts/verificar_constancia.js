document.addEventListener('DOMContentLoaded', function () {
    var buscarBtn = document.getElementById('buscarBtn');
    buscarBtn.addEventListener('click', buscarConstancia);
});

async function buscarConstancia() {
    const constanciaId = document.getElementById('constanciaId').value;
    // var newWindow = window.open('');
    // Make fetch
    const url = `/consultRequestsByID?id=${constanciaId}`;
    // const params = {id: constanciaId};
    // url.search = new URLSearchParams(params).toString();
    console.log(url);
     fetch(url, {
        method: 'GET',
    }).then(async response => {
        console.log("Status: " + response.status)
        if (response.status == 200) {
            let newWindow = window.open('');
            let pageHTML = formatResponseInfo(response.json());
            newWindow.document.write(pageHTML);
        } else {
            const errorText = await response.text();
            document.write(errorText);
        }
    }).catch(error => {
        console.log(error);
    })

}

function formatResponseInfo(responseJSON) {
    let page = "PlaceHolde Info";
    return page;
}
