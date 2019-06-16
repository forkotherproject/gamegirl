extern "C" {
    #include "getopt.h"
}

#include <cstdlib>
#include <string>
#include "common.h"
#include "MMU.h"
#include "WRam.h"
#include "ZRam.h"
#include "GPU.h"
#include "Timer.h"
#include "CartridgeDriver.h"
#include "InterruptManager.h"
#include "CPU.h"
#include "SDLManager.h"
#include "Boot.h"
#include "Joypad.h"
#include "EmptySpace.h"
#include "Logger.h"


bool isQuit = false;
uint64_t step();
bool init(int argc, char **argv);

int main(int argc, char **argv) {
    int allCycle = 0;
    bool useBoot = init(argc, argv);
    if (useBoot) {
        while (cpu.getPC() < 0x100) {
            allCycle += step();
        }
        MMU::getMMU()->removeAddressSpace(&boot);
    }
    while (!isQuit) {
        allCycle += step();
#ifndef NLOG
        logger << "clk:" << allCycle << std::endl;
#endif
    }
    return 0;
}


bool init(int argc, char **argv) {
    if (argc == 1) {
        throw FileNotFoundException("argument wrong", "no file path ");
    }
    const std::string FILE_PATH(argv[1]);
    uint8_t fps = 60;
    auto xPos = SDL_WINDOWPOS_UNDEFINED;
    auto yPos = SDL_WINDOWPOS_UNDEFINED;
    uint8_t zoomTime = 1;
    bool useBoot = false;
    bool useSprite = true;
    optind++;
    const std::string optString{"bSf:x:y:z:c:"};
    const char* const optPtr = optString.c_str();
    int option;
    while ((option = getopt(argc, argv, optPtr)) != -1){
        switch (option) {
            case 'b':
                useBoot = true;
                break;
            case 'z':
                zoomTime = std::atoi(optarg);
                break;
            case 'f':
                fps = std::atoi(optarg);
                break;
            case 'x':
                xPos = std::atoi(optarg);
                break;
            case 'y':
                yPos = std::atoi(optarg);
                break;
            case 'S':
                useSprite = false;
                break;
            case 'c': {
                Color coleredMap1[4] = {
                        {0xFF, 0xFA, 0xCD, 0x00},
                        {0xFF, 0xCA, 0x28, 0x55},
                        {0xFF, 0x00, 0x00, 0xAA},
                        {0x00, 0x00, 0x00, 0xFF}
                };
                Color coleredMap2[4] = {
                        {0xE0, 0xFF, 0xFF, 0x00},
                        {107, 194, 53, 0x55},
                        {6, 128, 67, 0xAA},
                        {0x00, 0x00, 0x00, 0xFF}
                };
                Color coleredMap3[4] = {
                        {0xFF, 0xE1, 0xFF, 0x00},
                        {0xFF, 0xBB, 0xFF, 0x55},
                        {0xBB, 0xFF, 0xFF, 0xAA},
                        {0x00, 0x00, 0x00, 0xFF}
                };
                Color coleredMap4[4] = {
                        {0x00, 0x00, 0x00, 0x00},
                        {0xFF, 0xCA, 0x28, 0x55},
                        {0xEE, 0xEE, 0x00, 0xAA},
                        {0xFF, 0xFF, 0xFF, 0xFF}
                };
                switch (std::atoi(optarg)) {
                    case 1: {
                        for (int i = 0; i < 4; i++) {
                            realColorMap[i] = coleredMap1[i];
                        }
                        break;
                    }
                    case 2:{
                        for (int i = 0; i < 4; i++) {
                            realColorMap[i] = coleredMap2[i];
                        }
                        break;
                    }
                    case 3:{
                        for (int i = 0; i < 4; i++) {
                            realColorMap[i] = coleredMap3[i];
                        }
                        break;
                    }
                    case 4:{
                        for (int i = 0; i < 4; i++) {
                            realColorMap[i] = coleredMap4[i];
                        }
                        break;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    std::ios::sync_with_stdio(false);
    CartridgeDriver::getCartridgeDriver()->openFile(FILE_PATH);
    SDLManager::getSDLManager()->init(CartridgeDriver::getCartridgeDriver()->getTitle(), zoomTime, xPos, yPos, fps);
    GPU::getGPU()->init(useSprite);
    cpu.initMap();
    MMU::getMMU()->init();
#ifndef NLOG
    logger.open("gamegirl.log");
#endif
    if (useBoot){
        MMU::getMMU()->addAddressSpace(&boot);
        cpu.initRegisters();
    } else {
        cpu.initRegistersAfterBoot();
    }
    MMU::getMMU()->addAddressSpace(CartridgeDriver::getCartridgeDriver());
    MMU::getMMU()->addAddressSpace(WRam::getWRam());
    MMU::getMMU()->addAddressSpace(ZRam::getZRam());
    MMU::getMMU()->addAddressSpace(GPU::getGPU());
    MMU::getMMU()->addAddressSpace(Timer::getTimer());
    MMU::getMMU()->addAddressSpace(Joypad::getJoypad());
    MMU::getMMU()->addAddressSpace(InterruptManager::getInterruptManager());
    MMU::getMMU()->addAddressSpace(EmptySpace::getEmptySpace());
    return useBoot;
}

uint64_t step() {
    isQuit = SDLManager::getSDLManager()->handleInput();
    Joypad::getJoypad()->update();
    Byte cpuCycle = cpu.step();
    Timer::getTimer()->addTime(cpuCycle);
    GPU::getGPU()->addTime(cpuCycle);
    return cpuCycle;
};

