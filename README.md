# Embedded Elevator Project - Final Coursework

## **Project Overview**
This project is the final coursework for the **Introduction to Embedded Systems** course. The objective is to design and implement an **elevator control system** using an **Arduino MEGA (Master)** and an **Arduino UNO (Slave)**. The microcontrollers communicate via the **I2C protocol**, integrating peripherals such as an LCD, keypad, LEDs, and a buzzer to simulate real-world elevator functionality.

## **Core Functionalities**
### **1. Floor Selection via Keypad**
- Users enter a floor number (0-99) using a keypad connected to MEGA.
- The **LCD screen** displays the selected floor and elevator status in real-time.

### **2. Elevator Movement**
- The system processes floor requests and moves the elevator accordingly.
- A **movement LED** on UNO lights up when the elevator is in motion.
- The LCD screen updates the **current floor number** during movement.

### **3. Door Operation**
- Upon reaching the destination, the **door LED** turns on for **5 seconds** to simulate door opening.
- The LCD screen displays **"Door Open"** and **"Door Closed"** messages.

### **4. Emergency Handling**
- An **external emergency button** connected to MEGA allows users to stop the elevator during movement.
- When activated:
  - The LCD displays **"EMERGENCY"**.
  - The movement LED blinks **three times**.
  - The buzzer plays an emergency **melody**.
  - The door opens automatically, and then closes after few seconds.

### **5. Communication Between MEGA & UNO**
- **TWI communication** is used for data exchange between the two microcontrollers.
- MEGA sends commands to UNO that control the LEDs and the buzzer

## Image ##
![picture](https://github.com/user-attachments/assets/0866b3c5-1862-4b96-8c9d-32f67bfdc57b)

## **Circuit Diagram**
![image](https://github.com/user-attachments/assets/f1b9786a-95b2-47c5-b53a-627e0f3a39cd)

