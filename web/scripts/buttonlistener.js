import {
  openSolicitudesPage,
  showExpedientAnotations,
  showVacationsBalance,
  showBaseSalary,
  reloadRequests,
  toBackPage,
} from ".././scripts/app.js";

function addButtonClickListener(buttonId, clickHandler) {
  const button = document.getElementById(buttonId);
  if (button) {
    button.addEventListener("click", clickHandler);
  }
}

// Vacations button
addButtonClickListener("saldo-vacaciones-btn", showVacationsBalance);
// Salary button
addButtonClickListener("salario-base-btn", showBaseSalary);
// Expedient button
addButtonClickListener("expediente-btn", showExpedientAnotations);
// Requests button
addButtonClickListener("estado-soluciones-btn", openSolicitudesPage);

// Reload requests button
addButtonClickListener("reload-requests", reloadRequests);
// Back button
addButtonClickListener("regresar", toBackPage);
