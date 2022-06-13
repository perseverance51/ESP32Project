# HOW TO BUILD
---------------------------------

* Export ESP32 toolchains by running the following command in Linux terminal, 
  `export PATH=/your_path/toolchains/esp32/bin:$PATH`

* Export `IDF_PATH` by running the command, `export IDF_PATH=/your_path/LuaNode/LuaNode_Esp32/esp-idf/`,
  where `your_path` is the path your save LuaNode.

* Change directory to `LuaNode32`, and then compile the project, `./build.sh`. If `build.sh` is not executable,
  you need to change the file permissions, input `sudo chmod 777 build.sh`

# FIRMWARE
---------------------------------

The firmware we built in the firmware directory is for test. You can flash it 
to your device to test LuaNode. The flash address for the firmware we provided
is `0x1000`.
