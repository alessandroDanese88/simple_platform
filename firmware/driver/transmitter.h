////////////////////////////////////////////////////////////////////////////////
//
//                     The Simple Platform project
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
////////////////////////////////////////////////////////////////////////////////


#ifndef __WB_TRANSMITTER_DRIVER__
#define __WB_TRANSMITTER_DRIVER__

#include "buslayer_master.h"

// the base address of Transmitter mudule
#define TRANSMITTER_BASE_ADDRESS M_PTR_C(0x60)

void transmit(char data) {
    wb_writeByte(TRANSMITTER_BASE_ADDRESS, data);
}

void transmitInt(unsigned int data) {
    transmit((char)data);
    transmit((char)(data >> 8));
    transmit((char)(data >> 16));
    transmit((char)(data >> 24));
}

#endif
