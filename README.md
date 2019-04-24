# Simple Pub-Sub Example
This example have 2 entity:  
* Publisher. Publish a message;  
* Subscriber. Get message from queue.

## Dependencies
* `g++`  
Debian/Ubuntu/Mint: `sudo apt install g++`
* `cmake`  
Debian/Ubuntu/Mint: `sudo apt install cmake`
* `libuv`  
Debian/Ubuntu/Mint: `sudo apt install libuv1-dev`
* `openssl`  
Debian/Ubuntu/Mint: `sudo apt install libssl-dev`
* `AMQP_CPP`  
Download and install it from [GitHub](https://github.com/CopernicaMarketingSoftware/AMQP-CPP).

## Install
1) Clone repo to your PC.
2) Enter to project directory.
3) Create `build` directory.
4) Go to the folder `build`.
5) Execute `cmake .. && make`.

## Run
1) Start publisher `build/publisher`
2) Type user you want to message to
3) Send message
4) Start subcriber `build/subscriber`
5) Type your nickname
