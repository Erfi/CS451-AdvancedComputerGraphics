/*
Ryan Brandt & Erfan Azad
Date: 31 March 2015
File: npr.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Image.h"
#include "npr.h"

void toGreyscale(Image* src){
	int i, j;
	double avg;
	for(i=0; i<src->rows; i++){
		for(j=0; j<src->cols; j++){
			avg = (src->data[i][j].rgb[0] + src->data[i][j].rgb[1] + src->data[i][j].rgb[2])/3;
			src->data[i][j].rgb[0] = avg;
			src->data[i][j].rgb[1] = avg;
			src->data[i][j].rgb[2] = avg;
		}
	}
}

void gaussFilter(Image* src, Kernel* k){
	int i, j, x, y;
	double sum[3];
	for(i=2; i<src->rows-2; i++){
		for (j=2; j<src->cols-2; j++){ //for each inside pixel
			sum[0] =0;
			sum[1] =0;
			sum[2] =0;
			for(x=-2; x<=2; x++){
				for(y=-2; y<=2; y++){
					sum[0] += src->data[i+x][j+y].rgb[0] * k->mat[x+2][y+2];
					sum[1] += src->data[i+x][j+y].rgb[1] * k->mat[x+2][y+2];
					sum[2] += src->data[i+x][j+y].rgb[2] * k->mat[x+2][y+2];
				}
			}
			src->data[i][j].rgb[0] = sum[0];
			src->data[i][j].rgb[1] = sum[1];
			src->data[i][j].rgb[2] = sum[2];
		}
	}

}

void kernel_create(Kernel *k, float sigma){
	if(sigma > 0){
		double s = 2 * sigma *sigma;
		double sum = 0;
		double r;

		int x,y;
		for(x=-2; x<= 2; x++){
			for(y=-2; y<=2; y++){
				r = x*x + y*y;
				k->mat[x+2][y+2] = (exp(-(r/s))/(M_PI*s));
				sum += k->mat[x+2][y+2];
			}
		}

		//Normalize
		for(x=0; x<5; x++){
			for(y=0; y<5; y++){
				k->mat[x][y] /= sum;
			}
		}
	}
}

void kernel_print(Kernel* kernel){
	printf("Gauss's Kernel: ");
	int x, y;
	printf("\n");
	for(x=0; x<5; x++){
		for(y=0; y<5; y++){
			printf(" %f ", kernel->mat[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

//creates a bigger image from the "src" image by 2xp border and fills the border with 
//near by pixels
Image* borderCreate(Image* src){
	if(src != NULL){
		Image* border = image_create(src->rows+4,src->cols+4);
		int i,j;
		// apply blank border around src image
		for (i = 2; i < border->rows-2; i++){
			for (j = 2; j < border->cols-2; j++){
				border->data[i][j] = src->data[i-2][j-2];
			}
		}

		// filling the border with values
		// Upper Left Corner
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				border->data[i][j] = src->data[0][0];
			}
		}

		// upper Right corner
		for (i = 0; i < 3; i++)
		{
			for (j = border->cols-3; j < border->cols; j++)
			{
				border->data[i][j] = src->data[0][src->cols-1];
			}
		}

				// lower left corner
		for (i = src->rows+1; i < src->rows+4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				border->data[i][j] = src->data[src->rows-1][0];
			}
		}

		// lower right
		for (i = src->rows+1; i < src->rows+4; i++)
		{
			for (j = src->cols+1;  j< src->cols+4; j++)
			{
				border->data[i][j] = src->data[src->rows-1][src->cols-1];
			}
		}

		// upside
		for (i = 3; i < src->cols+1; i++)
		{
			border->data[1][i] = src->data[0][i-2];
			border->data[0][i] = src->data[0][i-2];
		}

		// downside
		for (i = 3; i < src->cols+1; i++)
		{
			border->data[src->rows+2][i] = src->data[src->rows-1][i-2];
			border->data[src->rows+3][i] = src->data[src->rows-1][i-2];
		}

		// left
		for (i = 3; i < src->rows+1; i++)
		{
			border->data[i][0] = src->data[i-2][0];
			border->data[i][1] = src->data[i-2][0];
		}
		// right
		for (i = 3; i < src->rows+1; i++)
		{
			border->data[i][src->cols+2] = src->data[i-2][src->cols-1];
			border->data[i][src->cols+3] = src->data[i-2][src->cols-1];
		}
		return border;
	}
	return NULL;

}

//creates an image by removing a 2px border from the input image
Image* borderRemoval(Image* src){
	int i,j;
	Image *removed = image_create(src->rows-4,src->cols-4);
	for (i = 2; i < src->rows-2; i++){
		for (j = 2; j < src->cols-2; j++){
			removed->data[i-2][j-2] = src->data[i][j];
		}
	}
	return removed;
}

//initializes the values of Gx and Gy in the SobelOperator
void sobel_create(SobelOperator* sop){
	sop->Gx[0][0] = -1;
	sop->Gx[0][1] = 0;
	sop->Gx[0][2] = 1;
	sop->Gx[1][0] = -2;
	sop->Gx[1][1] = 0;
	sop->Gx[1][2] = 2;
	sop->Gx[2][0] = -1;
	sop->Gx[2][1] = 0;
	sop->Gx[2][2] = 1;

	sop->Gy[0][0] = -1;
	sop->Gy[0][1] = -2;
	sop->Gy[0][2] = -1;
	sop->Gy[1][0] = 0;
	sop->Gy[1][1] = 0;
	sop->Gy[1][2] = 0;
	sop->Gy[2][0] = 1;
	sop->Gy[2][1] = 2;
	sop->Gy[2][2] = 1;
}

void sobel_print(SobelOperator* sop){
	int i, j;
	printf("\nSobel Operator: Gx\n");
	for(i=0; i<3; i++){
		for(j=0; j<3 ; j++){
			printf(" %d ",sop->Gx[i][j]);
		}
		printf("\n");
	}

	printf("\nSobel Operator: Gy\n");
	for(i=0; i<3; i++){
		for(j=0; j<3 ; j++){
			printf(" %d ",sop->Gy[i][j]);
		}
		printf("\n");
	}
}

//applies the sobel operator to each (inner >> not the borders!) pixel of the "border" image
//and puts the result in "sobelMask"
void sobelFilter(Image* border, Image* sobelMask, SobelOperator* sop){
	int i, j, k, l;
	double sumx[3];
	double sumy[3];
	for (i=0; i<sobelMask->rows; i++){
		for(j=0; j<sobelMask->cols; j++){
			sumx[0] =0;
			sumx[1] =0;
			sumx[2] =0;

			sumy[0] =0;
			sumy[1] =0;
			sumy[2] =0;
			for(k=-1; k<=1; k++){
				for(l=-1; l<=1; l++){
					sumx[0] += border->data[i+2+k][j+2+l].rgb[0] * sop->Gx[k+1][l+1];
					sumx[1] += border->data[i+2+k][j+2+l].rgb[1] * sop->Gx[k+1][l+1];
					sumx[2] += border->data[i+2+k][j+2+l].rgb[2] * sop->Gx[k+1][l+1];

					sumy[0] += border->data[i+2+k][j+2+l].rgb[0] * sop->Gy[k+1][l+1];
					sumy[1] += border->data[i+2+k][j+2+l].rgb[1] * sop->Gy[k+1][l+1];
					sumy[2] += border->data[i+2+k][j+2+l].rgb[2] * sop->Gy[k+1][l+1];
				}
			} 
			sobelMask->data[i][j].rgb[0] = sqrt(sumx[0]*sumx[0] + sumy[0]*sumy[0]);
			sobelMask->data[i][j].rgb[1] = sqrt(sumx[1]*sumx[1] + sumy[1]*sumy[1]); 
			sobelMask->data[i][j].rgb[2] = sqrt(sumx[2]*sumx[2] + sumy[2]*sumy[2]);

			sobelMask->data[i][j].Gx = sumx[0]; //assuming grey scale
			sobelMask->data[i][j].Gy = sumy[0]; //assuming grey scale

			//We are assuming that the picture is grey scale and the first channel (red) gives a 
			//good representation of the theta angle
			double tempAngle =0;
			tempAngle = (atan2(sobelMask->data[i][j].Gx,sobelMask->data[i][j].Gy)/M_PI) * 180.0;


			// if(sumx[0] != 0){
			// 	tempAngle = atan(sumy[0]/sumx[0])*180/M_PI;
			// }else{
			// 	tempAngle = 90;
			// }
			// printf("angle: %f\n", tempAngle);
			// if(tempAngle <0){ //just to change the range of 0 : -90 to 180:90 for easier underestanding  
			// 	tempAngle += 180;
			// }
			// printf("angle after: %f\n", tempAngle);
			//categorizing the angles to 0, 45, 90, 135
			// if((tempAngle >=0 && tempAngle <22.5) || (tempAngle >157.5 && tempAngle <=180)){ //0:22.5 && 157.5:180
			// 	sobelMask->data[i][j].theta = 0;
			// }else if(tempAngle >= 22.5 && tempAngle < 67.5){ //22.5:67.5
			// 	sobelMask->data[i][j].theta = 45;
			// }else if(tempAngle >= 67.5 && tempAngle <112.5){ //67.5:112.5
			// 	sobelMask->data[i][j].theta = 90;
			// }else{											//112.5:157.5
			// 	sobelMask->data[i][j].theta = 135;
			// }
			// printf("Theta: %d\n", sobelMask->data[i][j].theta);

			/* Convert actual edge direction to approximate value */
			if ( ( (tempAngle < 22.5) && (tempAngle > -22.5) ) || (tempAngle > 157.5) || (tempAngle < -157.5) )
				sobelMask->data[i][j].theta = 0;
			if ( ( (tempAngle > 22.5) && (tempAngle < 67.5) ) || ( (tempAngle < -112.5) && (tempAngle > -157.5) ) )
				sobelMask->data[i][j].theta = 45;
			if ( ( (tempAngle > 67.5) && (tempAngle < 112.5) ) || ( (tempAngle < -67.5) && (tempAngle > -112.5) ) )
				sobelMask->data[i][j].theta = 90;
			if ( ( (tempAngle > 112.5) && (tempAngle < 157.5) ) || ( (tempAngle < -22.5) && (tempAngle > -67.5) ) )
				sobelMask->data[i][j].theta = 135;
		}

	}

}

