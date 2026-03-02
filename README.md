It is quite a challenge to get started on building a new project for the ESP32-2432S028R using Platform IO.  Also, most examples I've found for the board include LVGL which I don't prefer for building basic informational displays.

Here are all the files you willl need for getting the ESP32-2432S028R working with Arduino GFX Library in PlatformIO.  Please let me know if you have any issues, hope this helps.

On my board I need to hold the BOOT button in order to get the flash initiated.

Choose lib + src  = basic display without touch library

OR

lib with touch + src with touch = display with touch capability

Credits:

https://github.com/moononournation/Arduino_GFX

https://github.com/PaulStoffregen/XPT2046_Touchscreen
