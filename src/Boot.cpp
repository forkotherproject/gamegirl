//
// Created by dell on 2019/6/13.
//

#include "Boot.h"
#include "Exceptions.h"

bool Boot::accepts(Word address) {
    return address < 0x100;
}

Byte Boot::getByte(Word address) {
    return bios[address];
}

void Boot::setByte(Word address, Byte value) {}
