#include "/opt/Xilinx/Vivado/2018.3/include/gmp.h"
//#include "more_adaptive_thrash.h"
#include "preproc.h"


//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "common/xf_sw_utils.h"

void preproc(
		hls::stream< ap_axiu<8,1,1,1> >& _src,
		hls::stream< ap_axiu<8,1,1,1> >& _dst,
		unsigned char kernel1[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel2[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel3[FILTER_SIZE*FILTER_SIZE],
		uint32_t height,
		uint32_t width){

#pragma HLS INTERFACE m_axi depth=1024 port=kernel1 offset=slave bundle=kernel1
#pragma HLS INTERFACE m_axi depth=1024 port=kernel2 offset=slave bundle=kernel2
#pragma HLS INTERFACE m_axi depth=1024 port=kernel3 offset=slave bundle=kernel3
#pragma HLS INTERFACE s_axilite port=width
#pragma HLS INTERFACE s_axilite port=height
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both port=_dst
#pragma HLS INTERFACE axis register both port=_src
#pragma HLS DATAFLOW

/*	unsigned char kernel1_tmp[FILTER_SIZE*FILTER_SIZE];
	for(int i=0;i<FILTER_SIZE*FILTER_SIZE;i++){
		kernel1_tmp[i]=kernel1[i];
	}*/

	 xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> x_src(height,width);
#pragma HLS STREAM variable=x_src.data depth=1 dim=1
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> x_dst(height,width);
#pragma HLS STREAM variable=x_dst.data depth=1 dim=1

	xf::AXIvideo2xfMat(_src, x_src);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_1(height,width);
#pragma HLS STREAM variable=tmp_1.data depth=1 dim=1
	xf::erode<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(x_src,tmp_1, kernel1);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_2(height,width);
#pragma HLS STREAM variable=tmp_2.data depth=1 dim=1
	xf::GaussianBlur<XF_FILTER_5X5,XF_BORDER_CONSTANT,TYPE,HEIGHT,WIDTH, NPC1>(tmp_1, tmp_2, 1);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_3(height,width);
#pragma HLS STREAM variable=tmp_3.data depth=1 dim=1
	unsigned char Otsuval;
//	xf::OtsuThreshold<TYPE, HEIGHT, WIDTH, NPC1>(tmp_2, Otsuval);
	xf::Threshold<THRESH_TYPE,TYPE,HEIGHT,WIDTH,NPC1>(tmp_2, tmp_3,128,255);
//	more_adaptive_thresh(tmp_2,tmp_3,2);

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_4(height,width);
#pragma HLS STREAM variable=tmp_4.data depth=1 dim=1
	xf::erode<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(tmp_3, tmp_4, kernel2);

	xf::dilate<XF_BORDER_REPLICATE,TYPE,HEIGHT, WIDTH,KERNEL_SHAPE,FILTER_SIZE,FILTER_SIZE,ITERATIONS,NPC1>(tmp_4,x_dst, kernel3);

	xf::xfMat2AXIvideo(x_dst, _dst);
}
