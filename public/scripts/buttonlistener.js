import {
  openSolicitudesPage,
  showExpedientAnotations,
  showVacationsBalance,
  showBaseSalary,
  openRequestForm,
  reloadRequests,
  toBackPage,
} from ".././scripts/app.js";

function addButtonClickListener(buttonId, clickHandler, args) {
  const button = document.getElementById(buttonId);
  if (button) {
    if (args) {
      button.addEventListener("click", async () => {
        clickHandler(args);
      });
    } else {
      button.addEventListener("click", clickHandler);
    }
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

// Salary Form button
addButtonClickListener("salarial-btn", openRequestForm, "salarial-btn");
// Employment Certification Form button
addButtonClickListener("laboral-btn", openRequestForm, "laboral-btn");
// Payment Proof Form button
addButtonClickListener("pago-btn", openRequestForm, "pago-btn");
// Vacations Form button
addButtonClickListener("vacaciones-btn", openRequestForm, "vacaciones-btn");

// Reload requests button
addButtonClickListener("reload-requests", reloadRequests);
// Back button
addButtonClickListener("regresar", toBackPage);
