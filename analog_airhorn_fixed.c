#include <stdio.h>
#include <math.h>

#define fs 48000			//sample rate in hertz
#define length 0.1			//signal length in seconds
#define freq_multiply 0.96	//must have decimal!

int main() {
	int prev = 0;
	double num;
	short outbuf;

	FILE *fout = fopen("output.raw", "wb");

	for(double i=0; i<fs*length; i++) {
		if(fmod(i/fs*100*freq_multiply, 1)<1.0/3) {
			outbuf = sin(2*M_PI*num/fs*720*freq_multiply)*16384;
			prev = 1;
		} else {
			if(prev==1) num -= (double)fs/(600*freq_multiply);
			outbuf = sin(2*M_PI*num/fs*240*freq_multiply)*16384;
			prev = 0;
		}

		fwrite(&outbuf, 2, 1, fout);
		num++;
	}

	return 0;
}