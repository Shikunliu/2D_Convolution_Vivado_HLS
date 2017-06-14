#include <stdio.h>
#include <hls_opencv.h>
#include "core.h"
//#include "testUtils.h"

//Blur
/*
  char kernel[KERNEL_DIM*KERNEL_DIM]=
  {
	1,2,1,
	2,3,2,
	1,2,1,
  };
*/

//impulse
/*	char kernel [KERNEL_DIM*KERNEL_DIM]=
	{
	 0,0,0,
	 0,1,0,
	 0,0,0,
	};
*/
//Sobel
/*	char kernel [KERNEL_DIM*KERNEL_DIM]=
	{
	 -1,-2,-1,
	 0,0,0
	 1,2,1,
	};
*/

//Edge
char kernel[KERNEL_DIM*KERNEL_DIM]=
{
	-1,-1,-1,
	-1,8,-1,
	-1,-1,-1,
};


//Use with morphological (Erode, dilate)
/*char kernel[KERNEL_DIM*KERNEL_DIM]
{
	1,1,1,
	1,1,1,
	1,1,1,
};
*/

//Image file path

char outImage[IMG_HEIGHT_OR_ROWS][IMG_WIDTH_OR_COLS];
char outImageRef[IMG_HEIGHT_OR_ROWS][IMG_WIDTH_OR_COLS];

int main()
{
	//Read input image
	printf("Load image %s\n", INPUT_IMAGE_CORE); //INPUT_IMAGE is defined in header file core.h
	cv::Mat imageSrc;  //Create matrix
	imageSrc = cv::imread(INPUT_IMAGE_CORE);// Put image to the matrix
	//Convert to grayscale
	cv::cvtColor(imageSrc, imageSrc, CV_BGR2GRAY);
	printf("Image Rows:%d Cols%d\n", imageSrc.rows, imageSrc.cols);

	//Define stream for input and output
	hls::stream<uint_8_side_channel> inputStream;
	hls::stream<int_8_side_channel> outputStream;

	//OpenCV mat that point to a array (cv::Size(Width, Height))
	cv::Mat imgCvOut(cv::Size(imageSrc.cols, imageSrc.rows), CV_8UC1, outImage, cv::Mat::AUTO_STEP); //Define matrix that output the image, parameters: size of image , saving classification CV_8UC1:3 channels 8 bits unsigned
	cv::Mat imgCvOutRef(cv::Size(imageSrc.cols, imageSrc.rows), CV_8UC1, outImage, cv::Mat::AUTO_STEP);




	//Populate the input stream with the image bytes
	for(int idxRows = 0; idxRows < imageSrc.rows; idxRows++)
	{
		for(int idxCols = 0; idxCols < imageSrc.cols; idxCols++)
		{
			uint_8_side_channel valIn;
			valIn.data = imageSrc.at<unsigned char>(idxRows, idxCols);// at: access a specific pixel
			valIn.keep = 1; valIn.strb = 1; valIn.user = 1; valIn.id = 0; valIn.dest = 0;
			inputStream << valIn; //Put the image into the stream
		}
	}


	/* kun

	//Do the convolution (Reference)
	printf("Calling Reference function\n");
	conv2dByHand(imageSrc, outImageRef, kernel, KERNEL_DIM);
	printf("Reference function ended\n");
	//Save image out file or display
	if (imageSrc.rows < 12)
	{
		printSmallMatrixCVChar("Ref Core", imgCvOutRef);
	}
	else
	{
		printf("Saving image Ref\n");
		saveImage(std::string(OUTPUT_IMAGE_REF), imgCvOutRef);
	}

	kun*/

	//Do the convilution on the core (Third parameter choose operation 0(conv), 1(erode), 2(dilate))
	printf("Calling Core function\n");
	doImgproc(inputStream, outputStream, kernel, 0);
	printf("Core function ended\n");



	//Take data from the output stream to our array outImage (pointed in opencv)
	for (int idxRows = 0; idxRows < imageSrc.rows; idxRows++)
	{
		for (int idxCols = 0; idxCols < imageSrc.cols; idxCols++)
		{
			int_8_side_channel valOut;
			outputStream.read(valOut); //Read out the output stream
			outImage[idxRows][idxCols] = valOut.data; //Save the output image to outImage which is imgCvOut
		}
	}



	//imshow("My Image",imageSrc);
	imwrite(OUTPUT_IMAGE_CORE, imgCvOut);


	/*kun

	//Save image out file or display
	if (imageSrc.rows < 12)
	{
		printSmallMatrixCVChar("Res Core", imgCvOut);
	}
	else
	{
		printf("Saving image\n");
		saveImage(std::string(OUTPUT_IMAGE_CORE), imgCvOut);
	}
	kun*/

	return 0;
}
