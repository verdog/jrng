/*
 * crng.cpp
 * Exploring random number generators
 * Specifically, bijections and uniform mappings.
 * Josh Chandler
 * Dec. 26, 2017
*/

#ifndef CRNG_CPP
#define CRNG_CPP

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <bitset>

#include "EasyBMP_1.06/EasyBMP.h"
#include "jrng.h"

void printint(int p);

#define ARGC (4)

using namespace std;

int main(int argc, char const *argv[])
{
   // usage
   if (argc != ARGC)
   {
      cout << "usage: ./crng <bits in [1,8]> <multi (must be odd)> <xor (must be odd)>\n";
      return -1;
   }

   unsigned int bits = atoi(argv[1]);
   unsigned int multi = strtol(argv[2], NULL, 16);
   unsigned int exor = strtol(argv[3], NULL, 16);

   if (bits < 1 || bits > 16 || (multi & 1) == 0 || (exor & 1) == 0)
   {
      cout << "usage: ./crng <bits in [1,8]> <multi (must be odd)> <xor (must be odd)>\n";
      return -1;
   }

   int i, j;
   double avg;
   unsigned short input = 0;
   unsigned int iterations = 0;
   BMP graph;
   graph.SetSize(2048, 1024);

   RGBApixel blackpxl {0, 0, 0, 0};
   // RGBApixel pinkpxl {232, 232, 255, 0};

   // unvisited list
   int vsize = pow(2, bits);
   bool* visited = new bool[vsize];
   for (i=0; i<vsize; i++) visited[i] = false;

   // test the rng
   while (visited[input] == false)
   {
      // print
      cout << input << endl;

      // mark as visited
      visited[input] = true;

      // plot point
      graph.SetPixel(iterations * graph.TellWidth() / 65536,
                     graph.TellHeight() - 1 - (input * graph.TellHeight() / 65536),
                     blackpxl);

      // next output
      // input = bitrng_ext(input, bits, multi, exor);
      input = myrng(input);
      iterations++;
   }

   // final report
   cout << "\nfinal results:\n";
   cout << "iterations: " << iterations << endl;
   cout << "unvisited: " << endl;

   for (i=0; i<vsize; i++)
   {
      if (visited[i] == false) cout << i << endl;
   }
   cout << endl;

   cout << "test: " << endl;
   for (i=0;i<8;i++)
   {
      cout << myrng(input)%16 << endl;
      input = myrng(input);
   }
   cout << endl;

   cout << "average value %16 : \n";

   for (j=0; j<8; j++)
   {
      avg = 0;
      for (i=0; i<10000; i++)
      {
         avg += myrng(input)%16;
         input =myrng (input);
      }
      avg /= 10000;
      cout << avg << endl;
   }

   graph.WriteToFile("graph.bmp");

   return 0;
}

void printint(int p)
{
   cout.width(6);
   cout << p << " : ";
   cout.width(16);
   cout << bitset<16>(p) << endl;
   return;
}

#endif
