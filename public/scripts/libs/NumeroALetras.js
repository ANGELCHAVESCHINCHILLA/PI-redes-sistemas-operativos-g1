/**
 * ✨Magic✨ class that converts number into letters
 * @author: :eyes:
 */

class NumeroALetras {
    constructor() {
      this.unidades = ['', 'Uno', 'Dos', 'Tres', 'Cuatro', 'Cinco', 'Seis', 'Siete', 'Ocho', 'Nueve'];
      this.decenas = ['', 'Diez', 'Veinte', 'Treinta', 'Cuarenta', 'Cincuenta', 'Sesenta', 'Setenta', 'Ochenta', 'Noventa'];
      this.diecis = ['', 'Once', 'Doce', 'Trece', 'Catorce', 'Quince', 'Dieciséis', 'Diecisiete', 'Dieciocho', 'Diecinueve'];
      this.centenas = ['', 'Ciento', 'Doscientos', 'Trescientos', 'Cuatrocientos', 'Quinientos', 'Seiscientos', 'Setecientos', 'Ochocientos', 'Novecientos'];
    }
  
    convertir(numero) {
      let letras = '';
  
      if (numero == 0) {
        letras = 'Cero';
      } else if (numero < 0) {
        letras = 'Menos ' + this.convertir(Math.abs(numero));
      } else {
        if (numero >= 1000000) {
          letras = this.convertir(Math.floor(numero / 1000000)) + ' Millones ';
          numero %= 1000000;
        }
  
        if (numero >= 1000) {
          letras += this.convertir(Math.floor(numero / 1000)) + ' Mil ';
          numero %= 1000;
        }
  
        if (numero >= 100) {
          letras += this.centenas[Math.floor(numero / 100)] + ' ';
          numero %= 100;
        }
  
        if (numero >= 10 && numero <= 19) {
          letras += this.diecis[numero - 10] + ' ';
          numero = 0;
        } else if (numero >= 20 || numero == 10) {
          letras += this.decenas[Math.floor(numero / 10)] + ' ';
          numero %= 10;
        }
  
        if (numero > 0) {
          letras += this.unidades[numero] + ' ';
        }
      }
  
      return letras.trim();
    }
  }
  

  export { NumeroALetras as NAL};