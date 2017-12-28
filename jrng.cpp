/*
 * jrng.cpp
 * Function bodies for jrng.h
 * Josh Chandler
 * Dec. 26, 2017
*/

#ifndef JRNG_CPP
#define JRNG_CPP

#include <stdio.h>
#include <iostream>
#include <bitset>

using namespace std;

unsigned short crng(unsigned short input)
{
   unsigned short a;
   unsigned short b;

   // super mario 64
   a = (unsigned char)input << 8;
   a ^= input;
   input = ((a & 0xFF) << 8) | ((a & 0xFF00) >> 8);
   a = ((unsigned char)a << 1) ^ input;
   b = (a >> 1) ^ 0xFF80;
   if ((a & 1) == 0)
   {
      input = b ^ 0x1FF4;
   }
   else
   {
      input = b ^ 0x8180;
   }

   return input;
}

unsigned char bitrng(unsigned char input, unsigned int bits)
{
   unsigned char mask = 1;
   unsigned int i;

   // make mask
   for (i = 0; i < bits; i++) mask *= 2;
   mask -= 1; // should now be in the form 0b111...1

   return ((input*0xFF)^0x7F) & mask;
}

unsigned short bitrng_ext(unsigned short input, unsigned int bits, unsigned int multi, unsigned int exor)
{
   unsigned int mask = 1;
   unsigned int i;

   // make mask
   for (i = 0; i < bits; i++) mask *= 2;
   mask -= 1; // should now be in the form 0b111...1

   return ((input*multi)^exor) & mask;
}

unsigned short myrng(unsigned short input)
{
   if (input == 24310) input = 0; // failsafe

   unsigned short a;
   unsigned short b;

   input = ((input << 8) & 0xFF00) | ((input >> 8) & 0x00FF);

   a = ((unsigned char)input << 1)^input;

   b = input >> 6;

   if ((b & 1) == 0)
   {
      b ^= 0xBEEF;
   }
   else
   {
      b ^= 0xABCD;
   }

   input = a^b;

   return input;
}

#endif
