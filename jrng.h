/*
 * jrng.h
 * Headers for my rng functions
 * Josh Chandler
 * Dec. 26, 2017
*/

unsigned short crng(unsigned short input);
unsigned char bitrng(unsigned char input, unsigned int bits);
unsigned short bitrng_ext(unsigned short input, unsigned int bits, unsigned int multi, unsigned int exor);
unsigned short myrng(unsigned short input);
