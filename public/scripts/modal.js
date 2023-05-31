const openModalBtns = document.querySelectorAll(".open-modal-btn"); // open modal buttons
const closeBtns = document.querySelectorAll(".close-modal-btn"); // close modal buttons
const modals = document.querySelectorAll(".modal"); // modals per se

// When click to open modal
openModalBtns.forEach(function (btn, index) {
  btn.addEventListener("click", function () {
    modals[index].style.display = "flex";
  });
});

// When click to close modal
closeBtns.forEach(function (btn, index) {
  btn.addEventListener("click", function () {
    modals[index].style.display = "none";
  });
});

function openModal(modal) {
  modal.style.display = "flex";
}

function openSolicitudesModal() {
  var modal = document.getElementById("solicitudes_modal");
  openModal(modal);
}

function openConsultasModal() {
  var modal = document.getElementById("consultas_modal");
  openModal(modal);
}

/*
function testFunc() {
  const form = new FormBuilder('my-form')
  .addTextField('name', 'Nombre completo')
  .addEmailField('email', 'Correo electrónico')
  .addSelectField('gender', 'Género', ['Masculino', 'Femenino', 'No binario'])
  .addCheckboxField('terms', 'Acepto los términos y condiciones')
  .addDateField("fecha", "Fecha de ingreso")
  //.addPasswordField("pass", "Digite su contra rey")
  .build();

document.getElementById('form-container').appendChild(form);
}
*/
