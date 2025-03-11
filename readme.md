# Embedded Elevator Project - Final Coursework

### **Project Overview**
This project is the final coursework for the **Introduction to Embedded Systems** course. The goal is to design and implement an **elevator system** using an **Arduino MEGA (Master)** and an **Arduino UNO (Slave)**. The two microcontrollers communicate using the **I2C protocol**, and various components such as an LCD, keypad, LEDs, and a buzzer are integrated to simulate elevator functionality.

### **Core Functionalities**
1. **Floor Selection via Keypad:**
   - Users enter a floor number (0-99) using the keypad connected to MEGA.
   - The LCD displays the selected floor and elevator status.

2. **Elevator Movement:**
   - The system processes floor requests and moves the elevator accordingly.
   - A movement LED indicates when the elevator is in motion.

3. **Door Operation:**
   - The door LED turns on for 5 seconds when a floor is reached.
   - The LCD shows whether the door is open or closed.

4. **Emergency Handling:**
   - An external emergency button triggers an emergency stop.
   - The LCD displays "EMERGENCY," the buzzer plays a melody, and the door opens.

5. **Communication Between MEGA & UNO:**
   - I2C is used to send commands from MEGA to UNO (e.g., LED control, buzzer activation).
   - UNO processes these commands and executes the appropriate actions.

### **Group Members & Responsibilities**
- **Aleksi** – Elevator movement
- **Eliel** – Emergency System & Communication Module
- **Jericho** – Report (excluding circuit diagram)
- **Juhani** – Project codebase setup and live demonstration
- **Niklas** – Circuit diagram

### **Project Timeline & Checkpoints**
| Date  | Milestone |
|-------|------------|
| **18.3** | Circuit diagram and elevator movement draft completed |
| **25.3** | Individual module implementation finished |
| **5.4**  | Basic system integration (LCD, keypad, LEDs, movement) |
| **12.4** | Communication between MEGA & UNO functional |
| **19.4** | Emergency system and additional functionalities added |
| **26.4** | Full system testing and debugging |
| **3.5**  | Final refinements and optimization |
| **5.9**  | Project submission and demonstration |

### **Circuit Diagram**
- To be added

