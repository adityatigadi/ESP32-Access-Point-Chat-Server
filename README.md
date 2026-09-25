# ESP32-Access-Point-Chat-Server
A standalone Wi-Fi chat server built using an ESP32 with WebSocket communication.
# ESP32 Access Point Chat Server

A standalone wireless chat system built using only an ESP32 development board. The ESP32 creates its own Wi-Fi network and hosts a web-based chat application that allows multiple users to exchange messages without requiring an internet connection or external server.

---

## Features

* ESP32 acts as a Wi-Fi Access Point
* Built-in web server
* Real-time chat using WebSockets
* Supports multiple users
* No internet required
* No external hardware modules
* Only an ESP32 board is required

---

## Hardware Requirements

| Component                           | Quantity |
| ----------------------------------- | -------- |
| ESP32 Development Board             | 1        |
| USB Cable                           | 1        |
| Laptop/PC (for programming)         | 1        |
| Smartphone/Laptop (for chat access) | Optional |

---

## Software Requirements

* Arduino IDE
* ESP32 Board Package
* WebSockets Library

---

## Step 1: Install Arduino IDE

Download and install Arduino IDE:

* https://www.arduino.cc/en/software

---

## Step 2: Install ESP32 Board Package

1. Open Arduino IDE.
2. Go to:

```text
File → Preferences
```

3. In "Additional Boards Manager URLs", add:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

4. Click OK.

5. Open:

```text
Tools → Board → Boards Manager
```

6. Search:

```text
ESP32
```

7. Install:

```text
esp32 by Espressif Systems
```

---

## Step 3: Install WebSockets Library

Open:

```text
Sketch → Include Library → Manage Libraries
```

Search:

```text
WebSockets
```

Install:

```text
WebSockets by Markus Sattler
```

---

## Step 4: Create a New Project

1. Open Arduino IDE.
2. Create a new sketch.
3. Copy the ESP32 Chat Server code into the sketch.
4. Save the project.

Example:

```text
ESP32_Chat_Server
```

---

## Step 5: Select ESP32 Board

Open:

```text
Tools → Board → ESP32 Arduino → ESP32 Dev Module
```

Select the COM port:

```text
Tools → Port → COMx
```

---

## Step 6: Upload the Code

1. Connect the ESP32 using a USB cable.
2. Click Upload.

If uploading fails:

* Hold the BOOT button
* Press Upload again
* Release BOOT after connecting

---

## Step 7: Open Serial Monitor

Open:

```text
Tools → Serial Monitor
```

Set:

```text
115200 Baud
```

Example output:

```text
ESP32 CHAT SERVER
Access Point Started

Wi-Fi Name: ESP32_CHAT
Password: 12345678

IP Address:
192.168.4.1
```

---

## Step 8: Connect to ESP32 Wi-Fi

Open Wi-Fi settings on your phone or laptop.

Connect to:

```text
ESP32_CHAT
```

Password:

```text
12345678
```

---

## Step 9: Open the Chat Application

Open a browser and enter:

```text
http://192.168.4.1
```

The chat webpage will appear.

---

## Step 10: Connect Multiple Devices

Multiple devices can connect to the ESP32 network.

Example:

```text
Phone 1
Laptop
Phone 2
Tablet
```

All connected users can exchange messages.

---

## System Architecture

```text
          ESP32
             │
     Wi-Fi Access Point
             │
     Web Server + Chat
             │
   ┌─────────┼─────────┐
   │         │         │
 Phone    Laptop    Tablet
```

---

## Technologies Used

* ESP32
* Wi-Fi Access Point Mode
* HTTP Web Server
* WebSockets
* HTML
* CSS
* JavaScript
* Arduino IDE

---

## Applications

* Offline communication
* Smart classroom
* Emergency communication
* Local messaging system
* IoT networking experiments

---

## Advantages

* No internet required
* Low cost
* Portable
* Easy to implement
* No external hardware

---

## Future Improvements

* Usernames
* Message timestamps
* Chat history
* File sharing
* Encryption
* Password-protected chat rooms

---

## Author