//the input is assumed to be a greyscale image
void nonMaxSuppression(Image* src, Image* buffer){
	int i,j;
	for(i=0; i<src->rows; i++){
		for(j=0; j<src->cols; j++){
			if(i==0 || i==src->rows-1 || j==0 || j==src->cols-1){ //if border then make it black (temporary solution)
				buffer->data[i][j].rgb[0] = 0;
				buffer->data[i][j].rgb[1] = 0;
				buffer->data[i][j].rgb[2] = 0;
				buffer->data[i][j].theta = src->data[i][j].theta;
				buffer->data[i][j].Gx = src->data[i][j].Gx;
				buffer->data[i][j].Gy = src->data[i][j].Gy;
				continue;
			}
			if(src->data[i][j].theta == 0){
				if((src->data[i][j].rgb[0] < src->data[i-1][j].rgb[0]) || (src->data[i][j].rgb[0] < src->data[i+1][j].rgb[0])){
					buffer->data[i][j].rgb[0] = 0;
					buffer->data[i][j].rgb[1] = 0;
					buffer->data[i][j].rgb[2] = 0;
				}else{
					buffer->data[i][j].rgb[0] = src->data[i][j].rgb[0];
					buffer->data[i][j].rgb[1] = src->data[i][j].rgb[1];
					buffer->data[i][j].rgb[2] = src->data[i][j].rgb[2];
				}
			}else if(src->data[i][j].theta == 45){
				if((src->data[i][j].rgb[0] < src->data[i-1][j-1].rgb[0]) || (src->data[i][j].rgb[0] < src->data[i+1][j+1].rgb[0])){
					buffer->data[i][j].rgb[0] = 0;
					buffer->data[i][j].rgb[1] = 0;
					buffer->data[i][j].rgb[2] = 0;
				}else{
					buffer->data[i][j].rgb[0] = src->data[i][j].rgb[0];
					buffer->data[i][j].rgb[1] = src->data[i][j].rgb[1];
					buffer->data[i][j].rgb[2] = src->data[i][j].rgb[2];
				}
			}else if(src->data[i][j].theta == 90){
				if((src->data[i][j].rgb[0] < src->data[i][j-1].rgb[0]) || (src->data[i][j].rgb[0] < src->data[i][j+1].rgb[0])){
					buffer->data[i][j].rgb[0] = 0;
					buffer->data[i][j].rgb[1] = 0;
					buffer->data[i][j].rgb[2] = 0;
				}else{
					buffer->data[i][j].rgb[0] = src->data[i][j].rgb[0];
					buffer->data[i][j].rgb[1] = src->data[i][j].rgb[1];
					buffer->data[i][j].rgb[2] = src->data[i][j].rgb[2];
				}
			}else if(src->data[i][j].theta == 135){
				if((src->data[i][j].rgb[0] < src->data[i-1][j+1].rgb[0]) || (src->data[i][j].rgb[0] < src->data[i+1][j-1].rgb[0])){
					buffer->data[i][j].rgb[0] = 0;
					buffer->data[i][j].rgb[1] = 0;
					buffer->data[i][j].rgb[2] = 0;
				}else{
					buffer->data[i][j].rgb[0] = src->data[i][j].rgb[0];
					buffer->data[i][j].rgb[1] = src->data[i][j].rgb[1];
					buffer->data[i][j].rgb[2] = src->data[i][j].rgb[2];
				}
			}
			buffer->data[i][j].theta = src->data[i][j].theta;
			buffer->data[i][j].Gx = src->data[i][j].Gx;
			buffer->data[i][j].Gy = src->data[i][j].Gy;
		}
	}
}

