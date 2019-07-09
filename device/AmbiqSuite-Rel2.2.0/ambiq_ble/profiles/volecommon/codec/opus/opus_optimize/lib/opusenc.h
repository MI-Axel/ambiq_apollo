#ifndef OPUSENC__H
#define OPUSENC__H

typedef void* spl_opus_encoder_h;
spl_opus_encoder_h* octopus_encoder_create(int option);
int octopus_encode(spl_opus_encoder_h *st, const short *pcm, int frame_size, unsigned char *data, int out_data_bytes);

#endif // OPUSENC__H


