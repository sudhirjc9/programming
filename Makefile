.PHONY: clean

# Define the default shell to use
SHELL := /bin/bash

# Target to clean executable files in subdirectories
clean:
	@echo "Searching for and removing executable files in all subdirectories..."
	# Find all regular files (-type f) that are executable (-executable)
	# and then delete them. The -delete option is more efficient.
	# If -delete is not supported or you prefer, you can use:
	# find . -type f -executable -exec rm -f {} +
	find . -type f -executable -delete
	@echo "Executable file cleanup complete."

# Optional: Add a target to build executables if you have a build process
# all:
# 	@echo "Building projects (if any)..."
# 	# Example: Traverse into subdirectories and run 'make'
# 	# find . -maxdepth 1 -mindepth 1 -type d -print0 | xargs -0 -I {} bash -c 'cd {} && make'
