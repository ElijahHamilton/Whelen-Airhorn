#include <stdio.h>
#include <math.h>

#define fs 48000			//higher the sample rate, higher the accuracy
#define highfreq 651		//high frequency (hertz)
#define lowfreq 465		//low frequency (hertz)
#define highcycles 5		//number of high wave cycles
#define lowcycles 4		//number of low wave cycles
#define dur 10				//duration of output (seconds)

int main(int argc, char *argv[]) {
	short s;			//output buffer
	double phase1 = 0;	//for previous phase
	double phase2 = 0;	//for current phase
	double freq;		//buffer for comparative phase
	double high = highcycles/(double)highfreq;
	double low = lowcycles/(double)lowfreq;
	double srate = 1/(high+low);	//frequency swap rate
	double duty = high/(high+low);	//swap rate duty cycle

	FILE *fout = fopen("output.raw", "wb");

	printf("swap rate (Hz): %f\n", srate);
	printf("duty cycle (%%): %f\n\n", duty*100);

	for(int i = 1; i<fs*dur; i++) {
		freq = fmod(i*srate/fs, 1);

		if(freq > phase2) {	//upon completing a full cycle, reset the phase
			phase1 += (freq > duty) ? lowfreq/(double)fs : highfreq/(double)fs;
		} else {
			phase1 = 0;
		}

		phase2 = freq;

		s = (fmod(phase1, 1) < 0.5) ? 16384 : -16384;

		fwrite(&s, 2, 1, fout);
	}

	fclose(fout);
	printf("output written to output.raw (signed 16-bit, mono, %dhz)\n", fs);
	return 0;
}
