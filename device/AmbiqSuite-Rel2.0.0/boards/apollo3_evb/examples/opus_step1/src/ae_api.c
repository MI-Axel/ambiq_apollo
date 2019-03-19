// tst_octopus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
typedef void* spl_opus_encoder_h;
spl_opus_encoder_h* octopus_encoder_create();
int octopus_encode(spl_opus_encoder_h *st, const short *pcm, int frame_size, unsigned char *data, int out_data_bytes);

spl_opus_encoder_h *p_spl_opus_encoder;

int audio_enc_init()
{
  p_spl_opus_encoder = octopus_encoder_create();
  return 0;
}

int audio_enc_encode_frame(short *p_pcm_buffer, int n_pcm_samples, unsigned char *p_encoded_buffer)
{
  int n = 0, m;
  int hdr = 8;
  int size = 1500; //todo
  int rng = 0;
      reset_alloca_pool();
      n = octopus_encode(p_spl_opus_encoder, p_pcm_buffer, n_pcm_samples, &p_encoded_buffer[hdr], size);
      reset_alloca_pool();
      opus_encoder_enc_range(p_spl_opus_encoder, &rng);
      
      {
        char *p1 = (char*)(&n);
        char *p2 = (char*)(&rng);
        for(int i = 0; i < 4; i++) {
          p_encoded_buffer[i] = p1[3-i];
          p_encoded_buffer[4 + i] = p2[3-i];
        }
      }
      //printf("   stack usage = %d\n", m);
      
      return n + hdr;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


