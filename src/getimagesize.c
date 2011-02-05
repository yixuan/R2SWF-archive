/* http://www.wischik.com/lu/programmer/get-image-size.html */

#include <stdio.h>

void setDefault(int *width, int *height)
{
	//Rprintf("Couldn't determine the image size. Use default value instead.\n");
	*width = 640;
	*height = 640;
}

void getImageSize(char **filename, int *width, int *height)
{
	FILE *f = fopen(filename[0], "rb");
	if (f==0)
	{
		setDefault(width, height);
		return;
	}
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	fseek(f, 0, SEEK_SET); 
	if (len < 24)
	{
		setDefault(width, height);
		fclose(f);
		return;
	}

	unsigned char buf[24];
	fread(buf, 1, 24, f);

	if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
	{
		long pos = 2;
		while (buf[2]==0xFF)
		{
			if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
			pos += 2 + (buf[4]<<8) + buf[5];
			if (pos + 12 > len) break;
			fseek(f, pos, SEEK_SET);
			fread(buf + 2, 1, 12, f);    
		}
	}

	fclose(f);

	// JPEG
	if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
	{
		*height = (buf[7]<<8) + buf[8];
		*width = (buf[9]<<8) + buf[10];
		return;
	}

	// GIF
	if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
	{
		*width = buf[6] + (buf[7]<<8);
		*height = buf[8] + (buf[9]<<8);
		return;
	}

	// PNG
	if (buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
	{
		*width = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
		*height = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
		return;
	}

	setDefault(width, height);
}
