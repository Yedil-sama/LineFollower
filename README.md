# 🤖 Line Follower Robot

Smart line-following robot using IR sensors and motor control, developed as part of a robotics project under the supervision of Binara Imankulova at SDU. The robot is capable of detecting and following a black line using four IR sensors, with decision-making based on sensor inputs and a simple state-based motor control logic.

---

## 🛠️ Features

- 🚗 Line detection and navigation using 4 IR sensors
- 🔄 Motor control logic for left, right, forward movement and stop
- 🔌 PWM-based speed control for both motors
- 🧠 Modular code structure with encapsulated `Sensor` and `MotorDriver` classes
- ⚙️ Easily extendable to use state machine or strategy patterns
- 🪛 Built with Arduino C++ for compatibility with Uno, Nano, etc.

---

## 📁 Project Structure

<pre> 
   LineFollower 
   ├── LineFollower.ino # Main Arduino source file 
   ├── README.md # Project documentation
   └── LICENSE # SDU License (custom academic license) 
</pre>

---

## ⚙️ Hardware Requirements

- Arduino Uno / Nano / Mega
- 4 x IR Sensors (analog output)
- 2 x DC Motors with L298N Motor Driver
- Power Supply (Battery or USB)
- Chassis and Wheels

---

## 🔌 Pin Configuration

| Component         | Arduino Pin |
|-------------------|-------------|
| Left Motor EN     | D5          |
| Left Motor IN1    | D9          |
| Left Motor IN2    | D10         |
| Right Motor EN    | D6          |
| Right Motor IN1   | D7          |
| Right Motor IN2   | D8          |
| IR Sensor 1 (LO)  | A0          |
| IR Sensor 2 (LC)  | A1          |
| IR Sensor 3 (RC)  | A2          |
| IR Sensor 4 (RO)  | A3          |

---

## 🚦 Behavior Logic

The robot responds to sensor input with the following behavior:

- **All sensors on black** → Move forward
- **Left outer sensor detects black** → Turn left
- **Right outer sensor detects black** → Turn right
- **All sensors detect white** → Move forward (line re-acquisition)
- **Any ambiguous state** → Stop

---

## 🧪 How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/line-follower-robot.git
   cd line-follower-robot
Open LineFollower.ino in Arduino IDE.

Select the correct board and port.

Upload the sketch to your Arduino.

Place the robot on a black line over a white background and observe it follow the path.

👨‍💻 Authors
Fakhridin A. (@220107084@stu.sdu.edu.kz)

Yerdaulet O. (@220107038@stu.sdu.edu.kz)

Yedil S. (@220107011@stu.sdu.edu.kz)

Supervised by Binara Imankulova (@binara.imankulova@sdu.edu.kz)

📄 License
This project is licensed under the SDU License.
See the LICENSE file for details.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

⭐️ Contributions
This project was developed as part of a university coursework and is not actively maintained. Contributions are welcome for educational use or extensions.

📸 Gallery
![IMG_20250514_180850](https://github.com/user-attachments/assets/fb853859-5e6c-4c57-a441-8e86630e188a)


https://github.com/user-attachments/assets/ebd9751a-2c12-447a-bb18-216c4089e91d

