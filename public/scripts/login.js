const login = document.getElementById("login"); // get by id

if (login) {
    login.addEventListener('submit', function (event) {
      event.preventDefault(); // Avoid default shipment
  
      const username = login.elements['username'].value;
      const password = login.elements['password'].value;
  
      if (username && password) { // Check if exists

        // Crear un objeto con los datos que deseas enviar
        var userValidationInfo = {
          username: username,
          password: password
        };

        // Envía los datos de usuario y contraseñ
        fetch('/login', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ username, password }),
        })
          // Si la respuesta tiene código de estado 200 entonces continúa, si no
          // lanza un error
          .then(response => {
            if (response.ok) {
              return response.json();
            } else {
              alert("El usuario y/o la contraseña son incorrectos");
            }
          })
          // Si viene con un token entonces redirigimos, si no lanzamos un error
          // en consola.
          .then(data => {
            const token = data.token;
            localStorage.setItem('token', token);
            window.location.href = 'index.html';
          })
          .catch(error => {
            // Manejar errores de autenticación
            console.log(error.message);
          });

        // window.location.href = 'index.html'; // redirection
        //window.location.href = 'form_solicitar_vacaciones.html'; // Redirige a otra página
      } else {
        alert('Por favor complete todos los campos'); // 
      }
    });
  }
