# Handheld-Game-Device

A compact handheld gaming device with integrated games and a full menu system.

## Hardware Used

* Microcontroller:
    * Arduino Uno
* Displays:
    * 16x2 character LCD (For the menu and settings)
    * MAX7219 8x8 LED Dot Matrix Display (For rendering the game)
* Controls:
    * 5 Push buttons
* Power:
    * Power MB V2
 
## Libraries Used

* `OneButton`: Used for debouncing buttons and handling button presses such as long presses and double presses.
* `LedControl`: Used for controlling and customizing the MAX7219 8x8 Matrix Display.
* `LiquidCrystal`: Used for displaying text and customizing it on the 16x2 character LCD.

## How to Play

1. Power On: Connect the 9V to the Power MB V2.
2. Navigation: Use the down push button to navigate the menu.
3. Selection: Use the select button to confirm, select, and quit.
