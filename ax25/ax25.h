#ifndef AX25_H
#define AX25_H

// referenced http://www.ax25.net/AX25.2.2-Jul%2098-2.pdf

// AX.25 information frame looks like the following
/*
* Flag     - 8 bits, acts as a frame delimter, always 0x7E.
* Address  - 112/224 bits, contains source and destination as well as
*            command/respone info.
* Control  - 8/16 bits, identifies type of frame
* PID      - 8 bits, protocol identifier field for the layer 3 protocol in use.
* Info     - N*8 bits, user data (the payload).
* FCS      - 16 bits, frame check sequence.
* Flag     - 8 bits, acts as a frame delimter, always 0x7E.
*            Close flag can act as start flag for the next frame
*/


// minimum frame size of an AX.25 frame, including start/close flags
#define AX25_MIN_FRAME_SIZE 17 // bytes

// the minumum number of 1s to send in a row to abort a frame
#define AX25_NUM_ONES_ABOR 15

// the value of the start/close flag to delimit frames
#define AX25_FRAME_DELIMIT      0x7E

// non-repeater address subfield
typedef struct {
    uint8_t callsign[6];    // callsign (ASCII upper-case, padded with spaces)
    uint8_t ssid;           // SSID octet
} ax25_addr_subfield_t;

#endif
