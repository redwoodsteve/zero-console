#!/bin/bash
cd /home/pi/zero-console/software/launcher
sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxi-dev libxcursor-dev libgpiod-dev
make

cd /home/pi/zero-console/software/drivers

cp -f drivers/launcher.service /etc/systemd/system/launcher.service
systemctl start launcher

cp -f drivers/shutdowngpio.service /etc/systemd/system/shutdowngpio.service
systemctl start shutdowngpio

cd /home/pi/
git clone https://github.com/katzenjens/lcd32.git
cd lcd32
./install35.sh
cd /home/pi/zero-console/software
cp -f config.txt /boot/firmware/config.txt