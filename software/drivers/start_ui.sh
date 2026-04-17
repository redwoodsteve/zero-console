#!/bin/bash

# Start Matchbox in the background (no titlebars)
matchbox-window-manager -use_titlebar no &

# Launch your C++ menu
exec /home/pi/zero-console/software/launcher/launcher