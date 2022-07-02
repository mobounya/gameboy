# GameBoy BUS Documentation
Here is an example of a computer following the _von Neumann_ architecture :
![enter image description here](https://thecustomizewindows.com/wp-content/uploads/2013/07/Von-Neumann-Architecture.jpg)
The BUS here is the communication channel between the different components of a computer.
For example if the CPU needs to read a value from memory, the address first is written to the address line by the CPU, then the value in memory is written to the data line, by the RAM.

This is a very basic model where the only 2 components in the computer are CPU and RAM.

But when we have multiple components, in the example of a Game Boy, we will have to give each of those components, a range of addresses, so they all can be reachable from each other.

![enter image description here](https://miro.medium.com/max/1400/1*MFBSlcKLb_emOENu-PvhPw.png)If you observer this memory mapping, you will find that not all these addresses point to the main RAM, some of them point into areas in the cartridge ROM, and some of them are used to read input.
