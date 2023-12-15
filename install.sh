#!/bin/bash

# Verify if the user has root privileges
if [ $UID -ne 0 ]; then
	echo "You don't have root privileges"
	exit 1
fi

# Compile the source files
make 

# Verify if it compiled successfully
if [ $? -eq 0 ]; then
	# Copy the executable to the /usr/bin so it will be accessible throughout
	cp monty /usr/bin/monty
	# Install the man page
	cp monty.1 /usr/share/man/man1/monty.1
	# Update the man page database
	mandb
	# Remove all .c files
	make clean

	echo "Monty 0.99 installed successfully to /usr/bin"
	echo "Man page installed successfully"
else
	echo "Failed to compile. Please check the source code and try again."
fi
