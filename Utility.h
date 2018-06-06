#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <chrono>

#ifdef __linux
#include <pthreads.h>
#endif // __linux

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#define THREAD_COUNT    8
#define BW_BORDER       64
#define SMOOTH_RES      5

#define BLACK           0
#define WHITE           255

struct count_of_colors
{
	int black;
	int white;
};

typedef struct thread_data
{
	int* input_data;
	int* smooth_data;
	int begin_of_line;
	int end_of_line;
	int cols;
	int rows;

#ifdef _DEBUG
	int ThreadId;
#endif // _DEBUG

} THREAD_DATA, *PTHREAD_DATA;

count_of_colors CheckSurround(const int i, const int j, const cv::Mat_<int> &InputImage);
count_of_colors CheckSurroundThread(const int i, const int j, int* input, const int rows, const int cols);

#ifdef _WIN32
DWORD WINAPI ProcessLine(LPVOID);
#endif // _WIN32

#ifdef __linux
void *ProcessLine(void *data);
#endif // __linux

cv::Mat_<int> SmoothBWImage(const cv::Mat_<int> &InputImage);
int* SmoothBWImage_Parallel(const cv::Mat_<int> &InputImage);

#endif // !UTILITY_H


