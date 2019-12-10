#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "common/xf_infra.h"

#include "kf_custom_convolution.hpp"

#include "common/xf_types.h"


#define TYPE		XF_8UC1
#define HEIGHT		2160
#define WIDTH		3840
#define NPC1 		XF_NPPC1


/*  specify the filter height and filter width  */

#define SHIFT 			0

#define  FILTER_HEIGHT  9
#define  FILTER_WIDTH  	9


/*  set the optimization type  */

#define NO  1  	// Normal Operation
#define RO  0  	// Resource Optimized

/* set the output type */

#define 	OUT_8U  	1
#define 	OUT_16S 	0


void adaptive_thresh(
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst,
//		short int *filter_ptr,
		unsigned char delta,
		unsigned char shift);
