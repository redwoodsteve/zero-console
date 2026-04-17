# Lua Console
A console which uses the RPi Zero 2 W
## setup
-Make sure to set the username and password of your pi lite image to "pi"!
-cd into `software`, and run `sudo ./setup.sh`. You should also probably turn on auto login.
## software
The folder which houses the software, such as the home screen. Basically all of this code is in C++ for a low memory footprint and stuff.<br>
**Development:**<br>
For `launcher`:
 - For windows, install MinGW64, open the UCRT64 console, CD into the launcher directory and use `make`
 - For linux, CD into the launcher directory and `make`<br>
 - Make sure to install dependencies `sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxi-dev libxcursor-dev`
 
For `games`:
 - put any files you need for any games you add in here
 - make sure to add games to `launcher/games.json`
## assets
Common assets (textures, sounds, etc) to use throughout
## hardware
The folder where you can find KiCad files, the BOM (LCSC parts) and JLCPCB files.<br>
**Development:**<br>
Probably just send suggestions as pull requests, idk how I would set up a kicad project with github like this.<br>
**Getting a PCB:**<br>
You can easily upload the `production/Zero_Console.zip` file to JLCPCB and you will be able to produce it for **$2** for five!<br>
**Parts:**<br>
You can upload the bom.csv file to LCSC and it will automatically find the parts.
For the display, [this one](https://a.co/d/03g2Kwg4) ($17) works well and is pretty cheap, but they're all the same chinese models.<br>
You'll also need some pin headers for the display and pi.<br>
And of course, you'll need a raspberry pi zero 2 w (without headers).<br>
**Assembly**<br>
Load up the PCB in kicad, and start soldering the parts to the board.