mkdir build
cd build
cmake ../ -G "CodeBlocks - Unix Makefiles"
make 
sudo chmod 777 /dev/ttyUSB0(NOTE:please select correct serial in “app\node.cpp "/dev/ttyUSB0"”)
./delta_lidar_node
