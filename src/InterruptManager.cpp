//
// Created by dell on 2019/6/5.
//

#include "InterruptManager.h"


void InterruptManager::requestInterrupt(Byte bit) {
    setBit(iF, bit);
}

void InterruptManager::setIF(Byte newIF) {
    iF &= 0xE0;
    iF |= (newIF & 0x1F);
}

bool InterruptManager::getIME() {
    return iME;
}

void InterruptManager::setHalt(bool newHalt) {
    halt = newHalt;
}

void InterruptManager::setStop(bool newStop) {
    stop = newStop;
}

bool InterruptManager::hasInterrupt() {
    Byte maskCode = static_cast<Byte>((iE & iF) & 0x1F);
    return iME && maskCode;
}

Byte InterruptManager::handleInterrupt() {
    iME = false;
    halt = false;
    Byte maskCode = static_cast<Byte>((iE & iF) & 0x1F);
    for(Byte i = 0; i < 5; ++i){
        if (getBit(maskCode, i)){
#ifndef NLOG
            logger << "interrupt: " << i << std::endl;
#endif
            resetBit(iF, i);
            return i;
        }
    }

}

bool InterruptManager::handleHalt() {
    Byte iFUsed = iF & 0x1F;
    if (!iME && halt && iFUsed){
        halt = false;
        return false;
    }else if (!halt){
        return true;
    }
    return false;
}

bool InterruptManager::accepts(Word address) {
    return address == 0xFF0F || address == 0xFFFF;
}

Byte InterruptManager::getByte(Word address) {
    if (address == 0xFF0F) {
        return iF;
    } else if (address == 0xFFFF) {
        return iE;
    }
    return 0xFF;
}

void InterruptManager::setByte(Word address, Byte value) {
    if (address == 0xFF0F) {
        setIF(value);
    } else if (address == 0xFFFF) {
        iE = value;
    }
}

void InterruptManager::setIME(bool newIME) {
    iME = newIME;
}

InterruptManager *InterruptManager::getInterruptManager() {
    static InterruptManager interruptManager;
    return &interruptManager;
}
