/**
FormBuilder is a class that simplifies the process of creating HTML forms using the builder pattern.
It uses form fields classes defined below (starts line 74).
@class
@example
const form = new FormBuilder('my-form')
.addTextField('name', 'Nombre completo')
.addEmailField('email', 'Correo electrónico')
.addSelectField('gender', 'Género', ['Masculino', 'Femenino', 'No binario'])
.addCheckboxField('terms', 'Acepto los términos y condiciones')
.addDateField("fecha", "Fecha de ingreso")
.build();
@method addTextField - Adds a text field to the form
@method addEmailField - Adds an email field to the form
@method addPasswordField - Adds a password field to the form
@method addCheckboxField - Adds a checkbox field to the form
@method addSelectField - Adds a select field to the form
@method addDateField - Adds a date field to the form
@method build - Builds the form object
@param {string} name - The name of the form
@param {string} label - The label for the form
@returns {Object} form - The form object

@author David Cerdas / @SrDavidC
*/

export class FormBuilder {
  constructor() {
    this.fields = [];
  }

  addNumericField(name, label, isRequired) {
    this.fields.push(new NumericField(name, label, isRequired));
    return this;
  }

  addTextField(name, label, isRequired) {
    this.fields.push(new TextField(name, label, isRequired));
    return this;
  }
  addReadOnlyText(name, label, value) {
    this.fields.push(new TextReadOnlyField(name, label, value));
    return this;
  }

  addEmailField(name, label) {
    this.fields.push(new EmailField(name, label));
    return this;
  }

  addPasswordField(name, label) {
    this.fields.push(new PasswordField(name, label));
    return this;
  }

  addCheckboxField(name, label) {
    this.fields.push(new CheckboxField(name, label));
    return this;
  }

  addSelectField(name, label, options) {
    this.fields.push(new SelectField(name, label, options));
    return this;
  }
  addDateField(name, label) {
    this.fields.push(new DateField(name, label));
    return this;
  }

  addCancelButton(name, label) {
    this.fields.push(new CancelButton(name, label));
    return this;
  }

  addSubmitlButton(name, label, button_id) {
    this.fields.push(new SubmitButton(name, label, button_id));
    return this;
  }

  build() {
    const form = new Form();

    this.fields.forEach((field) => {
      form.addField(field);
    });

    return form.render();
  }
}

class Form {
  constructor() {
    this.fields = [];
  }

  addField(field) {
    this.fields.push(field);
  }

  render() {
    const form = document.createElement("form");

    this.fields.forEach((field) => {
      form.appendChild(field.render());
    });

    return form;
  }
}

class NumericField {
  constructor(name, label, isRequired) {
    this.name = name;
    this.label = label;
    this.isRequired = isRequired;
  }

  render() {
    const field = document.createElement("div");
    field.classList.add("form-field");

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "number";
    input.name = this.name;
    input.required = this.isRequired == true ? this.isRequired : false;

    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}

class TextField {
  constructor(name, label, isRequired) {
    this.name = name;
    this.label = label;
    this.isRequired = isRequired;
  }

  render() {
    const field = document.createElement("div");
    field.classList.add("form-field");

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "text";
    input.name = this.name;
    input.required = this.isRequired == true ? this.isRequired : false;
    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}

class TextReadOnlyField {
  constructor(name, label, value) {
    this.name = name;
    this.label = label;
    this.value = value;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "text";
    input.name = this.name;
    input.value = this.value;
    input.readOnly = true;

    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}

class EmailField {
  constructor(name, label) {
    this.name = name;
    this.label = label;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "email";
    input.name = this.name;

    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}

class PasswordField {
  constructor(name, label) {
    this.name = name;
    this.label = label;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "password";
    input.name = this.name;

    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}
class CheckboxField {
  constructor(name, label) {
    this.name = name;
    this.label = label;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "checkbox";
    input.name = this.name;

    field.appendChild(input);
    field.appendChild(label);

    return field;
  }
}
class SelectField {
  constructor(name, label, options) {
    this.name = name;
    this.label = label;
    this.options = options;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const select = document.createElement("select");
    select.name = this.name;

    this.options.forEach((option) => {
      const opt = document.createElement("option");
      opt.value = option;
      opt.text = option;
      select.appendChild(opt);
    });

    field.appendChild(label);
    field.appendChild(select);

    return field;
  }
}
class DateField {
  constructor(name, label) {
    this.name = name;
    this.label = label;
  }

  render() {
    const field = document.createElement("div");
    field.className = "form-field";

    const label = document.createElement("label");
    label.innerHTML = this.label;

    const input = document.createElement("input");
    input.type = "date";
    input.name = this.name;

    field.appendChild(label);
    field.appendChild(input);

    return field;
  }
}

class CancelButton {
  constructor(name, label) {
    this.name = name;
    this.label = label;
  }
  render() {
    const button = document.createElement("button");
    button.className = "cancel-btn";
    button.type = "cancel";
    button.textContent = this.label;
    return button;
  }
}

class SubmitButton {
  constructor(name, label, button_id) {
    this.name = name;
    this.label = label;
    this.button_id = button_id;
  }
  render() {
    const button = document.createElement("button");
    // button.className = "submit-btn";
    // button.type = "submit";
    button.textContent = this.label;
    button.id = this.button_id;
    return button;
  }
}
