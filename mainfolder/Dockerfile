# Use a base image with C++ development tools
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . .

# Install any dependencies (if needed)

# Compile the C++ source files
RUN g++ -o myapp main.cpp # Adjust according to your project structure

# Command to run the application
CMD ["./myapp"]
