#include "transmit.h"


/**
 * @brief Transmit frame nfc data
 * 
 * @param nfc use's nfc card
 * @param uid user identifier
 * @param data user's data
 */
void transmit(frame_nfc *nfc, char *uid, char *data)
{
  // TODO
  strcpy(nfc->frame.uid, uid);
  strcpy(nfc->frame.data, data);
}