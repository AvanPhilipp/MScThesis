#include "more_adaptive_thrash.h"

void more_adaptive_thresh(
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst,
		unsigned char delta){

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> filter_src, adder_src;
	filter_src = adder_src = _src;

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_filter(_src.rows,_src.cols);
	xf::boxFilter<XF_BORDER_CONSTANT,FILTER_WIDTH,TYPE,HEIGHT, WIDTH,NPC1>(filter_src,_dst);



//	unsigned char tab[768];
//
//	for(int i = 0; i < 768; i++ ){
//		tab[i] = (unsigned char)(i - 255 > - delta ? 255 : 0);
//	}
//
//	for(int i = 0; i < filter_src.rows; i++ ){
////		const uchar* sdata = _src.pt(i);
////		const uchar* mdata = tmp_1.ptr(i);
////		uchar* ddata = _dst.ptr(i);
//
//		for(int j = 0; j < filter_src.cols; j++ ){
//			_dst.data[i * _dst.cols + j] = tab[_src.data[i * _src.cols + j] - tmp_filter.data[i * tmp_filter.cols + j] + 255];
//		}
//	}
//
//	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_adder(_src.rows,_src.cols);
//	xf::addS<XF_CONVERT_POLICY_SATURATE, TYPE, HEIGHT, WIDTH,NPC1>(adder_src,&delta,tmp_adder);
//
//	for(int i=0;i<tmp_adder.rows; i++){
//		for(int j=0;j<tmp_adder.cols; j++){
//			_dst.data[i * _dst.cols + j] =tmp_adder.data[i * tmp_adder.cols + j] > tmp_filter.data[i * tmp_filter.cols + j] ? 255 : 0;
//		}
//	}
}

void more_adaptive_thresh_accel(
		ap_uint<8> *_src,
		ap_uint<8> *_dst,
		unsigned char delta,
		int height,
		int width){

	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> mat_src(height,width),mat_dst(height,width), filter_src(height,width), adder_src(height,width);

	xf::Array2xfMat<8, TYPE, HEIGHT, WIDTH, NPC1>( _src, mat_src);

//	mat_src.copyTo(_src);

//	mat_dst = mat_src;
//	xf::duplicateMat(mat_src,filter_src,adder_src);
//
//	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_filter(height,width);
	xf::boxFilter<XF_BORDER_CONSTANT,FILTER_WIDTH,TYPE,HEIGHT, WIDTH,NPC1>(mat_src,mat_dst);



//	unsigned char tab[768];
//
//	for(int i = 0; i < 768; i++ ){
//		tab[i] = (unsigned char)(i - 255 > - delta ? 255 : 0);
//	}
//
//	for(int i = 0; i < filter_src.rows; i++ ){
////		const uchar* sdata = _src.pt(i);
////		const uchar* mdata = tmp_1.ptr(i);
////		uchar* ddata = _dst.ptr(i);
//
//		for(int j = 0; j < filter_src.cols; j++ ){
//			_dst.data[i * _dst.cols + j] = tab[_src.data[i * _src.cols + j] - tmp_filter.data[i * tmp_filter.cols + j] + 255];
//		}
//	}
//
//	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> tmp_adder(height,width);
//	xf::addS<XF_CONVERT_POLICY_SATURATE, TYPE, HEIGHT, WIDTH,NPC1>(mat_src,&delta,tmp_adder);
//
//	for(int i=0;i<tmp_adder.rows; i++){
//		for(int j=0;j<tmp_adder.cols; j++){
//			mat_dst.data[i * mat_dst.cols + j] =tmp_adder.data[i * tmp_adder.cols + j] > tmp_filter.data[i * tmp_filter.cols + j] ? 255 : 0;
//		}
//	}

	xf::xfMat2Array<8, TYPE, HEIGHT, WIDTH, NPC1>(mat_dst,_dst);

//	_dst = mat_dst.copyFrom();

//	xf::adaptive_hax_filter2D<XF_BORDER_REPLICATE,FILTER_WIDTH,FILTER_HEIGHT,TYPE,TYPE,HEIGHT,WIDTH,NPC1>(_src,_dst,delta,shift);
}
