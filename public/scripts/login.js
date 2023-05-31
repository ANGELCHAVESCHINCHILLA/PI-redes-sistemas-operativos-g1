const login = document.getElementById("login"); // get by id

if (login) {
    login.addEventListener('submit', function (event) {
      event.preventDefault(); // Avoid default shipment
  
      const username = login.elements['username'].value;
      const password = login.elements['password'].value;
  
      if (username && password) { // Check if exists

        // // Crear un objeto con los datos que deseas enviar
        // var userValidationInfo = {
        //   username: username,
        //   password: password
        // };

        // // Realizar la solicitud POST utilizando fetch()
        // fetch("/login", {
        //   method: "POST",
        //   headers: {
        //     "Content-Type": "application/json"
        //   },
        //   body: JSON.stringify(userValidationInfo)
        // })

        // .then(function(response) {
        //   if (response.ok) {
        //     // La solicitud se completó con éxito
        //     return response.text();
        //   } else {
        //     // Ocurrió un error en la solicitud
        //     throw new Error(response.status);
        //   }
        // })

        // .then(function(responseText) {
        //   console.log(responseText);
        // })
        // .catch(function(error) {
        //   console.error(error);
        // });

        window.location.href = 'index.html'; // redirection
        //window.location.href = 'form_solicitar_vacaciones.html'; // Redirige a otra página
      } else {
        alert('Por favor complete todos los campos'); // 
      }
    });
  }
