#include "hls_stream.h"
//#include "ap_int.h"

#include "common/xf_common.h"
//#include "common/xf_utility.h"
#include "common/xf_infra.h"

#include "imgproc/xf_threshold.hpp"
#include "imgproc/xf_otsuthreshold.hpp"
#include "imgproc/xf_gaussian_filter.hpp"
#include "imgproc/xf_erosion.hpp"
#include "imgproc/xf_dilation.hpp"

#include "setup.h"

#define TYPE 		XF_8UC1
#define HEIGHT		2160
#define WIDTH		3840
#define NPC1 		XF_NPPC1

void preproc_v2(
		hls::stream< ap_axiu<8,1,1,1> >& _src,
		hls::stream< ap_axiu<8,1,1,1> >& _dst,
		unsigned char kernel1[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel2[FILTER_SIZE*FILTER_SIZE],
		unsigned char kernel3[FILTER_SIZE*FILTER_SIZE],
		int height,
		int width);
//void preproc(
//	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &x_src,
//	xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &x_dst,
//	unsigned char kernel[FILTER_SIZE*FILTER_SIZE]);
