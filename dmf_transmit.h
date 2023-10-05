#ifndef _TRANSMIT_H_
#define _TRANSMIT_H_

typedef struct _ts_frame_s ts_frame_t;

struct _ts_frame {
    unsigned int        is_register:1;

    // master => slaver                  0x00
    // slaver => master                  0x11
    // slaver(server) => slaver(client)  0x01
    // slaver(client) => slaver(server)  0x10
    unsigned int        ts_type:2;
};

#endif  // _TRANSMIT_H_
