//包含头文件和命名空间
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//全局变量声明
Mat srcImage, grayImage, resultImage;
int num_corners = 23;
int max_corners = 255;
const char* source_win = "亚像素级角点";
//随机数产生器
RNG rng(12345);
//函数声明
void cornersubPix_demo(int, void*);
//主函数
int main(int argc, char** argv) {
	//读取图像
	srcImage = imread("cornerdetector1.PNG");
	if (srcImage.empty()) {
		cout << "could not load image..\n" << endl;
		return -1;
	}
	//创建窗口
	namedWindow("srcImage", WINDOW_AUTOSIZE);
	//显示原图像
	imshow("srcImage", srcImage);
	//把原图像转换成灰度图
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//创建窗口
	namedWindow(source_win, WINDOW_AUTOSIZE);
	//创建滚动条
	createTrackbar("num corners", source_win, &num_corners, max_corners, cornersubPix_demo);
	//初始化
	cornersubPix_demo(0, 0);
	//等待有键按下
	waitKey(0);
	return 0;
}
//函数定义
void cornersubPix_demo(int, void*) {
	//如果角点小于1，按1输出
	if (num_corners < 1) { num_corners = 1; }
	//参数赋值
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	//克隆
	resultImage = srcImage.clone();
	//进行角点检测
	goodFeaturesToTrack(grayImage,
		corners,
		num_corners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		useHarrisDetector,
		k);
	//输出检测到的角点的数量
	cout << "Number of corners detected: " << corners.size() << endl;
	//绘制出被检测的角点
	for (size_t i = 0; i < corners.size(); i++) {
		circle(resultImage, corners[i], 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
	}
	//显示角点检测的结果
	imshow(source_win, resultImage);
	//参数设置
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
	//计算亚像素级角点位置
	cornerSubPix(grayImage, corners, winSize, zeroZone, criteria);
	//输出精准角点坐标信息
	for (int i = 0; i < corners.size(); i++) {
		cout << "["<<i<<"]" << "号角点坐标：" << "("<<corners[i].x<<", "<<corners[i].y<<")" << endl;
	}
}