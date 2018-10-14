
#include <Servo.h>

const int pin_sound = 2;
const int pin_button_1 = 5;
const int pin_servo_pan = 11;
const int pin_servo_tilt = 12;
const int pin_eye_1 = 6;
const int pin_eye_2 = 7;
const int pin_ir = 8;

Servo servo_pan;
Servo servo_tilt;

void tilt_angle(int angle) {
  servo_tilt.attach(pin_servo_tilt);
  servo_tilt.write(angle);
  delay(500);
  servo_tilt.detach();
}
void pan_angle(int angle) {
  servo_pan.attach(pin_servo_pan);
  servo_pan.write(angle);
  delay(500);
  servo_pan.detach();
}

void eyeblink(int millisec) {
  int counter = 0;
  while (counter < millisec / 50) {
    digitalWrite(pin_eye_1, LOW);
    digitalWrite(pin_eye_2, LOW);

    delay(10);
    digitalWrite(pin_eye_1, HIGH);
    digitalWrite(pin_eye_2, HIGH);
    delay(40);
    counter++;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pin_sound, OUTPUT);
  pinMode(pin_eye_1, OUTPUT);
  pinMode(pin_eye_2, OUTPUT);
  pinMode(pin_button_1, INPUT);
  pinMode(pin_ir, INPUT);
  digitalWrite(pin_sound, LOW);
  digitalWrite(pin_eye_1, LOW);
  digitalWrite(pin_eye_2, LOW);
  tilt_angle(5);
  pan_angle(10);

  Serial.println("Init done");
}

void scare_cycle() {
  int counter = 0;
  Serial.println("### START SCARE ###");
  Serial.println("Toggle sound");
  digitalWrite(pin_sound, HIGH);
  delay(100);
  digitalWrite(pin_sound, LOW);
  servo_tilt.attach(pin_servo_tilt);
  servo_pan.attach(pin_servo_pan);

  digitalWrite(pin_eye_1, HIGH);
  digitalWrite(pin_eye_2, HIGH);
  servo_pan.write(100);
  servo_tilt.write(90);

  eyeblink(3000);
  servo_pan.write(120);
  servo_tilt.write(100);

  eyeblink(3000);
  servo_pan.write(90);
  servo_tilt.write(90);

  eyeblink(3000);



  delay(100);

  servo_tilt.write(5);
  servo_pan.write(10);


  Serial.println("Toggle sound");
  digitalWrite(pin_sound, HIGH);
  delay(100);
  digitalWrite(pin_sound, LOW);

  delay(500);
  digitalWrite(pin_eye_1, LOW);
  digitalWrite(pin_eye_2, LOW);

  servo_tilt.detach();
  servo_pan.detach();
  Serial.println("### END SCARE ###");

}

void loop() {
  int buttonVal = digitalRead(pin_button_1);
  if (buttonVal == HIGH) {
    Serial.println("Button pressed.");
    scare_cycle();
  }
  int irVal = digitalRead(pin_ir);


  if (irVal == HIGH) {
    Serial.println("IR triggered.");
    scare_cycle();
  }

  delay(100);
}
