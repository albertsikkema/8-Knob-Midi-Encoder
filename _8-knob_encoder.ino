// Ableton Controller by Albert Sikkema (2018)
// Feel free to use it for your own (non-commercial) projects
// 8 * encoder with push-switch

#include <Encoder.h>
#include <Bounce.h>

// Encoder 1 - 8: connected to interrupt-pins and ground
// enc_1: top-left --> enc_8: bottom-right
  Encoder enc_1(21, 22);
  Encoder enc_2(15, 20);
  Encoder enc_3(12, 14);
  Encoder enc_4(10, 11);
  Encoder enc_5(2, 3);
  Encoder enc_6(4, 5);
  Encoder enc_7(6, 7);
  Encoder enc_8(8, 9);

// Create Bounce objects for each button (pin, debounce time in ms)
// button0: top-left --> button8: bottom-right
  Bounce button0 = Bounce(26, 5);
  Bounce button1 = Bounce(25, 5); 
  Bounce button2 = Bounce(24, 5);  
  Bounce button3 = Bounce(23, 5);  
  Bounce button4 = Bounce(16, 5);
  Bounce button5 = Bounce(17, 5); 
  Bounce button6 = Bounce(18, 5);  
  Bounce button7 = Bounce(19, 5); 

// variable stores read values of encoders
  int value1; 
  int value2;
  int value3; 
  int value4;
  int value5; 
  int value6;
  int value7; 
  int value8;

// Set CC/Note Values for encoders
  int enc_1_send = 1;
  int enc_2_send = 2;
  int enc_3_send = 3;
  int enc_4_send = 4;
  int enc_5_send = 5;
  int enc_6_send = 6;
  int enc_7_send = 7;
  int enc_8_send = 8;

// Set CC/Note Values for buttons 
  int btn_1_send = 61; 
  int btn_2_send = 62; 
  int btn_3_send = 63; 
  int btn_4_send = 64; 
  int btn_5_send = 65; 
  int btn_6_send = 66; 
  int btn_7_send = 67; 
  int btn_8_send = 68;  

// Set Value for 
// variable previous value for comparison
long enc_1_previous  = -999;
long enc_2_previous = -999;
long enc_3_previous  = -999;
long enc_4_previous = -999;
long enc_5_previous  = -999;
long enc_6_previous = -999;
long enc_7_previous  = -999;
long enc_8_previous = -999;


byte button_previous; 

// set midi channel to send and receive messages: default == 1
const int ch = 1;

// store incoming midi messages from Ableton
int inc_Midi_pr1[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// set send velocity/value in send midi message
const int val = 127;
const int off = 0;

void setup() {

  // Listen to incoming CCs
usbMIDI.setHandleControlChange(OnControlChange);

 // Configure button pins for input mode with pullup resistors.
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);  
  pinMode(26, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}



void loop() {
// USB MIDI receive
  usbMIDI.read(); 

// read all encoders  
  value1 = enc_1.read();
  value2 = enc_2.read();
  value3 = enc_3.read();
  value4 = enc_4.read();
  value5 = enc_5.read();
  value6 = enc_6.read();
  value7 = enc_7.read();
  value8 = enc_8.read();

//Use constrain to prevent value from becoming >127 or <0
/*value1 = constrain(value1, 0, 127);
value2 = constrain(value2, 0, 127);
value3 = constrain(value3, 0, 127);
value4 = constrain(value4, 0, 127);
value5 = constrain(value5, 0, 127);
value6 = constrain(value6, 0, 127);
value7 = constrain(value7, 0, 127);
value8 = constrain(value8, 0, 127);
*/


// read all buttons
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();

  // Check each button for "falling" edge.(high to low --> connection to earth)
  // Midi Message (note/cc, velocity/value, midichannel)
  // midichannel is set as variable ch 
  if (button0.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_1_send, val, ch);  
  }
  if (button1.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_2_send, val, ch); 
  }
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_3_send, val, ch);  
  }
  if (button3.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_4_send, val, ch); 
  }
  if (button4.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_5_send, val, ch); 
  }
  if (button5.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_6_send, val, ch);  
  }
  if (button6.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_7_send, val, ch);  
  }
  if (button7.fallingEdge()) {
    usbMIDI.sendNoteOn(btn_8_send, val, ch);  
  }
 
  // Check each button for "rising" edge (low to high)
  if (button0.risingEdge()) {
    usbMIDI.sendNoteOff(btn_1_send, off, ch);  
  }
  if (button1.risingEdge()) {
    usbMIDI.sendNoteOff(btn_2_send, off, ch);  
  }
  if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(btn_3_send, off, ch);  
  }
  if (button3.risingEdge()) {
    usbMIDI.sendNoteOff(btn_4_send, off, ch);  
  }
  if (button4.risingEdge()) {
    usbMIDI.sendNoteOff(btn_5_send, off, ch);  
  }
  if (button5.risingEdge()) {
    usbMIDI.sendNoteOff(btn_6_send, off, ch); 
  }
  if (button6.risingEdge()) {
    usbMIDI.sendNoteOff(btn_7_send, off, ch);  
  }
  if (button7.risingEdge()) {
    usbMIDI.sendNoteOff(btn_8_send, off, ch); 
  }
 
 // compare encoders, if changed then send message 
  if (value1 != enc_1_previous) {    enc_1_previous = value1;    usbMIDI.sendControlChange(enc_1_send , value1, ch);  }
  if (value2 != enc_2_previous) {    enc_2_previous = value2;    usbMIDI.sendControlChange(enc_2_send , value2, ch);  }
  if (value3 != enc_3_previous) {    enc_3_previous = value3;    usbMIDI.sendControlChange(enc_3_send , value3, ch);  }
  if (value4 != enc_4_previous) {    enc_4_previous = value4;    usbMIDI.sendControlChange(enc_4_send , value4, ch);  }
  if (value5 != enc_5_previous) {    enc_5_previous = value5;    usbMIDI.sendControlChange(enc_5_send , value5, ch);  }
  if (value6 != enc_6_previous) {    enc_6_previous = value6;    usbMIDI.sendControlChange(enc_6_send , value6, ch);  }
  if (value7 != enc_7_previous) {    enc_7_previous = value7;    usbMIDI.sendControlChange(enc_7_send , value7, ch);  }
  if (value8 != enc_8_previous) {    enc_8_previous = value8;    usbMIDI.sendControlChange(enc_8_send , value8, ch);  }
  
  }
// What to do with incoming Midi??
void OnControlChange(byte channel, byte cc, byte value) {

  if (cc==enc_1_send) {
      inc_Midi_pr1[0] = value;
      }  
}
  
