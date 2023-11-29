#include <stdio.h>
#include <math.h>

#define fs 48000		//higher the sample rate, higher the accuracy
#define highfreq 651	//high frequency (hertz)
#define lowfreq 465		//low frequency (hertz)
#define highcycles 5	//number of high wave cycles
#define lowcycles 4		//number of low wave cycles
#define dur 10			//duration of output (seconds)

int main(int argc, char *argv[]) {
	short s;
	double phase1 = 0;
	double phase2 = 0;
	double freq;
	double high = highcycles/(double)highfreq;
	double low = lowcycles/(double)lowfreq;
	double srate = 1/(high+low);
	double duty = high/(high+low);

	FILE *fout = fopen("output.raw", "wb");

	for(int i = 1; i<fs*dur; i++) {
		phase1 += srate/fs;
		freq = (fmod(phase1, 1) < duty) ? highfreq : lowfreq;

		phase2 += freq/fs;
		s = (fmod(phase2, 1) < 0.5) ? 16384 : -16384;

		fwrite(&s, 2, 1, fout);
	}

	fclose(fout);
	printf("output written to output.raw (signed 16-bit, mono, %dhz)\n", fs);
	return 0;
}
