ESP32 ↔ STM32 UART Communication via MQTT

This project demonstrates a complete communication pipeline:

MQTT → ESP32 → UART → STM32 → Action (LED / Motor)

1.The ESP32 subscribes to an MQTT topic and forwards commands over UART.
2.The STM32 receives, parses, and executes commands (LED control and stepper motor control).
3.Debug logs are printed using ITM (SWO) and Serial Monitor.

Hardware Used:
1. ESP32 Devkit
2. STM32F446RE Nucleo Board 

Hardware Connections 
UART Connection between ESP32 and STM32
ESP32 Pin	              STM32 Pin	
GPIO17 (TXD2)	          PA1(UART4_RX)	
GPIO16 (RXD2)	          PA0(UART4_TX)	
GND	                    GND

LED and Stepper Motor Pinouts on STM32
Pin	                    Function
PA5	                    LED output
PA6	                    Direction (DIR)
PA4	                    Step (STEP)

MQTT Configuration
Broker: broker.emqx.io
Port: 8084
Topic: revati/epicure/commands

Example Messages
led:on
led:off
motor:200:1

UART Protocol
Format
  <command>\n
Examples
  led:on\n
  led:off\n
  motor:200:1\n
Notes
\n (newline) is used as a delimiter.
STM32 processes data only after receiving newline.
Commands are ASCII strings.

Command Structure
1. LED Control
led:on   → Turn ON LED
led:off  → Turn OFF LED
2. Motor Control
motor:<steps>:<dir>
Parameter	              Description
steps	                  Number of steps
dir	                    Direction (0 or 1)

Output images are in Output_Images folder
Video proof is in Video folder
