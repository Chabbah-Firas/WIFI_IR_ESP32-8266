/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as SendDemo.
 *
 *  Copyright (C) 2020-2022  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  MIT License
 */
#include <Arduino.h>

//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>
#define IR_SEND_PIN              4  // D4
#define LED_BUILTIN         27
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */
 /* // A22 R21
uint16_t sAddress = 0x5583;
uint8_t sCommand = 0x90;
uint8_t sRepeats = 0;
  * 
  *
 // A22 R21
uint16_t sAddress = 0x5583;
uint8_t sCommand = 0x90;
uint8_t sRepeats = 0;
*/
// BLOC B A03 A21 R12
uint16_t sAddress = 0x5583;
uint8_t sCommand = 0x90;
uint8_t sRepeats = 0;

void loop() {
    /*
     * Print current send values
     */
    Serial.println();
    Serial.print(F("Send now: address=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" repeats="));
    Serial.print(sRepeats);
    Serial.println();

    Serial.println(F("Send NEC with 16 bit address"));
    Serial.flush();

    // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
    //IrSender.sendNEC(sAddress, sCommand, sRepeats);

    /*
     * If you must send a raw value directly like e.g. 0xCB340102, you have to use sendNECRaw()
     */
  //Serial.println(F("Send NECRaw 0x8800347"));
  //IrSender.sendNECRaw(0x8800347, sRepeats);
    /*
     * Increment send values
     * Also increment address just for demonstration, which normally makes no sense
     */
    //sAddress += 0x0101;
    //5sCommand += 0x11;
    sRepeats++;
    // clip repeats at 4
    if (sRepeats < 3) {
      IrSender.sendNEC(sAddress, sCommand, sRepeats);
      
    }else {sRepeats=5;}

    delay(10);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}
