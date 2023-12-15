#!/bin/bash

# Verify if the user has root privileges
if [ $UID -ne 0 ]; then
	echo "You don't have root privileges"
	exit 1
fi

# Compile and copy the executable to the /usr/bin so it will be accessible throughout
make && cp monty /usr/bin/monty

# Verify if it compiled successfully
if [ $? -eq 0 ]; then
	echo "Monty 0.99 installed successfully to /usr/bin"
else
	echo "Failed to compile. Please check the source code and try again."
fi


