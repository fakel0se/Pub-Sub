echo "Installing dependencies...\n"
sudo apt install -y g++ cmake libuv1-dev libssl-dev
echo "Dependencies installed\n"

echo "-----------------------------\n"

echo "Installing AMQP-CPP lib\n"
echo "Initing submodule AMQP-CPP\n"
git submodule init
git submodule update

if test -d build
then
  echo "\e[31mRemoving old 'build' directory\e[0m" 
  rm -rf build
fi

mkdir build
cd build

cmake ../src/AMQP-CPP/ -DAMQP-CPP_LINUX_TCP=ON -DAMQP-CPP_AMQBUILD_SHARED=OFF
sudo cmake --build . --target install

rm -rf * 
echo "AMQP-CPP installed\n"

echo "-----------------------------\n"
 
echo "Pub-Sub project installing...\n"
cmake ..
cmake --build .
echo "FINISH"
