#include "Utility.h"

int main()
{
	try
	{
		cv::Mat input_image = cv::imread("test.jpg", CV_LOAD_IMAGE_COLOR);

		if (input_image.empty())
		{
			std::cout << "Could not open or find the image" << std::endl;
			cv::waitKey(0);
			return EXIT_FAILURE;
		}

		//cv::imshow("Input image", input_image);

		cv::Mat gray_image(input_image.size(), CV_8U);
		cv::cvtColor(input_image, gray_image, CV_BGR2GRAY);
		
		cv::Mat bw_image(gray_image.size(), gray_image.type());
		cv::threshold(gray_image, bw_image, BW_BORDER, 255, cv::THRESH_BINARY);
		
		cv::imwrite("smooth_bw.bmp", bw_image);

		std::cout << "Processing in progress..." << std::endl;
		
		std::cout << "Ordinary function called..." << std::endl;
		auto start = std::chrono::system_clock::now();
		cv::Mat_<int> smoothed_image_first = SmoothBWImage(bw_image);
		auto end = std::chrono::system_clock::now();
		auto elapsed = end - start;
		std::cout << "Ordinary time: " << elapsed.count() << std::endl;

		cv::imwrite("smooth_seq.bmp", smoothed_image_first);
		
		std::cout << "Parallel function called" << std::endl;
		start = std::chrono::system_clock::now();
		int* data = SmoothBWImage_Parallel(bw_image);
		cv::Mat_<int> smoothed(bw_image.rows, bw_image.cols, data, bw_image.step * sizeof(int));
		end = std::chrono::system_clock::now();
		elapsed = end - start;
		std::cout << "Parallel time: " << elapsed.count() << std::endl;
		
		cv::imwrite("smooth_par.bmp", smoothed);
		cv::waitKey();

		free(smoothed.data);
	}
	catch (std::exception incoming)
	{
		std::cout << incoming.what() << std::endl;
		cv::waitKey(0);
	}
	system("pause");
	return EXIT_SUCCESS;
}

