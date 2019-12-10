#include "preproc.v2.h"

void preproc_v2(
		unsigned char src_img_data[HEIGHT*WIDTH],
		unsigned char dst_img_data[HEIGHT*WIDTH],
		unsigned char kernel1[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel2[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel3[FILTER_SIZE*FILTER_SIZE],
		int height,
		int width){

	hls::stream< ap_axiu<8,1,1,1> >& src_stream;
	hls::stream< ap_axiu<8,1,1,1> >& dst_stream;

	for(int i=0; i<height; i++){
		for(int j=0; j<height; j++){
			ap_axiu<8,1,1,1> tmp;
			tmp.data = src_img_data[i][j];
			tmp.user =
			src_stream.write(tmp);
		}
	}


	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> x_src(height,width);
	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> x_dst(height,width);

	xf::AXIvideo2xfMat(src_stream, x_src);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_1(height,width);
	xf::erode<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(x_src,tmp_1, kernel1);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_2(height,width);
	xf::GaussianBlur<XF_FILTER_5X5,XF_BORDER_CONSTANT,TYPE,HEIGHT,WIDTH, NPC1>(tmp_1, tmp_2, 1);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_3(height,width);
	unsigned char Otsuval;
//	xf::OtsuThreshold<TYPE, HEIGHT, WIDTH, NPC1>(tmp_2, Otsuval);
	xf::Threshold<THRESH_TYPE,TYPE,HEIGHT,WIDTH,NPC1>(tmp_2, tmp_3,128,255);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_4(height,width);
	xf::erode<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(tmp_3, tmp_4, kernel2);

	xf::dilate<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(tmp_4,x_dst, kernel3);

	xf::xfMat2AXIvideo(x_dst, dst_stream);


	for(int i=0; i<height; i++){
		for(int j=0; j<height; j++){

		}
	}
}
