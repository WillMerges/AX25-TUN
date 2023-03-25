/*******************************************************************************
*
*  Name: kiss.h
*
*  Purpose: Defines functions for the usage of the KISS protocol.
*
*  Author: Will Merges
*
*******************************************************************************/
#ifndef KISS_H
#define KISS_H

// keep it simple, stupid!

#include <stdint.h>

// referenced http://www.ax25.net/kiss.aspx

// special characters
#define KISS_FEND           0xC0
#define KISS_FESC           0xDB
#define KISS_TFEND          0xDC
#define KISS_TFESC          0xDD

// commands
#define KISS_DATA_FRAME     0x00
#define KISS_TX_DELAY       0x01
#define KISS_PERSISTENCE    0x02
#define KISS_SLOT_TIME      0x03
#define KISS_TX_TAIL        0x04    // optionally supported by TNC
#define KISS_FULL_DUPLEX    0x05
#define KISS_SET_HARDWARE   0x06    // optionally supported by TNC
#define KISS_RETURN         0xFF    // optionally supported by TNC

/// @brief generate a KISS frame containing a payload
/// @param payload          the payload to encapsulate
/// @param payload_len      the size of the payload
/// @param dst              the address to copy the generated frame to
/// @param dst_len          the length of dst. The generated frame will be
///                         2 + (2 * payload_len) bytes maximum, but likely
///                         much smaller (this assumes every byte must be
///                         escaped plus frame end characters).
/// @return the size of frame in 'dst', or -1 on error
ssize_t gen_kiss_frame(uint8_t* payload, size_t payload_len,
                       uint8_t* dst, size_t dst_len);

#endif
