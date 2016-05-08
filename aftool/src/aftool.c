/***************************************************************************
 *   Copyright (C) 2009 by Jared Bruni                                     *
 *   jared@lostsidedead.biz                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include<gd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

gdImagePtr img1,img2,img3,img4;
gdImagePtr ptrs[4];

typedef union _Color {
	unsigned int colors;
	unsigned char rgb[4];
} Color;

int output_ = 0;

int mxAlphaInit(gdImagePtr ptr)
{
	unsigned int i,z;
	for(i = 0; i < ptr->sx; i++)
	{
		for(z = 0; z < ptr->sy; z++)
		{
			int one = rand()%4, two = rand()%4, three = rand()%4;
			int fcolor = 0;
			Color color[3];
			color[0].colors = gdImageGetPixel(ptrs[one], i, z);
			color[1].colors = gdImageGetPixel(ptrs[two], i, z);
			color[2].colors = gdImageGetPixel(ptrs[three], i, z);
			fcolor = gdImageColorAllocate(ptr, color[0].rgb[0], color[1].rgb[1], color[2].rgb[2]);
			gdImageSetPixel(ptr, i, z, fcolor);
		}
	}
	return 0;
}

int mxBlend(gdImagePtr ptr, gdImagePtr main)
{
	int i,z;
	static float alpha = 1.0f;
	for(i = 0; i < main->sx && i < ptr->sx; i++)
	{
		for(z = 0; z < main->sy && z < ptr->sy; z++)
		{
			Color col, colz;
			col.colors = gdImageGetPixel(ptr, i, z);
			colz.colors = gdImageGetPixel(main, i, z);
			colz.rgb[0] = col.rgb[0] + (alpha*colz.rgb[0]);
			colz.rgb[1] = col.rgb[1] + (alpha*colz.rgb[1]);
			colz.rgb[2] = col.rgb[2] + (alpha*colz.rgb[2]);
			gdImageSetPixel(main, i, z, colz.colors);
		}
	}
	return 0;
}

int mxMorph(gdImagePtr main)
{
	int i,z;
	for(i = 0; i < main->sx - 2; i++)
	{
		for(z = 0; z < main->sy; z++)
		{
			Color col[4];
			int tcol[4];
			col[0].colors = gdImageGetPixel(main, i, z);
			col[1].colors = gdImageGetPixel(main, i+1,z);
			col[2].colors = gdImageGetPixel(main,i, z+1);
			col[3].colors = gdImageGetPixel(main,i+1, z+1);

			tcol[0] = col[0].rgb[0] + col[1].rgb[0] + col[2].rgb[0] + col[3].rgb[0];
			tcol[1] = col[0].rgb[1] + col[1].rgb[1] + col[2].rgb[1] + col[3].rgb[1];
			tcol[2] = col[0].rgb[2] + col[1].rgb[2] + col[2].rgb[2] + col[3].rgb[2];

			tcol[0] /= 4;
			tcol[1] /= 4;
			tcol[2] /= 4;

			switch(rand()%3)
			{
			case 0:
			{
				Color colorz;
				colorz.rgb[0] = ++tcol[0];
				colorz.rgb[1] = --tcol[1];
				colorz.rgb[2] = --tcol[2];
				gdImageSetPixel(main, i, z, colorz.colors);
			}
			break;
			case 1:
			{
				Color colorz;
				colorz.rgb[0] = --tcol[0];
				colorz.rgb[1] = ++tcol[1];
				colorz.rgb[2] = --tcol[2];
				gdImageSetPixel(main, i, z, colorz.colors);

			}
			break;
			case 2:
			{
				Color colorz;
				colorz.rgb[0] = --tcol[0];
				colorz.rgb[1] = --tcol[1];
				colorz.rgb[2] = ++tcol[2];
				gdImageSetPixel(main, i, z, colorz.colors);

			}
			break;
			}
		}
	}
	return 0;
}


int mxAlphaFlame(gdImagePtr ptr, int iterations)
{
	int i;
	for(i = 0; i < iterations; i++)
	{
		if(output_ == 0) mxMorph(ptr);
		mxBlend(ptrs[rand()%4], ptr);
		if(output_ == 1) mxMorph(ptr);

	}
	return 0;
}

int main(int argc, char **argv)
{
	FILE *fptr[4], *source;
	gdImagePtr image;
	int i, it = 25, small_x, small_y;
	char result[256];


	if(argc != 5)
	{
		printf("Error invalid arguments.\n");
		return -2;

	}

	if(strcmp(argv[4], "-m") == 0) {
		output_ = 0;
	} else if(strcmp(argv[4], "-a") == 0) {
		output_ = 1;
	}

	printf("Opening file list..\n");

	strncpy(result, argv[1], 255);
	source = fopen(argv[1], "r");

	if(source) {
		printf("Loading images..\n");
		for(i=0;i<4;i++)
		{
			fgets(result, 256, source);
			result[strlen(result)-1] = 0;
			fptr[i] = fopen(result,  "rb");
			if(!fptr[i]) { printf("error could not load: [%s]\n", result); exit(-3); }
		}
	} else {
		printf("Error loading images..\n");
		fclose(source);
		fprintf(stdout, "error cannot find file %s\n", argv[1]);
		exit(-2);
	}
	fclose(source);
	it = atoi(argv[2]);
	printf("Creating data from file pointers...\n");
	for(i = 0; i < 4; i++) {
	ptrs[i] =  gdImageCreateFromPng(fptr[i]);
		if(i == 0) { small_x = ptrs[0]->sx; small_y = ptrs[0]->sy; }
		if(ptrs[i]->sx > small_x) small_x = ptrs[i]->sx;
		if(ptrs[i]->sy > small_y) small_y = ptrs[i]->sy;
	}

	image = gdImageCreateTrueColor(small_x,small_y);

	mxAlphaInit(image);
	mxAlphaFlame(image, it);
	printf("Flamed\n");
	{
		FILE *save_ptr = fopen(argv[3], "w");
		if(!save_ptr) { printf("Error could not open output file\n"); exit(-4); }
		gdImagePng(image, save_ptr);
		fclose(save_ptr);
		printf("Saved to file output.png\n");
	}
	printf("Cleaning up..\n");
	for(i = 0; i < 4; i++)
	{
		fclose(fptr[i]);
		gdImageDestroy(ptrs[i]);
	}
	gdImageDestroy(image);
	return EXIT_SUCCESS;
}

