const login = document.getElementById("login"); // get by id
localStorage.setItem('logged', "false");
if (login) {
    login.addEventListener('submit', function (event) {
      event.preventDefault(); // Avoid default shipment

      const username = login.elements['username'].value;
      localStorage.setItem('username', username);

      const password = login.elements['password'].value;
  
      if (username && password) { // Check if exists

        // Crear un objeto con los datos que deseas enviar
        var userValidationInfo = {
          username: username,
          password: password
        };
        // TODO: encriptar el password
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
              localStorage.setItem('logged', "true");
              window.location.href = 'index.html';
              return response.json();
            } else {
              alert("El usuario y/o la contraseña son incorrectos");
            }
          })
          .catch(error => {
            // Manejar errores de autenticación
            console.log(error.message);
          });

      } else {
        alert('Por favor complete todos los campos'); // 
      }
    });
  }