void doubleThreshold(Image* src, double high, double low){
	int i, j;
	for(i=0; i<src->rows; i++){
		for(j=0; j<src->cols; j++){
			if(src->data[i][j].rgb[0] >= high){
				src->data[i][j].rgb[0] = 1;
				src->data[i][j].rgb[1] = 1;
				src->data[i][j].rgb[2] = 1;
			}else if(src->data[i][j].rgb[0] >= low){
				src->data[i][j].rgb[0] = 0.5;
				src->data[i][j].rgb[1] = 0.5;
				src->data[i][j].rgb[2] = 0.5;
			}
		}
	}
}

void hysteresis(Image* src){
	int i, j;
	for(i=1; i<src->rows-1; i++){
		for(j=0; j<src->cols-1; j++){
			if(src->data[i][j].rgb[0] == 1){//if you have found a start to an edge (assuming grey scale image)
				//check 8 neighboring pixels
				if(src->data[i-1][j-1].rgb[0] == 0.5){
					src->data[i-1][j-1].rgb[0] = 1;
					src->data[i-1][j-1].rgb[1] = 1;
					src->data[i-1][j-1].rgb[2] = 1;
				}
				if(src->data[i-1][j].rgb[0] == 0.5){
					src->data[i-1][j].rgb[0] = 1;
					src->data[i-1][j].rgb[1] = 1;
					src->data[i-1][j].rgb[2] = 1;
				}
				if(src->data[i-1][j+1].rgb[0] == 0.5){
					src->data[i-1][j+1].rgb[0] = 1;
					src->data[i-1][j+1].rgb[1] = 1;
					src->data[i-1][j+1].rgb[2] = 1;
				}
				if(src->data[i][j-1].rgb[0] == 0.5){
					src->data[i][j-1].rgb[0] = 1;
					src->data[i][j-1].rgb[1] = 1;
					src->data[i][j-1].rgb[2] = 1;
				}
				if(src->data[i][j+1].rgb[0] == 0.5){
					src->data[i][j+1].rgb[0] = 1;
					src->data[i][j+1].rgb[1] = 1;
					src->data[i][j+1].rgb[2] = 1;
				}
				if(src->data[i+1][j-1].rgb[0] == 0.5){
					src->data[i+1][j-1].rgb[0] = 1;
					src->data[i+1][j-1].rgb[1] = 1;
					src->data[i+1][j-1].rgb[2] = 1;
				}
				if(src->data[i+1][j].rgb[0] == 0.5){
					src->data[i+1][j].rgb[0] = 1;
					src->data[i+1][j].rgb[1] = 1;
					src->data[i+1][j].rgb[2] = 1;
				}
				if(src->data[i+1][j+1].rgb[0] == 0.5){
					src->data[i+1][j+1].rgb[0] = 1;
					src->data[i+1][j+1].rgb[1] = 1;
					src->data[i+1][j+1].rgb[2] = 1;
				}	
			}
		}
	}
	//backward
	for(i=src->rows-2; i>0; i--){
		for(j=src->cols-2; j>0; j--){
			if(src->data[i][j].rgb[0] == 1){//if you have found a start to an edge (assuming grey scale image)
				//check 8 neighboring pixels
				if(src->data[i-1][j-1].rgb[0] == 0.5){
					src->data[i-1][j-1].rgb[0] = 1;
					src->data[i-1][j-1].rgb[1] = 1;
					src->data[i-1][j-1].rgb[2] = 1;
				}
				if(src->data[i-1][j].rgb[0] == 0.5){
					src->data[i-1][j].rgb[0] = 1;
					src->data[i-1][j].rgb[1] = 1;
					src->data[i-1][j].rgb[2] = 1;
				}
				if(src->data[i-1][j+1].rgb[0] == 0.5){
					src->data[i-1][j+1].rgb[0] = 1;
					src->data[i-1][j+1].rgb[1] = 1;
					src->data[i-1][j+1].rgb[2] = 1;
				}
				if(src->data[i][j-1].rgb[0] == 0.5){
					src->data[i][j-1].rgb[0] = 1;
					src->data[i][j-1].rgb[1] = 1;
					src->data[i][j-1].rgb[2] = 1;
				}
				if(src->data[i][j+1].rgb[0] == 0.5){
					src->data[i][j+1].rgb[0] = 1;
					src->data[i][j+1].rgb[1] = 1;
					src->data[i][j+1].rgb[2] = 1;
				}
				if(src->data[i+1][j-1].rgb[0] == 0.5){
					src->data[i+1][j-1].rgb[0] = 1;
					src->data[i+1][j-1].rgb[1] = 1;
					src->data[i+1][j-1].rgb[2] = 1;
				}
				if(src->data[i+1][j].rgb[0] == 0.5){
					src->data[i+1][j].rgb[0] = 1;
					src->data[i+1][j].rgb[1] = 1;
					src->data[i+1][j].rgb[2] = 1;
				}
				if(src->data[i+1][j+1].rgb[0] == 0.5){
					src->data[i+1][j+1].rgb[0] = 1;
					src->data[i+1][j+1].rgb[1] = 1;
					src->data[i+1][j+1].rgb[2] = 1;
				}	
			}
		}
	}

	//suppression
	for(i=0; i<src->rows; i++){
		for(j=0; j<src->cols; j++){
			if(src->data[i][j].rgb[0] <= 0.5){
				src->data[i][j].rgb[0] = 0;
				src->data[i][j].rgb[1] = 0;
				src->data[i][j].rgb[2] = 0;
			}
		}
	}
}


