# Simple Pub-Sub Example
This example have 2 entity:  
* Publisher. Publish a message;  
* Subscriber. Get message from queue.

## Dependencies
* `libuv`
Debian/Ubuntu/Mint: `sudo apt install libuv1-dev`
* `g++`
Debian/Ubuntu/Mint: `sudo apt install g++`
* `openssl`
Debian/Ubuntu/Mint: `sudo apt install libssl`
* `cmake`
Debian/Ubuntu/Mint: `sudo apt install cmake`
* `AMQP_CPP`
Download and install it from [GitHub](https://github.com/CopernicaMarketingSoftware/AMQP-CPP).

## Install
1) Clone repo to your PC.
2) Enter to project directory.
3) Create `build` directory.
4) Go to the folder `build`.
5) Execute `cmake .. && make`.

## Run
Start publisher `build/publisher`.

Type user you want to message to.

Send message.

Start subcriber `build/subscriber`.

Type your nickname.
