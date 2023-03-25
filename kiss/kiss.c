#include <stdlib.h>

#include "kiss.h"

/// @brief generate a KISS frame containing a payload
/// @param payload          the payload to encapsulate
/// @param payload_len      the size of the payload
/// @param dst              the address to copy the generated frame to
/// @param dst_len          the length of dst. The generated frame will be
///                         3 + (2 * payload_len) bytes maximum, but likely
///                         much smaller (this assumes every byte must be
///                         escaped plus frame end characters).
/// @return the size of frame in 'dst', or -1 on error
ssize_t gen_kiss_frame(uint8_t* payload, size_t payload_len,
                                                uint8_t* dst, size_t dst_len) {
    size_t dst_i = 0;
    size_t pay_i = 0;

    // minimum of 3 bytes (frame end, data frame command, data byte, frame end)
    if(dst_len < 4) {
        return -1;
    }

    dst[dst_i++] = KISS_FEND;
    dst[dst_i++] = KISS_DATA_FRAME;

    // we know we need an extra frame end at the end
    dst_len--;

    while(pay_i < payload_len) {
        if(KISS_FEND == payload[pay_i]) {
            if(dst_i + 2 >= dst_len) {
                // no room
                return -1;
            }

            dst[dst_i++] = KISS_FESC;
            dst[dst_i++] = KISS_TFEND;
        } else if(KISS_FESC == payload[pay_i]) {
            if(dst_i + 2 >= dst_len) {
                // no room
                return -1;
            }

            dst[dst_i++] = KISS_FESC;
            dst[dst_i++] = KISS_TFESC;
        } else {
            if(dst_i + 1 >= dst_len) {
                // no room
                return -1;
            }

            dst[dst_i++] = payload[pay_i];
        }

        pay_i++;
    }

    // no need to check size, we preemptively subtracted this byte from the len
    dst[dst_i++] = KISS_FEND;

    return dst_i;
}
