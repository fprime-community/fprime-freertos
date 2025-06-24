# fprime-freertos

## Overview

Welcome to fprime-freertos, a port that connects the Operating System Abstraction Layer (OSAL) of the <a href="https://fprime.jpl.nasa.gov/">F' Flight Software Framework</a> with the <a href="https://www.freertos.org/">FreeRTOS</a> open-source RTOS for microcontrollers and small microprocessors. This repository is designed to be paired with platform and board specific repositories to run F' systems on a variety of boards. If the board you are trying to run fprime-freertos on already has a reference application and platform repository, I recommend starting there. The instructions below can help you get started using this port on a board that hasn't been used before and over time you can build and contribute your own board/platform/reference repositories. For more detail, see the relevant repositories for the featherm4-freertos platform:

- <a href=https://github.com/fprime-community/fprime-featherm4-freertos-reference>fprime-featherm4-freertos-reference</a> - an example of a basic build using a specific platform
    - <a href=https://github.com/fprime-community/fprime-featherm4-freertos>fprime-featherm4-freertos</a> - a platform repository which is defined by a combination of board and OS
        - <a href=https://github.com/fprime-community/fprime-arduino>fprime-arduino</a> - board-specific platform/toolchain/driver files
        - fprime-freertos (this repository) - a port connecting the F' OSAL to FreeRTOS
 
