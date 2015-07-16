#ifndef PRINTER_H
#define PRINTER_H

//#include "logo.cpp"
//#include "qr.cpp"

static Adafruit_Thermal printer(36,33);

void printerPrint()
{
  /*
  printer.begin();
  delay(500);
  printer.println("In Autonomous!");
  delay(500);
  */
  printer.begin();
  delay(500);
  printer.justify('C'); 
  //printer.printBitmap(180, 182, logo);
  delay(5000);
  printer.boldOn();
  printer.print("FEAR THE ROOBOT!");
  printer.println(" ");
  printer.boldOff();  
  delay(500); 
  printer.underlineOn(); 
  printer.print("DATA:");
  printer.underlineOff();  
  printer.println(" ");
  delay(500);
  printer.justify('L'); 
  printer.print("Energy Usage: ");
  printer.print(1, DEC);
  printer.print(" Amp Seconds");
  printer.println(" ");
  delay(500);
  printer.justify('C');
  delay(200);
  printer.boldOn(); 
  printer.println("Have a good day!");
  printer.println(" ");
  printer.println("-From S.T.A.C.E.E.");
  printer.boldOff(); 
  printer.println(" ");
  printer.println("Check out our Facebook with");
  printer.println("the QR code below!");
  printer.println(" ");
  //printer.printBitmap(132, 132, qr);
}

#endif
