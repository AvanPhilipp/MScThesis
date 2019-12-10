#include "adaptive_thrash.h"

void adaptive_thresh(
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,
		xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst,
//		short int *filter_ptr,
		unsigned char delta,
		unsigned char shift){

	xf::adaptive_hax_filter2D<XF_BORDER_REPLICATE,FILTER_WIDTH,FILTER_HEIGHT,TYPE,TYPE,HEIGHT,WIDTH,NPC1>(_src,_dst,delta,shift);
}
