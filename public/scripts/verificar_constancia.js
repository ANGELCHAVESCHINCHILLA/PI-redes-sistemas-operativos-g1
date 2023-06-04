document.addEventListener('DOMContentLoaded', function () {
    var buscarBtn = document.getElementById('buscarBtn');
    buscarBtn.addEventListener('click', buscarConstancia);

    function buscarConstancia() {
        var constanciaId = document.getElementById('constanciaId').value;
        console.log(constanciaId);
        var newWindow = window.open('');
        newWindow.document.write(constanciaId);
        // TODO: when DB API rest is up, change this to work
        /*
        fetch('', {
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
                }
            })
            .then(function(data) {
                // Crear una nueva pestaña y mostrar el contenido obtenido del fetch(constancia)
                var newWindow = window.open('');
                newWindow.document.write(data);
            })
            .catch(function(error) {
                console.error('Error al realizar la búsqueda:', error);
            });
    }
});

         */

    }
});