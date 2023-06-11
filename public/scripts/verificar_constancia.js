document.addEventListener('DOMContentLoaded', function () {
    var buscarBtn = document.getElementById('buscarBtn');
    buscarBtn.addEventListener('click', buscarConstancia);
});

function buscarConstancia() {
    var constanciaId = document.getElementById('constanciaId').value;
    // var newWindow = window.open('');
    // Make fetch
    const url = new URL("http://127.0.0.1:8003/consultRequestsByID");
    const params = {id: constanciaId};
    url.search = new URLSearchParams(params).toString();
    console.log(url);
    const promise = fetch(url, {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        },
    }).then(response => {
        console.log("Status: " + response.status )
        if (response.status == 200) {
            let newWindow = window.open('');
            let pageHTML = formatResponseInfo(response.json());
            newWindow.write(pageHTML);
        } else {
             document.write(response.text());
        }
    }).catch(error => {
        console.log(error);
    })

}

function formatResponseInfo(responseJSON) {
    let page = "PlaceHolde Info";
    return page;
}
