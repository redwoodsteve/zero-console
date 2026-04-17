#!/bin/bash
while true
do
	SHUTDOWNPIN=$(gpioget --numeric -l GPIO3)
	if ["$SHUTDOWNPIN" -eq 1]; then
		systemctl poweroff
		exit 0
	fi
	sleep 0.5
done