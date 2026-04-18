#!/bin/bash
cd /home/pi/zero-console/software/launcher
sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxi-dev libxcursor-dev libgpiod-dev love matchbox-window-manager git-lfs
make

cd /home/pi/zero-console/software/drivers

cp -f launcher.service /etc/systemd/system/launcher.service
systemctl start launcher

cp -f shutdowngpio.service /etc/systemd/system/shutdowngpio.service
systemctl start shutdowngpio

cp -f Xwrapper.config /etc/X11/Xwrapper.config

systemctl daemon -reload

cd /home/pi/zero-console/software

cd /home/pi/
git lfs install
git clone https://github.com/katzenjens/lcd32.git
git lfs pull
cd lcd32
./install35.sh
cd /home/pi/zero-console/software
cp -f config.txt /boot/firmware/config.txt