#ifndef __TRANSMIT_H__
#define __TRANSMIT_H__

#include "main.h"

typedef union
{
    struct
    {
        char uid[4];
        char data[8];
    } frame;

    char data_frame[12];
} frame_nfc;

void transmit(frame_nfc *nfc, char *uid, char *data);

#endif