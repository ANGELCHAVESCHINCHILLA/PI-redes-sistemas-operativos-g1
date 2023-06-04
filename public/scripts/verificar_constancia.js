document.addEventListener('DOMContentLoaded', function () {
    var buscarBtn = document.getElementById('buscarBtn');
    buscarBtn.addEventListener('click', buscarConstancia);

    function makeFetch(constanciaId) {
        fetch('/getConst', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ constanciaId: constanciaId })
        })
            .then(function(response) {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Error en la respuesta del servidor');
                    return null;
                }
            })
    }
    function formatInfo(info) {
        // TODO: finish this according info receiving from the fetch
        let formattedText;
        return formattedText;
    }
    function buscarConstancia() {
        var constanciaId = document.getElementById('constanciaId').value;
        var newWindow = window.open('');
        newWindow.document.write(constanciaId); // remove this when below TODO is ready
        // TODO: when DB API rest is up, change this to work
        /*
        let info = makeFetch(constanciaId);
        if (info) {
            formatInfo(info)
            newWindow.document.write(constanciaId);
        }

         */
    }
});