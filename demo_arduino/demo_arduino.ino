// Adapted from https://howtomechatronics.com/tutorials/Arduino/how-to-track-orientation-with-Arduino-and-adxl345-accelerometer/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;

void setup(void) {
  Serial.begin(19200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Searching for Adafruit MPU6050");

  // Try to initialize!
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(1000);
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(a.acceleration.y / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2))) * 180 / PI;
  pitch = atan(-1 * a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2))) * 180 / PI;

  // Low-pass filter
  rollF = 0.94 * rollF + 0.06 * roll;
  pitchF = 0.94 * pitchF + 0.06 * pitch;

  // print to Serial (this is what is read in the processing ide code)
  Serial.print(rollF);
  Serial.print("/");
  Serial.println(pitchF);

}
