# CAN frame generator and reader

The scripts used in this project can read and decode CAN frames. And this marks my entry into the CAN data bus and its application in the automotive industry.
It is possible to get the CAN frames using either a real CAN communication or a virtual CAN connection, or vCAN. Additionally, there is a script that takes user input and injects the frame.
The scripts' communication method is socketCAN, and they are written in C++.

## SocketCAN

The socketcan package is an implementation of CAN protocols (Controller Area Network) for Linux. 

The CAN socket API has been designed as similar as possible to the TCP/IP protocols to allow programmers, familiar with network programming, to easily learn how to use CAN sockets.

In this project, I use a virtual CAN interface which is the perfect solution to develop CAN nodes, without the need of a real physical CAN bus.

1. create a bash script with the following code

```bash
#!/bin/bash
# Make sure the script runs with super user privileges.
[ "$UID" -eq 0 ] || exec sudo bash "$0" "$@"
# Load the kernel module.
modprobe vcan
# Create the virtual CAN interface.
ip link add dev vcan0 type vcan
# Bring the virtual CAN interface online.
ip link set up vcan0

```
2. flag it as an executable: chmod +x

Just run this script to get the vcan0 virtual CAN interface on a Linux system

## CAN-utils
can-utils is a Linux specific set of utilities that enables Linux to communicate with the CAN network.

With CAN-utils, we can sniff, spoof and create our own CAN packets
```
    $ sudo apt-get update
    $ sudo apt-get install can-utils
```

## Build
And now the compilation and linking of the c++ program.
```
    $ make
```
- ./reader for reading incoming CAN frames
- ./send for sending a frame typed by the user

## View
```
    $ ./reader
```
- Testing in another terminal with :
```
    (Terminal 2) - $ cangen vcan0
```
to obtain :

	![alt text](https://i.ibb.co/c2VLSb5/number1.png)

- Testing in another terminal with :
```
    (Terminal 2) - $ ./send
```
to obtain :

	![alt text](https://i.ibb.co/98RYb2c/number2.png)

## License

[Mohamed Aziz Tmar](https://www.linkedin.com/in/tmar-med-aziz/)
