
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

class FormBuilder {
    constructor() {
      this.fields = [];
    }
  
    addTextField(name, label) {
      this.fields.push(new TextField(name, label));
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
        this.fields.push(new DateField(name, label))
        return this;
    }
  
    build() {
      const form = new Form();
  
      this.fields.forEach(field => {
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
      const form = document.createElement('form');
  
      this.fields.forEach(field => {
        form.appendChild(field.render());
      });
  
      return form;
    }
  }
  
  class TextField {
    constructor(name, label) {
      this.name = name;
      this.label = label;
    }
  
    render() {
      const field = document.createElement('div');
      field.className = 'form-field';
  
      const label = document.createElement('label');
      label.innerHTML = this.label;
  
      const input = document.createElement('input');
      input.type = 'text';
      input.name = this.name;
  
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
      const field = document.createElement('div');
      field.className = 'form-field';
  
      const label = document.createElement('label');
      label.innerHTML = this.label;
  
      const input = document.createElement('input');
      input.type = 'email';
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
      const field = document.createElement('div');
      field.className = 'form-field';
  
      const label = document.createElement('label');
      label.innerHTML = this.label;
  
      const input = document.createElement('input');
      input.type = 'password';
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
      const field = document.createElement('div');
      field.className = 'form-field';
    
      const label = document.createElement('label');
      label.innerHTML = this.label;
    
      const input = document.createElement('input');
      input.type = 'checkbox';
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
      const field = document.createElement('div');
      field.className = 'form-field';
    
      const label = document.createElement('label');
      label.innerHTML = this.label;
    
      const select = document.createElement('select');
      select.name = this.name;
    
      this.options.forEach(option => {
        const opt = document.createElement('option');
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
      const field = document.createElement('div');
      field.className = 'form-field';
    
      const label = document.createElement('label');
      label.innerHTML = this.label;
    
      const input = document.createElement('input');
      input.type = 'date';
      input.name = this.name;
    
      field.appendChild(label);
      field.appendChild(input);
    
      return field;
    }
  }
  
  