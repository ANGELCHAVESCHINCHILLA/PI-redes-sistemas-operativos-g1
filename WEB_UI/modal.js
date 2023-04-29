const openModal_btn = document.getElementById('realizar-solicitud-btn'); // open modal button
const closeModal_btn = document.getElementById('close-modal'); // close modal button
const modal = document.getElementById('solicitudes_modal'); // modal per se

/** Listeners */

// When click to open modal
openModal_btn.addEventListener('click', function() {
  modal.style.display = 'flex';
});

// When click to close modal
closeModal_btn.addEventListener('click', function() {
  modal.style.display = 'none';
});

// When click to open vacations form
const realizarSolicitudBtn = document.getElementById('vacaciones-btn'); // get by id
if (realizarSolicitudBtn) {
  realizarSolicitudBtn.addEventListener('click', function () {
    window.location.href = 'form_solicitar_vacaciones.html'; // redirect
  });
}
