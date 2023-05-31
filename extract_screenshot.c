//read vbox screenshoot

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t readf(FILE *f)
{
	uint32_t r;
	fread(&r, 4, 1, f);
	return r;
}

char imgdata[1024*1024];

void writeimg(int width, int height, char *data)
{

	FILE *out = fopen("out.ppm", "w");
	fprintf(out, "P3\n%d %d\n255\n", width, height);
	int r,c,g;
	unsigned char *u = data;
	for (r = 0; r < height; r++) {
		for (c=0; c<width; c++) {
			int c1 = *u++;
			int c2 = *u++;
			int c3 = *u++;
			fprintf(out, "%d %d %d ", c3, c2, c1);
			*u++;
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

int main(int argc, char *argv[])
{
	char s[50];
	puts("Enter the path of the dir containing vbox.img-DisplayScreenshot.out file: ");
	scanf("%49[^\n]%*c", s); //input path
	//printf("Path: %s\n", s);

	char inputFile[100]; //path/to/vbox.img-DisplayScreenshot.out
	strcpy(inputFile, s);
	strcat(inputFile, "/vbox.img-DisplayScreenshot.out");
	//printf("Input file: %s\n", inputFile);

	char outputRaw[100]; //path/to/out.raw
	strcpy(outputRaw, s);
	strcat(outputRaw, "/out.raw");
	//printf("Output file: %s\n", outputRaw);

	char outputPng[100]; //path/to/out.png
	strcpy(outputPng, s);
	strcat(outputPng, "./out.png");
	//printf("Output file (png): %s\n", outputPng);

	FILE *f = fopen(inputFile, "rb"); //open the input file
	int blocks;
	fread(&blocks, 4, 1, f);
	printf("Count of blocks: %d\n", blocks);
	int i;
	for (i = 0; i < blocks; i++) {
		int cbblock;
		fread(&cbblock, 4, 1, f);
		printf("cbbblock: %d\n", cbblock);	
		int type;
		fread(&type, 4, 1, f);
		printf("type: %d\n", type);	
		int cbData = cbblock - 2 * sizeof(uint32_t);
		printf("data size: %d bytes\n", cbData);
		int width = readf(f);
		int height = readf(f);
		printf("%d x %d = %d\n", width, height, width*height);
		fread(imgdata, cbData, 1, f);
		if (type==0) {
			FILE *out = fopen(outputRaw, "w");
			fwrite(imgdata, cbData, 1, out);
			fclose(out);
			printf("Output file: %s\n", outputRaw);

			writeimg(width, height, imgdata);
		} else {
			FILE *out = fopen(outputPng, "w");
			fwrite(imgdata, cbData, 1, out);
			fclose(out);
			printf("Output file (png): %s\n", outputPng);
		}
	}
}
