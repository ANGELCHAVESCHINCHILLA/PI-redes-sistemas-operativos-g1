const PEPPER = "Universidad de Costa Rica";

const login = document.getElementById("login"); // get by id
// Used for validate the user in each page
localStorage.setItem('logged', "false");


if (login) {
  login.addEventListener('submit', async function (event) {
    event.preventDefault();
    
    // Read user name and password
    const username = login.elements['username'].value;
    localStorage.setItem('username', username);
    const password = login.elements['password'].value;

    if (username && password) {
      // sent request to get Salt
      const saltResponse = await fetch(`/auth/salt?username=${username}`, {
        method: 'GET'
      });

      if(!saltResponse.ok) {
        alert("El usuario y/o la contraseña son incorrectos");
      } else {
        const salt = await saltResponse.json();

        // Create hash with password and salt
        let hash = CryptoJS.SHA256(password + salt.salt + PEPPER)
        hash = hash.toString(CryptoJS.enc.Base64)
        hash = hash.substring(0, 15);
        
        // Create the JSON to be send to FS server
        const FSValidation =  {
          username: username,
          password: hash
        };
  
        // Send request to know if username and password are right
        const response = await fetch(`/login`, {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify(FSValidation),
        });
  
        if(!response.ok) {
          alert("El usuario y/o la contraseña son incorrectos");
        } else {
          // Send request to know the type of user (empleado, supervisor,...)
          const permissionsResponse =
            await fetch(`/permissions?username=${username}`, {
            method: 'GET'
          });
          const permissions = parseInt(await permissionsResponse.text());
          // If the user has permissions (is a empleado, supervisor, ...)
          if (permissions >= 0) {
            // Local storage for future usage
            localStorage.setItem('permissions', permissions)
            localStorage.setItem('logged', "true");
            // Go to index.html
            window.location.href = 'index.html';
          } else {
            alert("Su usuario no tiene permisos para acceder al sistema");
          }
        }
      }

    } else {
      alert('Por favor complete todos los campos'); // 
    }
  });
} else {
  console.log("No existe el login")
}
