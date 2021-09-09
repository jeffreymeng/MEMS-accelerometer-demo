// Adapted from https://howtomechatronics.com/tutorials/Arduino/how-to-track-orientation-with-Arduino-and-adxl345-accelerometer/
import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
Serial myPort;
String data="";
float roll, pitch;PImage altIndicator;
PImage frame;

void setup() {
  size (1280, 720, P3D);
  myPort = new Serial(this, "/dev/cu.usbmodem141301", 19200); // starts the serial communication
  myPort.bufferUntil('\n');  altIndicator = loadImage("attitude-indicator.png");
  frame = loadImage("frame.png");
  hint(ENABLE_DEPTH_SORT);
}
void draw() {
  translate(width/2, height/2);
  background(233);
  textSize(22);
  translate(0,0,100);
  image(frame, -250, -250, 500, 500);
  fill(0,0,0);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch), -100, 265);

  rotateZ(radians(-pitch));
  translate(0, roll*-2, 0);
  translate(0, 0, -100);

  image(altIndicator, -300, -300, 600, 600);

}

// Read data from the Serial Port
void serialEvent (Serial myPort) {
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {
      //--- Roll,Pitch in degrees
      roll = float(items[0]);
      pitch = float(items[1]);
    }
  }
}
