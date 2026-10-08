#include <Servo.h>

Servo servo9;
Servo servo10;
Servo servo11;

float panAngle = 90.0f;
float panSpeed = 0.0f;
float panTarget = 90.0f;

bool panning = false;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);

  servo9.attach(9);
  servo10.attach(10);
  servo11.attach(11);

  servo9.write(90);
  servo10.write(90);
  servo11.write(90);

  lastUpdate = millis();

  Serial.println("Commands: 90 90 90 | pan 150 15");
}

// Heading in degrees, speed in degrees/second
void pan(uint16_t heading, uint16_t speed) {
  panTarget = constrain(heading, 0, 180);
  panSpeed = speed;
  panning = (speed > 0);
  lastUpdate = millis();
}

void updatePan() {
  if (!panning) return;

  unsigned long now = millis();
  float dt = (now - lastUpdate) / 1000.0f;
  lastUpdate = now;

  float step = panSpeed * dt;

  if (panAngle < panTarget) {
    panAngle = min(panAngle + step, panTarget);
  }
  else {
    panAngle = max(panAngle - step, panTarget);
  }

  servo11.write((int)panAngle);

  if (panAngle == panTarget) {
    panning = false;
    Serial.println("Pan complete");
  }
}

void loop() {
  updatePan();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    int a, b, c;
    unsigned int heading, speed;

    if (sscanf(input.c_str(), "pan %u %u", &heading, &speed) == 2) {
      pan(heading, speed);

      Serial.print("Panning to ");
      Serial.print(panTarget);
      Serial.print(" at ");
      Serial.print(panSpeed);
      Serial.println(" deg/s");
    }
    else if (sscanf(input.c_str(), "%d %d %d", &a, &b, &c) == 3) {
      panning = false;


      // update these accordingly
      a = constrain(a, 0, 180);
      b = constrain(b, 0, 180);
      c = constrain(c, 0, 180);

      servo9.write(a);
      servo10.write(b);
      servo11.write(c);

      panAngle = a;

      Serial.print("Angles: ");
      Serial.print(a);
      Serial.print(" ");
      Serial.print(b);
      Serial.print(" ");
      Serial.println(c);
    }
    else {
      Serial.println("Invalid command");
    }
  }
}