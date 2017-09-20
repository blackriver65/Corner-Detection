//����ͷ�ļ��������ռ�
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//ȫ�ֱ�������
Mat srcImage, grayImage, resultImage;
int num_corners = 23;
int max_corners = 255;
//�����������
RNG rng(12345);
//��������
void goodFeaturesToTrack_demo(int, void*);
//������
int main(int argc, char** argv) {
    //��ȡͼ��
	srcImage = imread("Tshi-Tomasi.jpg");
	if (srcImage.empty()) {
		cout << "could not load image..\n" << endl;
		return -1;
	}
	//��������
	namedWindow("srcImage", WINDOW_AUTOSIZE);
	//��ʾԭͼ��
	imshow("srcImage", srcImage);
	//��ԭͼ��ת���ɻҶ�ͼ
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//��������
	namedWindow("Shi-TomasiCorner", WINDOW_AUTOSIZE);
	//����������
	createTrackbar("num corners", "Shi-TomasiCorner", &num_corners, max_corners, goodFeaturesToTrack_demo);
	//��ʼ��
	goodFeaturesToTrack_demo(0, 0);
	//�ȴ��м�����
	waitKey(0);
	return 0;
}
//��������
void goodFeaturesToTrack_demo(int, void*) {
	//����ǵ�С��1����1���
	if (num_corners < 1) { num_corners = 1; }
	//������ֵ
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	//��¡
	resultImage = srcImage.clone();
	//���нǵ���
	goodFeaturesToTrack(grayImage,
		corners,
		num_corners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		useHarrisDetector,
		k);
	//�����⵽�Ľǵ������
     cout << "Number of corners detected: " << corners.size() << endl;
	 //���Ƴ������Ľǵ�
	 for (size_t i = 0; i < corners.size(); i++) {
		 circle(resultImage, corners[i], 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
	 }
	 //��ʾ�ǵ���Ľ��
	 namedWindow("Shi-TomasiCorner", WINDOW_AUTOSIZE);
	 imshow("Shi-TomasiCorner",resultImage);
}