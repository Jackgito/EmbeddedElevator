# Embedded Elevator Project - Final Coursework

## **Project Overview**
This project is the final coursework for the **Introduction to Embedded Systems** course. The objective is to design and implement an **elevator control system** using an **Arduino MEGA (Master)** and an **Arduino UNO (Slave)**. The microcontrollers communicate via the **I2C protocol**, integrating peripherals such as an LCD, keypad, LEDs, and a buzzer to simulate real-world elevator functionality.

## **Core Functionalities**
### **1. Floor Selection via Keypad**
- Users enter a floor number (0-99) using a **4x4 keypad** connected to MEGA.
- The **LCD screen** displays the selected floor and elevator status in real-time.

### **2. Elevator Movement**
- The system processes floor requests and moves the elevator accordingly.
- A **movement LED** on UNO lights up when the elevator is in motion.
- The LCD screen updates the **current floor number** during movement.
- Elevator supports floor queue, meaning floor numbers can be entered while the elevator is moving, and will move according to queue.

### **3. Door Operation**
- Upon reaching the destination, the **door LED** turns on for **5 seconds** to simulate door opening.
- The LCD screen displays **"Door Open"** and **"Door Closed"** messages appropriately.

### **4. Emergency Handling**
- An **external emergency button** connected to MEGA allows users to stop the elevator during movement.
- When activated:
  - The LCD displays **"EMERGENCY"**.
  - The movement LED blinks **three times**.
  - The buzzer plays an emergency **melody**.
  - The door opens automatically.
- Enhanced emergency levels allow users to manually confirm door opening or keep the alarm active until deactivation.

### **5. Communication Between MEGA & UNO**
- **I2C communication** is used for data exchange between the two microcontrollers.
- MEGA sends commands to UNO, such as:
  - **Turning LEDs ON/OFF**.
  - **Activating the buzzer** for alerts.
  - **Handling door control events**.
- UNO receives and processes these commands to execute the appropriate actions.

## **Project Structure**
- **Master (MEGA):** Handles input (keypad), display (LCD), decision-making, and emergency handling.
- **Slave (UNO):** Controls movement indicators (LEDs), door mechanism, and buzzer alerts.

## **Group Members & Responsibilities**
| Name       | Responsibility                         |
|------------|----------------------------------|
| **Aleksi**  | Elevator movement control      |
| **Eliel**   | Emergency system & communication module |
| **Jericho** | Report (excluding circuit diagram) |
| **Juhani**  | Project codebase setup & live demonstration |
| **Niklas**  | Circuit diagram |

## **Circuit Diagram**
*To be added.*
