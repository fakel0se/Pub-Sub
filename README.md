#Simple Pub-Sub Example
This example have 2 entity:
Publisher - publish a message;
Subscriber - get message from queue

#Dependencies
Install `libuv`
*Debian/Ubuntu/Mint
`sudo apt install libuv1`

Download and install `AMQP_CPP` from
[https://github.com/CopernicaMarketingSoftware/AMQP-CPP](GitHub)

Install `cmake`
*Debian/Ubuntu/Mint
`sudo apt install cmake`

#Instruction:
1.Clone repo to your PC
2.Enter to project directory
3.Create `build` directory
4.Go to the folder `build`
5.Execute `cmake .. && make`

#Run
Start publisher `build/publisher`
Type user you want to message to.
Send message.
Start subcriber `build/subscriber`
Type your nickname.
