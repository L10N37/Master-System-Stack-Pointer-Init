// Stack pointer initilisation for after-market Master System cartridge adapters on Megadrive / Genesis
// Used Information from SMS power and Raphnet
// Vajskids Consoles 2021

#define wait_()   while (bitRead (PINB, 3) == 0) {;}  // wait for RD high again
#define wait()  while (bitRead (PINB, 3) == 1) {;}  // wait for RD low pulse


void setup() {

  // all outputs for bits 0:5
  DDRD = 0B11111100;
  // all outputs except RD/CLK pin as input, bits 6/7 not usable (mapped to xtal)
  DDRB = 0B00110111;
  //CE HIGH
  bitWrite (PORTB, 4, 1);
  // Setup first byte port B bits
  bitClear (PORTB, 0);
  bitClear (PORTB, 1);
  //Serial.begin (115200);
}


void complete() {
  //Serial.println (" PWR DOWN ");
  complete();
}


void loop() {
  wait()
  // present Initial byte and keep CE high
  //Serial.println (" Byte 1");
  //delay (500);
  PORTD = 0x84;
  //delay (500);
  wait_();

  //byte 2
  wait();
  //Serial.println (" Byte 2");
  //delay (500);
  PORTD = 0X4;
  //delay (500);
  wait_();

  //byte 3
  wait();
  //Serial.println (" Byte 3");
  //delay (500);
  bitWrite(PORTD, 7, 1);
  bitWrite (PORTB, 0, 1);
  bitWrite (PORTB, 1, 1);
  //delay (500);
  wait_();

  //byte 4
  wait();
  //Serial.println (" Byte 4");
  //delay (500);
  bitClear (PORTB, 0);
  bitClear (PORTB, 1);
  PORTD = 0x94;
  //delay (500);
  wait_();

  //byte 5
  wait();
  //Serial.println (" Byte 5");
  //delay (500);
  bitWrite (PORTB, 0, 1);
  bitWrite (PORTB, 1, 1);
  PORTD = 0xE4;
  //delay (500);
  wait_();

  //byte 6
  wait();
  //Serial.println (" Byte 6");
  //delay (500);
  PORTD = 0x1C;
  //delay (500);
  wait_();
  //Serial.println (" FINISHED ");
  // high-z everything
  DDRB = 0x00;
  DDRD = 0x00;
  PORTD = 0x00;
  PORTB = 0x00;
  // Serial.println (" HIGH-Z ");
  // finished
  complete();
}



/*
               D9/PB1 to D7
               D8/PB0 to D6
               D7/PD7 to D5
               D6/PD6 to D4
               D5/PD5 to D3
               D4/PD4 to D2
               D3/PD3 to D1
  Arduino      D2/PD2 to D0              SMS


                        Then 5v and GND

  0x21 | 00100001
  0x01 | 00000001
  0xE1 | 11100001
  0x25 | 00100101
  0xF9 | 11111001
  0xC7 | 11000111
*/