/*
croppes the border of an image "src" by "n" pixels 
*/
Image* cropBorder(Image* src, int n){
	Image* cropped = NULL;
	if(n < src->cols/2 && n < src->rows){
		int i, j;
		cropped = image_create(src->rows-n , src->cols-n);
		for(i=0; i<cropped->rows; i++){
			for(j=0; j< cropped->cols; j++){
				cropped->data[i][j].rgb[0] = src->data[i+n][j+n].rgb[0];
				cropped->data[i][j].rgb[1] = src->data[i+n][j+n].rgb[1];
				cropped->data[i][j].rgb[2] = src->data[i+n][j+n].rgb[2];
				cropped->data[i][j].theta = src->data[i+n][j+n].theta;
				cropped->data[i][j].Gx = src->data[i+n][j+n].Gx;
				cropped->data[i][j].Gy = src->data[i+n][j+n].Gy;

			}
		}
	}
	return cropped;
}


Image* cannyEdgeDetect(Image* src, float sigma, double T_high, double T_low){
	Image* sobelMask;//to record the result after sobel operator applied
	Image* border;//to hold the blured image with extended borders
	Image* nonMaxSuppressionBuffer; //to hold the image after the non maximal suppression is applied
	Kernel k;//to hold the gaussian filter convolution matrix
	SobelOperator sop;//holds the sobel operators for horizontal and vertical axis (Gx & Gy)

	sobelMask = image_create(src->rows, src->cols);
	border = borderCreate(src);
	nonMaxSuppressionBuffer = image_create(sobelMask->rows, sobelMask->cols);

	//bluer
	kernel_create(&k,sigma);
	kernel_print(&k);
	gaussFilter(border, &k);
	image_write(border, "../images/CLAS/CLASSS/Step1_gauss.ppm");

	//greyscale
	toGreyscale(border);
	image_write(border, "../images/CLAS/CLASSS/Step2_greyScale.ppm");

	//gradient
	sobel_create(&sop);
	sobel_print(&sop);
	sobelFilter(border, sobelMask, &sop);
	image_write(sobelMask, "../images/CLAS/CLASSS/Step3_gradient.ppm");

	//non maximal suppression
	nonMaxSuppression(sobelMask, nonMaxSuppressionBuffer);
	image_write(nonMaxSuppressionBuffer, "../images/CLAS/CLASSS/Step4_NonMaxSuppression.ppm");

	//double threshold
	doubleThreshold(nonMaxSuppressionBuffer, T_high, T_low);
	image_write(nonMaxSuppressionBuffer, "../images/CLAS/CLASSS/Step5_doubleThreshold.ppm");		

	//hysterisis 
	hysteresis(nonMaxSuppressionBuffer);
	image_write(nonMaxSuppressionBuffer, "../images/CLAS/CLASSS/Step6_Hysterisis.ppm");


	//free images
	image_free(border);
	image_free(sobelMask);	

	return nonMaxSuppressionBuffer;
}

