/*
 * =============================================================================
 *  Project      : Line Follower Robot
 *  File         : LineFollower.ino
 *  Authors      : Fakhridin A. <220107084@stu.sdu.edu.kz>;
 *                 Yerdaulet O. <220107038@stu.sdu.edu.kz>; 
 *                 Yedil S. <220107011@stu.sdu.edu.kz>;
 *  Supervisor   : Binara Imankulova <binara.imankulova@sdu.edu.kz>
 *  Finished on  : May 15, 2025
 *  Description  : Smart line-following robot using IR sensors and motor control.
 * 
 *  License      : SDU License
 *                 Permission is hereby granted, free of charge, to any person 
 *                 obtaining a copy of this software and associated documentation 
 *                 files (the "Software"), to deal in the Software without restriction,
 *                 including without limitation the rights to use, copy, modify, 
 *                 merge, publish, distribute, sublicense, and/or sell copies of the 
 *                 Software, and to permit persons to whom the Software is furnished 
 *                 to do so, subject to the following conditions:
 * 
 *                 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * =============================================================================
 */

#define LEFT_MOTOR_SPEED 180
#define RIGHT_MOTOR_SPEED 180
#define BLACK_THRESHOLD 300
#define SENSOR_COUNT 4

// Motor Pins
const int enableRightMotor = 6;
const int rightMotorPin1 = 7;
const int rightMotorPin2 = 8;

const int enableLeftMotor = 5;
const int leftMotorPin1 = 9;
const int leftMotorPin2 = 10;

class Sensor {
public:
  explicit Sensor(int analogPin) : pin(analogPin) {}

  int read() const {
    return analogRead(pin);
  }

  bool isBlack() const {
    return read() > BLACK_THRESHOLD;
  }

private:
  int pin;
};

class MotorDriver {
public:
  MotorDriver(int enPin, int pin1, int pin2)
    : enablePin(enPin), controlPin1(pin1), controlPin2(pin2) {}

  void setup() const {
    pinMode(enablePin, OUTPUT);
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
  }

  void setSpeed(int speed) const {
    if (speed < 0) {
      analogWrite(controlPin1, 0);
      analogWrite(controlPin2, abs(speed));
    } else if (speed > 0) {
      analogWrite(controlPin1, abs(speed));
      analogWrite(controlPin2, 0);
    } else {
      analogWrite(controlPin1, 0);
      analogWrite(controlPin2, 0);
    }
    analogWrite(enablePin, abs(speed));
  }

private:
  int enablePin;
  int controlPin1;
  int controlPin2;
};

// Instantiate Motors
MotorDriver leftMotor(enableLeftMotor, leftMotorPin1, leftMotorPin2);
MotorDriver rightMotor(enableRightMotor, rightMotorPin1, rightMotorPin2);

// Instantiate Sensors
Sensor sensors[SENSOR_COUNT] = {
  Sensor(A0), // Left Outer
  Sensor(A1), // Left Center
  Sensor(A2), // Right Center
  Sensor(A3)  // Right Outer
};

enum class RobotState {
  Forward,
  LeftTurn,
  RightTurn,
  Stop
};

RobotState currentState = RobotState::Stop;

RobotState determineState(const bool sensorStates[SENSOR_COUNT]) {
  if (sensorStates[0] && sensorStates[1] && sensorStates[2] && sensorStates[3]) {
    return RobotState::Forward;
  } else if (sensorStates[0]) {
    return RobotState::LeftTurn;
  } else if (sensorStates[3]) {
    return RobotState::RightTurn;
  } else if (!sensorStates[0] && !sensorStates[1] && !sensorStates[2] && !sensorStates[3]) {
    return RobotState::Forward;
  } else {
    return RobotState::Stop;
  }
}

// Motion Control
void rotateMotors(int leftSpeed, int rightSpeed) {
  leftMotor.setSpeed(leftSpeed);
  rightMotor.setSpeed(rightSpeed);
}

void setup() {
  Serial.begin(9600);
  TCCR0B = TCCR0B & B11111000 | B00000010; // Timer prescaler adjustment

  leftMotor.setup();
  rightMotor.setup();

  rotateMotors(0, 0); // Stop initially
}

void loop() {
  bool isBlack[SENSOR_COUNT];
  for (int i = 0; i < SENSOR_COUNT; i++) {
    isBlack[i] = sensors[i].isBlack();
  }

  currentState = determineState(isBlack);

  switch (currentState) {
    case RobotState::Forward:
      rotateMotors(LEFT_MOTOR_SPEED, RIGHT_MOTOR_SPEED);
      break;
    case RobotState::LeftTurn:
      rotateMotors(-LEFT_MOTOR_SPEED, RIGHT_MOTOR_SPEED);
      if (!isBlack[1]) delay(500);
      break;
    case RobotState::RightTurn:
      rotateMotors(LEFT_MOTOR_SPEED, -RIGHT_MOTOR_SPEED);
      if (!isBlack[2]) delay(500);
      break;
    case RobotState::Stop:
      rotateMotors(0, 0);
      break;
  }

  delay(100);
}