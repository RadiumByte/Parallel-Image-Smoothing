#include "Utility.h"

#ifdef _DEBUG
CRITICAL_SECTION section;
#endif // _DEBUG

count_of_colors CheckSurround(const int i, const int j, const cv::Mat_<int> &InputImage)
{
	const int rows = InputImage.rows;
	const int cols = InputImage.cols;

	count_of_colors surround;

	if (i > rows || j > cols || i < 0 || j < 0)
		throw std::domain_error("Index is out of range");

	int count_of_white = 0;
	int count_of_black = 0;

	if ((i > 0 && i < rows - 1) && (j > 0 && j < cols - 1))   // Middle center
	{
		count_of_white += InputImage(i - 1, j - 1);
		count_of_white += InputImage(i - 1, j);
		count_of_white += InputImage(i - 1, j + 1);
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i, j + 1);
		count_of_white += InputImage(i + 1, j - 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white += InputImage(i + 1, j + 1);
		count_of_white /= WHITE;
		count_of_black = 8 - count_of_white;
	}
	else if (i == 0 && j == 0)    // Top left
	{
		count_of_white += InputImage(i, j + 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white += InputImage(i + 1, j + 1);
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if (i == 0 && (j > 0 && j < cols - 1))   // Top center
	{
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i, j + 1);
		count_of_white += InputImage(i + 1, j - 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white += InputImage(i + 1, j + 1);
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if (i == 0 && j == cols - 1)  // Top right
	{
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i + 1, j - 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if ((i > 0 && i < rows - 1) && j == 0) // Middle left
	{
		count_of_white += InputImage(i - 1, j);
		count_of_white += InputImage(i - 1, j + 1);
		count_of_white += InputImage(i, j + 1);
		count_of_white += InputImage(i + 1, j + 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if ((i > 0 && i < rows - 1) && j == cols - 1)  // Middle right
	{
		count_of_white += InputImage(i - 1, j);
		count_of_white += InputImage(i - 1, j - 1);
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i + 1, j - 1);
		count_of_white += InputImage(i + 1, j);
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if (i == rows - 1 && j == 0)  // Bottom left
	{
		count_of_white += InputImage(i - 1, j);
		count_of_white += InputImage(i - 1, j + 1);
		count_of_white += InputImage(i, j + 1);
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if (i == rows - 1 && (j > 0 && j < cols - 1))  // Bottom center
	{
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i - 1, j - 1);
		count_of_white += InputImage(i - 1, j);
		count_of_white += InputImage(i - 1, j + 1);
		count_of_white += InputImage(i, j + 1);
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if (i == rows - 1 && j == cols - 1)   // Bottom right
	{
		count_of_white += InputImage(i, j - 1);
		count_of_white += InputImage(i - 1, j - 1);
		count_of_white += InputImage(i - 1, j);
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}

	surround.black = count_of_black;
	surround.white = count_of_white;
	return surround;
}

count_of_colors CheckSurroundThread(const int i, const int j, int* data, const int rows, const int cols)
{
	count_of_colors surround;

	if (i > rows || j > cols || i < 0 || j < 0)
		throw std::domain_error("Index is out of range");

	int count_of_white = 0;
	int count_of_black = 0;

	if ((i > 0 && i < rows - 1) && (j > 0 && j < cols - 1))   // Middle center
	{
		count_of_white += data[(i - 1)*cols + (j - 1)];
		count_of_white += data[(i - 1)*cols + j];
		count_of_white += data[(i - 1)*cols + (j + 1)];
		count_of_white += data[i*cols + (j - 1)];
		count_of_white += data[i*cols + (j + 1)];
		count_of_white += data[(i + 1)*cols + (j - 1)];
		count_of_white += data[(i + 1)*cols + j];
		count_of_white += data[(i + 1)*cols + (j + 1)];
		count_of_white /= WHITE;
		count_of_black = 8 - count_of_white;
	}
	else if (i == 0 && (j > 0 && j < cols - 1))   // Top center
	{
		count_of_white += data[i*cols + (j - 1)];
		count_of_white += data[i*cols + (j + 1)];
		count_of_white += data[(i + 1)*cols + (j - 1)];
		count_of_white += data[(i + 1)*cols + j];
		count_of_white += data[(i + 1)*cols + (j + 1)];
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if ((i > 0 && i < rows - 1) && j == 0) // Middle left
	{
		count_of_white += data[(i - 1)*cols + j];
		count_of_white += data[(i - 1)*cols + (j + 1)];
		count_of_white += data[i*cols + (j + 1)];
		count_of_white += data[(i + 1)*cols + (j + 1)];
		count_of_white += data[(i + 1)*cols + j];
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if ((i > 0 && i < rows - 1) && j == cols - 1)  // Middle right
	{
		count_of_white += data[(i - 1)*cols + j];
		count_of_white += data[(i - 1)*cols + (j - 1)];
		count_of_white += data[i*cols + (j - 1)];
		count_of_white += data[(i + 1)*cols + (j - 1)];
		count_of_white += data[(i + 1)*cols + j];
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if (i == rows - 1 && (j > 0 && j < cols - 1))  // Bottom center
	{
		count_of_white += data[i*cols + (j - 1)];
		count_of_white += data[(i - 1)*cols + (j - 1)];
		count_of_white += data[(i - 1)*cols + j];
		count_of_white += data[(i - 1)*cols + j + 1];
		count_of_white += data[i*cols + (j + 1)];
		count_of_white /= WHITE;
		count_of_black = 5 - count_of_white;
	}
	else if (i == 0 && j == 0)    // Top left
	{
		count_of_white += data[    i*cols + (j+1)]; 
		count_of_white += data[(i+1)*cols +     j];
		count_of_white += data[(i+1)*cols + (j+1)];
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if (i == 0 && j == cols - 1)  // Top right
	{
		count_of_white += data[    i*cols + (j-1)];
		count_of_white += data[(i+1)*cols + (j-1)];
		count_of_white += data[(i+1)*cols +     j];
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if (i == rows - 1 && j == 0)  // Bottom left
	{
		count_of_white += data[(i - 1)*cols + j];
		count_of_white += data[(i - 1)*cols + (j + 1)];
		count_of_white += data[i*cols + (j + 1)];
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}
	else if (i == rows - 1 && j == cols - 1)   // Bottom right
	{
		count_of_white += data[i*cols + (j - 1)];
		count_of_white += data[(i - 1)*cols + (j - 1)]; 
		count_of_white += data[(i - 1)*cols + j];
		count_of_white /= WHITE;
		count_of_black = 3 - count_of_white;
	}

	surround.black = count_of_black;
	surround.white = count_of_white;
	return surround;
}

cv::Mat_<int> SmoothBWImage(const cv::Mat_<int> &InputImage)
{
	cv::Mat_<int> smoothed_image = InputImage.clone();

	for (int i = 0; i < smoothed_image.rows; ++i)
	{
		for (int j = 0; j < smoothed_image.cols; ++j)
		{
			int color = InputImage(i, j);

			count_of_colors surround = CheckSurround(i, j, InputImage);
			int count_of_white = surround.white;
			int count_of_black = surround.black;

			if (color == WHITE && count_of_black >= SMOOTH_RES)
				smoothed_image(i, j) = BLACK;
			else if (color == BLACK && count_of_white >= SMOOTH_RES)
				smoothed_image(i, j) = WHITE;
		}
	}

	return smoothed_image;
}

#ifdef _WIN32
DWORD WINAPI ProcessLine(LPVOID data)
{
	PTHREAD_DATA data_for_line = (PTHREAD_DATA)data;

	int cols = data_for_line->cols;
	int rows = data_for_line->rows;

	int* raw_input = data_for_line->input_data;
	int* raw_smooth = data_for_line->smooth_data;

	int begin = data_for_line->begin_of_line;
	int end = data_for_line->end_of_line;
	
#ifdef _DEBUG
	int id = data_for_line->ThreadId;

	EnterCriticalSection(&section);
	std::cout << "Thread " << id << " started. Begin: " << begin << "  End: " << end << std::endl;
	LeaveCriticalSection(&section);
#endif // _DEBUG

	for (int i = begin; i <= end; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int color = raw_input[i*cols + j];

			count_of_colors surround = CheckSurroundThread(i, j, raw_smooth, rows, cols);

			int count_of_white = surround.white;
			int count_of_black = surround.black;

			if (color == WHITE && count_of_black >= SMOOTH_RES)
				raw_smooth[i*cols + j] = BLACK;
			else if (color == BLACK && count_of_white >= SMOOTH_RES)
				raw_smooth[i*cols + j] = WHITE;
		}
	}

#ifdef _DEBUG
	EnterCriticalSection(&section);
	std::cout << "Thread " << id << " stopped. Begin: " << begin << "  End: " << end << std::endl;
	LeaveCriticalSection(&section);

#endif // _DEBUG

	return 0;
}

int* SmoothBWImage_Parallel(const cv::Mat_<int> &InputImage)
{
#ifdef _DEBUG
	InitializeCriticalSection(&section);
	std::cout << "Function started." << std::endl;
	std::cout << "Threads to be initialized: " << THREAD_COUNT << std::endl;

#endif // _DEBUG

	int cols = InputImage.cols;
	int rows = InputImage.rows;
	int framesize = cols * rows;
	int line_wigth = rows / THREAD_COUNT;
	int* input_data = (int*)InputImage.data;
	int* smooth_data = (int*)malloc(framesize * sizeof(int));
	memcpy(smooth_data, InputImage.data, framesize * sizeof(int));

	HANDLE thread[THREAD_COUNT];
	DWORD  thrId[THREAD_COUNT];
	THREAD_DATA parameters[THREAD_COUNT];

	int begin = 0;
	int end = line_wigth - 1;

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		parameters[i].cols = cols;
		parameters[i].rows = rows;
		parameters[i].begin_of_line = begin;

		// Line append to last thread
		if (i == THREAD_COUNT - 1)
			parameters[i].end_of_line = rows - 1;
		else
			parameters[i].end_of_line = end;

#ifdef _DEBUG
		parameters[i].ThreadId = i;
#endif // _DEBUG

		parameters[i].smooth_data = smooth_data;
		parameters[i].input_data = input_data;
		
		thread[i] = CreateThread(NULL, 0, &ProcessLine, &parameters[i], 0, &thrId[i]);
		
		begin = end + 1;
		end += line_wigth;
	}
	
	WaitForMultipleObjects(THREAD_COUNT, thread, TRUE, INFINITE);

#ifdef _DEBUG
	DeleteCriticalSection(&section);
#endif // _DEBUG

	return smooth_data;
}
#endif //_WIN32

#ifdef __linux
void *ProcessLine(void *data)
{
	PTHREAD_DATA data_for_line = (PTHREAD_DATA)data;

	int cols = data_for_line->cols;
	int rows = data_for_line->rows;

	int* raw_input = data_for_line->input_data;
	int* raw_smooth = data_for_line->smooth_data;

	int begin = data_for_line->begin_of_line;
	int end = data_for_line->end_of_line;

	for (int i = begin; i <= end; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int color = raw_input[i*cols + j];

			count_of_colors surround = CheckSurroundThread(i, j, raw_smooth, rows, cols);

			int count_of_white = surround.white;
			int count_of_black = surround.black;

			if (color == WHITE && count_of_black >= SMOOTH_RES)
				raw_smooth[i*cols + j] = BLACK;
			else if (color == BLACK && count_of_white >= SMOOTH_RES)
				raw_smooth[i*cols + j] = WHITE;
		}
	}

	return 0;
}

int* SmoothBWImage_Parallel(const cv::Mat_<int> &InputImage)
{
	int cols = InputImage.cols;
	int rows = InputImage.rows;
	int framesize = cols * rows;
	int line_wigth = rows / THREAD_COUNT;
	int* input_data = (int*)InputImage.data;
	int* smooth_data = (int*)malloc(framesize * sizeof(int));
	memcpy(smooth_data, InputImage.data, framesize * sizeof(int));

	pthread_t threads[THREAD_COUNT];
	PTHREAD_DATA parameters[THREAD_COUNT];

	int return_code = 0;

	int begin = 0;
	int end = line_wigth - 1;

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		parameters[i] = (PTHREAD_DATA)malloc(sizeof(THREAD_DATA));
		parameters[i]->cols = cols;
		parameters[i]->rows = rows;
		parameters[i]->begin_of_line = begin;

		// Line append to last thread
		if (i == THREAD_COUNT - 1)
			parameters[i]->end_of_line = rows - 1;
		else
			parameters[i]->end_of_line = end;

		parameters[i]->input_data = input_data;
		parameters[i]->smooth_data = smooth_data;

		return_code = pthread_create(threads[i], NULL, ProcessLine, (void*)&parameters[i]);
		if (return_code)
		{
			std::cout << "Failed to create thread" << std::endl;
			exit(EXIT_FAILURE);
		}

		begin = end + 1;
		end += line_wigth;
	}

	for (int i = 0; i < THREAD_COUNT; ++i)
		pthread_join(threads[i], NULL);

	return smooth_data;
}
#endif // __linux