While fprime-freertos should be able to be used on a wide variety of systems, it has so far been tested with Linux and ATSAMD51J19 (specifically, the <a href=https://www.adafruit.com/product/3857>Adafruit Feather M4</a>). 

Platform and Toolchain files used to exist in this repository and you can dig them up from commit history to target an M4 board or a linux environment, but the reference repository listed above is the newer way of getting started. The rest of this README is out of date but may still be useful in the future.

The rest of this README will provide detailed setup instructions for a Linux platform build (Section 1) and a featherM4 build (Section 2). Before proceeding, make sure fprime and all of the system requirements are met by following the instructions specified on the <a href=https://fprime.jpl.nasa.gov/latest/getting-started/installing-fprime>Installing F'</a> page or by using the following steps as a guide:

- F' requires Linux, macOS, or WSL on Windows. Here are the details on how I setup my WSL on Windows environment with F'
    - Open Powershell in administrator mode
    - Run Powershell command to install wsl 
        ```sh
        wsl --install
        ```
    - Restart machine
    - Open Powershell in administrator mode
    - Run Powershell command to configure wsl
        ```sh
        wsl --set-default-version 1
        ```
        - If you get an error message stating WSL 1 isn’t supported, go to Control Panel -> Programs -> Programs and Features -> Turn Windows Features on or off -> Select box for WSL -> Press Ok -> restart -> rerun set default command above
    - Run WSL and get linux terminal
    - Run Linux command 
        ```sh
        sudo apt update && sudo apt upgrade
        ```
    - Run Linux command to install git
        ```sh 
        sudo apt install git
        ```
    - Run Linux command to install cmake
        ```sh
        sudo apt install cmake
        ```
    - Run Linux command to install clang
        ```sh
        sudo apt install clang
        ```
    - Run Linux command and ensure python version 3.8+ is installed
        ```sh
        python3 --version
        ```
    - Run Linux command to install pip
        ```sh
        sudo apt install python3-pip
        ```
    - Run Linux command to install venv
        ```sh
        sudo apt install python3-venv
        ```
    - Create a top level directory to contain the virtual environment and F' project directories
        ```sh
        mkdir fprime_freertos_example
        ```
    - Change your working directory to the newly created top level directory
        ```sh
        cd fprime_freertos_example
        ```
    - Create a virtual environment
        ```sh
        python3 -m venv fprime-venv
        ```
    - Activate virtual environment. Note: anything done past this point needs the fprime-venv activated.
        ```sh
        . fprime-venv/bin/activate
        ```
    - Install fprime-tools
        ```sh
        pip install fprime-tools
        ```
    - Install fprime-bootstrap
        ```sh
        pip install fprime-bootstrap
        ```



## Section 1: Linux Setup Procedure

For this section, we will adapt the <a href=https://fprime.jpl.nasa.gov/latest/tutorials-math-component/docs/math-component>MathComponent Tutorial</a> provided with the F' Framework to work with FreeRTOS in a linux environment.

- Clone the MathComponent Tutorial Project and ensure it runs without modification
    - Clone the project repository
        ```sh
        fprime-bootstrap clone https://github.com/fprime-community/fprime-tutorial-math-component.git
        ```
    - Change your working directory to the newly cloned project directory
        ```sh
        cd fprime-tutorial-math-component
        ```
    - Generate F' build files
        ```sh
        fprime-util generate
        ```
    - Build MathDeployment
        ```sh
        fprime-util build
        ```
    - Run the binary and launch the F' Ground Data System
        ```sh
        fprime-gds
        ```
    - Navigate to <a href=http://127.0.0.1:5000>http://127.0.0.1:5000</a> in a browser or wherever the terminal output shows the GDS UI is available
    - Send a few commands and make sure event and channelized telemetry are updating

- Add FreeRTOS
    - Add the fprime-freertos repository as a submodule
        ```sh
        git submodule add https://github.com/fprime-community/fprime-freertos.git
        ```
    - Add FreeRTOS kernel as a submodule
        ```sh
        git submodule add https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        ```
    - Open the project directory in the IDE of your choosing. Open the `settings.ini` file and add the following line:
        ```.ini
        library_locations: ./fprime-freertos
        ```
    - In the project-level CmakeLists.txt (i.e. /fprime-tutorial-math-component/CmakeLists.txt) add these lines after `project(fprime-tutorial-math-component C CXX)`:
        ```.txt
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/port.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/MemMang/heap_4.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/tasks.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/list.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/queue.c")
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/timers.c")

        include_directories("${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix")
        include_directories("${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils")
        include_directories("${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/include")

        add_compile_definitions(_POSIX_C_SOURCE=200809L)
        add_compile_options(-include unistd.h)
        ```
    - In `MathDeployment/Main.cpp` add the following includes at the top of the file:
        ```.cpp
        #include <FreeRTOS.h>
        #include <task.h>
        ```
    - In `MathDeployment/Main.cpp` add the following function right above main. As built, the MathDeployment uses the call to startSimulatedCycle to begin running the FSW and simulate clock cycles that would cause the ratedriver to invoke output ports. We still need that to happen, but it now needs to happen within a FreeRTOS task. So, we will create this BlockDriverTask function and use it later as a task routine to pass to FreeRTOS when a task is created. The `startSimulatedCycle` function never returns either unless the system is shutting down, which means we don't need to structure this in an infinite for or while loop as is customary for FreeRTOS tasks
        ```.cpp
        void BlockDriverTask (void *params) {
            MathDeployment::startSimulatedCycle(1000);
        }
        ```
    - In `MathDeployment/Main.cpp` add the following lines after the `setupTopology` call. Here, we create the task that will run the ratedriver and subsequently kickoff the FreeRTOS scheduler with `vTaskStartScheduler`. Note this call will only return if there is insufficient RTOS heap available to create the idle or timer daemon tasks. This is why we couldn't call both this and `startSimulatedCycle` the way it was done previously. The `startSimulatedCycle` function never returns either unless the system is shutting down, so we address that by putting it in a FreeRTOS task. See <a href=https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/05-Implementing-a-task>FreeRTOS Documentation</a> for more detail.
        ```.cpp
        FW_ASSERT(xTaskCreate(BlockDriverTask, "BlockDriverTask", 1600, NULL, 140, NULL));
        vTaskStartScheduler();
        ```
    - In `MathDeployment/Main.cpp` remove the following line that should now be just after `vTaskStartScheduler`.
        ```.cpp
        MathDeployment::startSimulatedCycle(1000);
        ```
    - We are done making edits to that file and return to the terminal. Create a FreeRTOSConfig file using the template provided with the kernel
        ```sh
        cp FreeRTOS-Kernel/examples/template_configuration/FreeRTOSConfig.h FreeRTOS-Kernel/include
        ```
    - Edit the newly created configuration file
        - Change configMAX_PRIORITIES to 150
        - Change configTotal_HEAP_SIZE to ( 8000* 1024 )
        - Change configCHECK_FOR_STACK_OVERFLOW to 0
        - At the very end, with all the other “INCLUDE_” statements, add this line
        ```.h
        #define INCLUDE_xSemaphoreGetMutexHolder       1
        ```
    - In `MathDeployment/Top/MathDeploymentTopology.cpp`, change COMM_PRIORITY to 96
        - What is most important here is that the priority is below the tlmSend component (Svc.TlmChan) which is currently set to 97
        - All components and their current priority can be seen in `MathDeployment/Top/instances.fpp`
- Confirm Success
    - Generate F' build files
        ```sh
        fprime-util generate
        ```
    - Build MathDeployment
        ```sh
        fprime-util build
        ```
    - Run the binary and launch the F' Ground Data System
        ```sh
        fprime-gds
        ```
    - Navigate to <a href=http://127.0.0.1:5000>http://127.0.0.1:5000</a> in a browser or wherever the terminal output shows the GDS UI is available
    - Send a few commands and make sure event and channelized telemetry are updating
    - Congratulations, you have the MathComponent project running on FreeRTOS!


## Section 2: FeatherM4 (Arduino) Setup Procedure

For this section, we will build a basic project to work with FreeRTOS on a <a href=https://www.adafruit.com/product/3857>Adafruit Feather M4</a>.

Before continuing, make sure your current working directory is where you want your new project located (fprime_freertos_example if you are following my setup example in the overview) and that your `fprime-venv` is activated.

- Install board packages and relevant Arduino libraries by running these terminal commands in order
    ```sh
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=$VIRTUAL_ENV/bin sh
    ```
    ```sh
    pip install arduino-cli-cmake-wrapper
    ```
    ```sh
    arduino-cli config init
    ```
    ```sh
    arduino-cli config add board_manager.additional_urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
    ```
    ```sh
    arduino-cli core update-index
    ```
    ```sh
    arduino-cli core install adafruit:samd
    ```
    ```sh
    arduino-cli core install arduino:samd
    ```
    ```sh
    arduino-cli lib install Time
    ```
    ```sh
    arduino-cli lib install FreeRTOS_SAMD51
    ```

- Project setup and configuration
    - Create the new project and give it a name like `example_project`
        ```sh
        fprime-bootstrap project
        ```
    - Change your working directory to the newly created project directory
        ```sh
        cd example_project
    - Add the fprime-arduino repository as a submodule
        ```sh
        git submodule add https://github.com/fprime-community/fprime-arduino.git
        ```
    - Add the fprime-freertos repository as a submodule
        ```sh
        git submodule add https://github.com/fprime-community/fprime-freertos.git
        ```
    - Install all fprime-arduino requirements
        ```sh
        pip install -r fprime-arduino/requirements.txt
        ```
    - Open the project directory in the IDE of your choosing. Open the `settings.ini` file and add the following lines after the framework_path line:
        ```.ini
        library_locations: ./fprime-arduino:./fprime-freertos
        default_toolchain: FreeRTOS_featherM4
        config_directory: ./config
        deployment_cookiecutter: https://github.com/laboratory10/fprime-freertos-arduino-deployment-cookiecutter
        ```
    - In the previous step, a config_directory was defined. We need to customize the F' configuration from the default in the F' repository to allow the image to be compact enough to fit into the small amount of memory available on a Feather M4. Now, we must copy over those configuration files into the directory we previously specified.
        - Copy the provided config directory into the project directory
            ```sh
            cp -r fprime/config .
            ```
        - Adjust TLMCHAN_HASH_BUCKETS in TlmChanImplCfg.hpp to 40
        - Adjust the files to meet your needs. A lot can be done to minimize the required memory, but I have focused on making the smallest number of changes needed to shrink the minimalist deployment in this example to fit in RAM, and this one change is all that is necessary for me.
    - In the project-level CmakeLists.txt (i.e. /example_project/CmakeLists.txt) add these lines after `project(example_project C CXX)`. Make sure `ARDUINO_LIB_PATH` and `ARDUINO_SAMD_LIB_PATH` match where these libraries actually are on your machine.
        ```.txt
        ### Libraries
        # Set the path to the Arduino libraries directory
        set(ARDUINO_LIB_PATH "/home/<username>/Arduino/libraries")
        set(ARDUINO_SAMD_LIB_PATH "/home/<username>/.arduino15/packages/adafruit/hardware/samd/1.7.16/libraries")

        # Include directories for Arduino libraries
        include_directories(
            ${ARDUINO_LIB_PATH}/Time
            ${ARDUINO_LIB_PATH}/FreeRTOS_SAMD51
            ${ARDUINO_SAMD_LIB_PATH}/Wire
            ${ARDUINO_SAMD_LIB_PATH}/SPI
            ${ARDUINO_SAMD_LIB_PATH}/Adafruit_ZeroDMA
        )
        target_use_arduino_libraries("FreeRTOS_SAMD51")
                
        ```
    - From the example_project directory run the following linux command to create a deployment using the cookiecutter specified in the `settings.ini` file. When prompted, give the deployment a name like `ExampleDeployment` and type "yes" if asked about adding the deployment to the project.cmake.
        ```sh
        fprime-util new --deployment
        ```
    - Make FreeRTOS arduino library configuration changes
        - Open the FreeRTOSConfig.h file wherever your arduino libraries are stored. For me the filepath is /home/username/Arduino/libraries/FreeRTOS_SAMD51/src/FreeRTOSConfig.h
        - Change config_TOTAL_HEAP_SIZE to 112 KB
            ```.h
            #define configTOTAL_HEAP_SIZE			( ( size_t ) ( 112 * 1024 ) )
            ```
        - Also add the following to somewhere in the file:
            ```.h
            #define INCLUDE_xSemaphoreGetMutexHolder 1
            ```

- Confirm Success
    - Generate F' build files
        ```sh
        fprime-util generate
        ```
    - Build ExampleDeployment
        ```sh
        fprime-util build
        ```
    - After the build command completes, you should see the size breakdown of the memory segments of the final target image
    - Confirm the binary was created in /example_project/ build-artifacts/FreeRTOS_featherM4/ExampleDeployment/bin/ExampleDeployment.elf.bin 

- Flash image to the target
    - Force the Feather M4 to enter programming mode by doing EITHER:
        - Double tap the physical reset button on the microcontroller
        - Using a serial monitor, open a connection to the board with a 1200 baud rate then immediately close it. Once programming mode is entered, it is recommended to switch the baud to 115200 immediately to prevent an inadvertent entry into programming mode.
    - Using the windows explorer GUI or another preferred method, copy the `ExampleDeployment.elf.bin` binary from the WSL filesystem into one directly accessible by Windows. The “Documents” folder will be used here and referenced later on during the command to flash the image.
    - Confirm the adafruit libraries required for the FeatherM4 are installed in Windows using the Arduino IDE (adafruit and arduino M0/SAMD packages). Specifically, the `bossac.exe` file is needed.
    - Determine the COM port you board is currently connected to by issuing this command in Powershell
        ```sh
        usbipd list
        ```
    - Flash the image using the following Powershell command. Be sure the filepath for `bossac.exe` and `ExampleDeployment.elf.bin` binary match reality.
        ```sh
        C:\Users\<username>\AppData\Local\Arduino15\packages\adafruit\tools\bossac\1.8.0-48-gb176eee/bossac.exe -i -d --port=COM27 -U -i --offset=0x4000 -w -v C:\Users\<username>\Documents\ExampleDeployment.elf.bin -R
        ```
    - Once flashing completes, a serial monitor of your choice can be used before continuing to confirm the target is active and writing to the serial interface.

- Interact with the target via F' Ground Data System
    - Bind and attach the target device to WSL so the serial data can be fed to the GDS using the following Powershell command and the appropriate busid from the usbipd command above.
        ```sh
        winget install --interactive --exact dorssel.usbipd-win
        ```
        ```sh
        usbipd bind --busid 1-9
        ```
        ```sh
        usbipd attach --wsl --busid 1-9
        ```
    - For this to succeed, the serial port must not be currently monitored by any other application. Once attached, Windows applications won't be able to access this COM port. If you need to detach it, you can power cycle the board or run the command `usbipd detach --busid 1-9` in Powershell.
    - In the WSL terminal, the following two commands can be optionally used to see that the attch command was successful. It will usually be attached as ttyACM0.
        ```sh
        sudo apt install usbutils
        ```
        ```sh
        lsusb
        ```
        ```sh
        ls /dev/tty*
        ```
    - Before being able to have fprime-gds connect to the borad via serial, you must update permission (one time only)
        ```sh
        sudo usermod -a -G dialout $USER
        ```
    - Run the GDS with the following linux command:
        ```sh
        fprime-gds -n --dictionary ./build-artifacts/FreeRTOS_featherM4/ExampleDeployment/dict/ExampleDeploymentTopologyAppDictionary.xml --communication-selection uart --uart-device /dev/ttyACM0 --uart-baud 115200
        ```
    - Navigate to <a href=http://127.0.0.1:5000>http://127.0.0.1:5000</a> in a browser or wherever the terminal output shows the GDS UI is available
    - Send a few commands and make sure event and channelized telemetry are updating
    - Congratulations, you have the F' and FreeRTOS running on a physical board!

