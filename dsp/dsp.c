#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <complex.h>
#include "wav.h"

#define N 100000
#define PI 3.14159265

/*
Convolve: convoles two arrays x and h
input: float arrays x, h, their lengths, and pointer to ylen that will save
the length of output array;
output: float array y which is convolution of x and h
*/

float* convolve(float x[], float h[], int xlen, int hlen, int * ylens) {

  int ylen;
  ylen = xlen + hlen - 1;
  float *y = (float *)malloc(sizeof(float *) * ylen);
  int i,j, k;
  float yval;
  for (i=0;i < ylen; i++) { // for loop occurs until the max shift happens
    k = i; // k
    yval = 0.00;
    for (j = 0; j <xlen; j++) {
      if (k >=0)  {
        if (k < hlen) { // k must be from 0 to (length of h - 1)
        yval += h[k]*x[j];  // add values to y[i] for every overlap
        }
      }
      k = k-1;
    }
    y[i] = yval;
  }
  (*ylens) = ylen; // output y[i]
  return y;

}

/*
create_csv: save data in float array in csv file.
input: filename of csv, float array, length of float array
output: it should save csv file with data
*/

void create_csv(char *filename, float a[],int m){

  int p;
  filename=strcat(filename,".csv");
  FILE *fp=fopen(filename,"w");

  for(p=0;p<m;p++){
    fprintf(fp,"%f \n",a[p]);
    }

  fclose(fp);
  printf("\nfile created\n");

}

/*
create_csv_comp: save data in float complex  array in csv file.
input: filename of csv, float array, length of float array
output: it should save csv file with data

IN PROGRESS OF FIXING THIS
*/

void create_csv_comp(char *filename, float complex a[],int m){

  int p;
  filename=strcat(filename,".csv");
  FILE *fp=fopen(filename,"w");

  for(p=0;p<m;p++){
    if (!cimag(a[p]))
			fprintf(fp, "%f \n", creal(a[p]));
		else
			fprintf(fp, "%f, %f \n", creal(a[p]), cimag(a[p]));
    }
  fclose(fp);
  printf("\nfile created\n");

}

/*
DFT: computes DTFT of the float array. This is NOT FFT, so it will compute DTFT
in brute force way. To read about DTFT, read this:
https://en.wikipedia.org/wiki/Discrete-time_Fourier_transform


input:float array, length of float array
output: float complex array that sould save DTFT of the array, each element is
complex number

IN PROGRESS OF FIXING THIS
*/

float complex *DFT(float data[], int dlen){

   int n, k;
   //float data[N];
   int i, j;
   float real, imag;
   //float complex *output = malloc(dlen);
   float complex *output = (float complex*)malloc(sizeof(float complex*) * dlen);
   for (n=0; n < dlen; n++) {
     real = 0;
     imag = 0;
     for (k = 0; k < dlen; k++) {
      real += creal(data[k] * (cos(2*PI*n*k/dlen) -I * sin(2*PI*n*k/dlen)));
      imag -= cimag(data[k] * (cos(2*PI*n*k/dlen) -I * sin(2*PI*n*k/dlen)));
    }
    float complex z = CMPLX(real, imag);
    output[n] = z;
   }

   return output;
}

/*
The three functions below(_fft, fft, show) are from external sources. They are
modified so that they output desired data type (complex float)
*/
void _fft(float complex buf[], float complex out[], int n, int step)
{
  if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);

		for (int i = 0; i < n; i += 2 * step) {
			float complex t = cexp(-I *  PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}

float complex* fft(float complex buf[], int n)
{
  int i;
  int j;
  float complex *output = (float complex*)malloc(sizeof(float complex*) * n);
  float complex out[n];
  for (i = 0; i < n; i++) {
    out[i] = buf[i];
  }
	_fft(buf, out, n, 1);
  for (j = 0; j < n; j++) {
    output[i] = buf[i];
  }
  return output;
}



void show(const char * s, float complex buf[], int n) {
	printf("%s", s);
	for (int i = 0; i < n; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}

/*
choose_channel: chooses channel and its data that we want.
input: pointer to pointer to float array, length of array, side (channel choice)
(side = 0 => channel 1, side = 2 => channel 2)
output: float array that has data from one of the channels

*/
float* choose_channel(float** x, int len, int side) {
  int i;
  float *y = (float *)malloc(sizeof(float *) * len);
  for (i=0;i <len;i++) {
    if (side == 0) {
      y[i] = x[i][0];
    }
    else {
      y[i] = x[i][1];
    }
  }
  return y;

}

/*
choose_channel: chooses channel and its data that we want. Made specifically
for channel with complex number data
input: pointer to pointer to float array, length of array, side (channel choice)
(side = 0 => channel 1, side = 2 => channel 2)
output: float array that has data from one of the channels

IN PROGRESS OF FIXING THIS FUNCTION
*/
float complex* choose_channel_comp(float** x, int len, int side) {
  int i;
  float complex *y = (float complex*)malloc(sizeof(float complex*) * len);
  for (i=0;i <len;i++) {
    if (side == 0) {
      y[i] = x[i][0];
    }
    else {
      y[i] = x[i][1];
    }
  }
  return y;

}