Image* alphaBlend(Image* src, Image* edgeMask){
	Image* result = NULL;
	if(src != NULL && edgeMask != NULL){
		result = image_create(src->rows, src->cols);
		int i, j;
		for(i=0; i<src->rows; i++){
			for(j=0; j<src->cols; j++){
				if(edgeMask->data[i][j].rgb[0] != 0){ //assuming greyscale imageMask
					result->data[i][j].rgb[0] = (1-edgeMask->data[i][j].rgb[0])*src->data[i][j].rgb[0];
					result->data[i][j].rgb[1] = (1-edgeMask->data[i][j].rgb[0])*src->data[i][j].rgb[1];
					result->data[i][j].rgb[2] = (1-edgeMask->data[i][j].rgb[0])*src->data[i][j].rgb[2];  
				}else{
					result->data[i][j].rgb[0] = src->data[i][j].rgb[0];
					result->data[i][j].rgb[1] = src->data[i][j].rgb[1];
					result->data[i][j].rgb[2] = src->data[i][j].rgb[2];
				}
				result->data[i][j].theta = edgeMask->data[i][j].theta;
			}
		}
	}
	return result;
}


//used to thiken the edges in the edge mask
void thickenLines(Image* edgeMask, Image* thickMask, int thickness){
	if(edgeMask != NULL && thickMask != NULL){
		int i, j, k;
		for(i=0; i<edgeMask->rows; i++){
			for(j=0; j<edgeMask->cols; j++){
				if(edgeMask->data[i][j].rgb[0] == 1){//assuming grey scale (if edge)
					thickMask->data[i][j].rgb[0] = 1;
					thickMask->data[i][j].rgb[1] = 1;
					thickMask->data[i][j].rgb[2] = 1;
					switch(edgeMask->data[i][j].theta){
						case 0:
							if(i- thickness >= 0){
								for(k=0; k<=thickness; k++){
									thickMask->data[i-k][j].rgb[0] = 1;
									thickMask->data[i-k][j].rgb[1] = 1;
									thickMask->data[i-k][j].rgb[2] = 1;
								}
							}
							if(i+ thickness < edgeMask->rows){
								for(k=0; k<=thickness; k++){
									thickMask->data[i+k][j].rgb[0] = 1;
									thickMask->data[i+k][j].rgb[1] = 1;
									thickMask->data[i+k][j].rgb[2] = 1;
								}
							}
							break;

						case 45:
							if(i- thickness >= 0){
								for(k=0; k<= thickness; k++){
									thickMask->data[i-k][j].rgb[0] = 1;
									thickMask->data[i-k][j].rgb[1] = 1;
									thickMask->data[i-k][j].rgb[2] = 1;
								}
							}
							if(i+ thickness < edgeMask->rows){
								for(k=0; k<= thickness; k++){
									thickMask->data[i+k][j].rgb[0] = 1;
									thickMask->data[i+k][j].rgb[1] = 1;
									thickMask->data[i+k][j].rgb[2] = 1;
								}
							}
							if(j- thickness >= 0){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j-k].rgb[0] = 1;
									thickMask->data[i][j-k].rgb[1] = 1;
									thickMask->data[i][j-k].rgb[2] = 1;
								}
							}
							if(j+ thickness < edgeMask->cols){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j+k].rgb[0] = 1;
									thickMask->data[i][j+k].rgb[1] = 1;
									thickMask->data[i][j+k].rgb[2] = 1;
								}
							}
							break;

						case 90:
							if(j- thickness >= 0){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j-k].rgb[0] = 1;
									thickMask->data[i][j-k].rgb[1] = 1;
									thickMask->data[i][j-k].rgb[2] = 1;
								}
							}
							if(j+ thickness < edgeMask->cols){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j+k].rgb[0] = 1;
									thickMask->data[i][j+k].rgb[1] = 1;
									thickMask->data[i][j+k].rgb[2] = 1;
								}
							}
							break;

						case 135: //same as 45
							if(i- thickness >= 0){
								for(k=0; k<= thickness; k++){
									thickMask->data[i-k][j].rgb[0] = 1;
									thickMask->data[i-k][j].rgb[1] = 1;
									thickMask->data[i-k][j].rgb[2] = 1;
								}
							}
							if(i+ thickness < edgeMask->rows){
								for(k=0; k<= thickness; k++){
									thickMask->data[i+k][j].rgb[0] = 1;
									thickMask->data[i+k][j].rgb[1] = 1;
									thickMask->data[i+k][j].rgb[2] = 1;
								}
							}
							if(j- thickness >= 0){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j-k].rgb[0] = 1;
									thickMask->data[i][j-k].rgb[1] = 1;
									thickMask->data[i][j-k].rgb[2] = 1;
								}
							}
							if(j+ thickness < edgeMask->cols){
								for(k=0; k<= thickness; k++){
									thickMask->data[i][j+k].rgb[0] = 1;
									thickMask->data[i][j+k].rgb[1] = 1;
									thickMask->data[i][j+k].rgb[2] = 1;
								}
							}
							break;
					}
				}
			}
		}
	}
}





