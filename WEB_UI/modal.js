const openModalBtns = document.querySelectorAll('.open-modal-btn'); // open modal buttons
const closeBtns = document.querySelectorAll('.close-modal-btn'); // close modal buttons
const modals = document.querySelectorAll('.modal'); // modals per se

// When click to open modal
openModalBtns.forEach(function(btn, index) {
  btn.addEventListener('click', function() {
    modals[index].style.display = 'flex';
  });
});

// When click to close modal
closeBtns.forEach(function(btn, index) {
  btn.addEventListener('click', function() {
    modals[index].style.display = 'none';
  });
});

// When click to open vacations form
const realizarSolicitudBtns = document.querySelectorAll('.vacaciones-btn'); // get by class
if (realizarSolicitudBtns) {
  realizarSolicitudBtns.forEach(function(btn) {
    btn.addEventListener('click', function () {
      window.location.href = 'form_solicitar_vacaciones.html'; // redirect
    });
  });
}

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
