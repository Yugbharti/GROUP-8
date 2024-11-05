# Use the official GCC image to compile C++ programs
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the C++ source code into the container
COPY . .

# Install make (required to compile C++ code with Makefile, if needed)
RUN apt-get update && apt-get install -y make

# Compile the C++ source code
RUN g++ -o hospital_management_system SourceCode.cpp

# Set the default command to run the application
CMD ["./hospital_management_system"]
