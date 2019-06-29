# Simple Pub-Sub Example
This example have 2 entity:  
* Publisher. Publish a message;  
* Subscriber. Get message from queue.

# Install (easy way)
```
sh install.sh 
```

# Install (hard way)
## Install dependencies
* `g++`  
Debian/Ubuntu/Mint: `sudo apt install g++`
* `cmake`  
Debian/Ubuntu/Mint: `sudo apt install cmake`
* `libuv`  
Debian/Ubuntu/Mint: `sudo apt install libuv1-dev`
* `openssl`  
Debian/Ubuntu/Mint: `sudo apt install libssl-dev`
* `[AMQP-CPP](https://github.com/CopernicaMarketingSoftware/AMQP-CPP)`  
Debian/Ubuntu/Mint: 
```
git submodule init
git submodule update
mkdir build
cd build
cmake .. [-DAMQP-CPP_AMQBUILD_SHARED] [-DAMQP-CPP_LINUX_TCP]  # -DAMQP-CPP_AMQBUILD_SHARED=ON|OFF 
cmake --build . --tairget install
```

 Option                  | Default | Meaning
-------------------------|---------|-----------------------------------------------------------------------
 AMQP-CPP_BUILD_SHARED   | OFF     | Static lib(ON) or shared lib(OFF)? Shared is not supported on Windows.
 AMQP-CPP_LINUX_TCP      | OFF     | Should the Linux-only TCP module be built?


## Install
1) Clone repo to your PC.
2) Enter to project directory.
3) Create `build` directory.
4) Go to the folder `build`.
5) Execute `cmake .. && make`.

# Run
1) Start publisher `build/publisher`
2) Type user you want to message to
3) Send message
4) Start subcriber `build/subscriber`
5) Type your nickname
