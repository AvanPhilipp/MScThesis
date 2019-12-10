#include "/opt/Xilinx/Vivado/2018.3/include/gmp.h"
#include "preproc.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "common/xf_sw_utils.h"
#include "common/xf_axi.h"

int main(int argc, char **argv){

	if(argc != 2){
		fprintf(stderr,"Invalid Number of Arguments!\nUsage:\n");
		fprintf(stderr,"<Executable Name> <input image path> \n");
		return -1;
	}

	cv::Mat out_img, ocv_ref;
	cv::Mat test_img;
	cv::Mat in_gray, diff;
	cv::Mat tmp_1, tmp_2, tmp_3, tmp_4;

	// reading in the color image
	in_gray = cv::imread(argv[1], 0);

	if (in_gray.data == NULL){
		fprintf(stderr,"Cannot open image at %s\n", argv[1]);
		return 0;
	}

	// create memory for output images
	ocv_ref.create(in_gray.rows,in_gray.cols,CV_8UC1);
	out_img.create(in_gray.rows,in_gray.cols,CV_8UC1);
	diff.create(in_gray.rows,in_gray.cols,CV_8UC1);


	cv::Mat element = cv::getStructuringElement( KERNEL_SHAPE,cv::Size(FILTER_SIZE, FILTER_SIZE), cv::Point(-1, -1));

	unsigned char kernel[FILTER_SIZE*FILTER_SIZE];
	for(int i=0;i<(FILTER_SIZE*FILTER_SIZE);i++){
//		kernel[i]=element.data[i];
		element.data[i]=i+1;
		kernel[i]=i+1;
	}

	cv::erode(in_gray, tmp_1, element, cv::Point(-1, -1), ITERATIONS, cv::BORDER_CONSTANT);
//	cv::erode(test_img, tmp_1, element, cv::Point(-1, -1), ITERATIONS, cv::BORDER_CONSTANT);
	cv::GaussianBlur(tmp_1,tmp_2,cvSize(FILTER_SIZE, FILTER_SIZE),FILTER_SIZE / 6.0,FILTER_SIZE / 6.0,cv::BORDER_CONSTANT);
//	cv::adaptiveThreshold(tmp_2,tmp_3,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,2);
	cv::threshold(tmp_2,tmp_3,128,255,CV_THRESH_BINARY);
	cv::erode(tmp_3, tmp_4, element, cv::Point(-1, -1), ITERATIONS, cv::BORDER_CONSTANT);
	cv::dilate(tmp_4, ocv_ref, element, cv::Point(-1, -1), ITERATIONS, cv::BORDER_CONSTANT);

	cv::imwrite("out_ocv.jpg", ocv_ref);


	hls::stream< ap_axiu<8,1,1,1> > _src,_dst;

	cvMat2AXIvideoxf<NPC1>(in_gray, _src);

	preproc(_src,_dst,kernel,kernel,kernel,in_gray.rows,in_gray.cols);

	AXIvideo2cvMatxf<NPC1>(_dst, out_img);

	cv::imwrite("hls_out.jpg",out_img);

	cv::absdiff(ocv_ref, out_img, diff);
	cv::imwrite("error.png", diff);

	std::cout<< CV_VERSION<<std::endl;
		double minval = 256, maxval = 0;
		int cnt = 0;
		for (int i = 0; i < in_gray.rows; i++) {
			for (int j = 0; j < in_gray.cols; j++) {
				uchar v = diff.at<uchar>(i, j);
				if (v > 0)
					cnt++;
				if (minval > v)
					minval = v;
				if (maxval < v)
					maxval = v;
			}
		}
		float err_per = 100.0 * (float) cnt / (in_gray.rows * in_gray.cols);
		printf(
				"Minimum error in intensity = %f\n\
Maximum error in intensity = %f\n\
Percentage of pixels above error threshold = %f\n",
				minval, maxval, err_per);

		if(err_per > 1){
			printf("\nTest failed\n");
			return -1;
		}
		else{
			printf("\nTest Pass\n");
		return 0;
		}





	return 0;
}
