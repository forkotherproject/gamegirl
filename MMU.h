// memory management unit
// Created by dell on 2019/4/17.
//

#ifndef GAMEGIRL_MMU_H
#define GAMEGIRL_MMU_H

#include <vector>
#include <array>
#include "common.h"
#include "AddressSpace.h"


class MMU {
private:
    std::vector<AddressSpace *> spaces;
    Byte* unusedSpaces;
public:
	void addAddressSpace(AddressSpace * s){
		spaces.push_back(s);
	};
    MMU(){
        unusedSpaces = new Byte[0x10000];
    }
    Byte readByte(Word address);
    Word readWord(Word address);
    void writeByte(Word address, Byte value);
    void writeWord(Word address, Word value);
};
extern MMU mmu;

#endif //GAMEGIRL_MMU_H
