//����ͷ�ļ��������ռ�
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//ȫ�ֱ�������
Mat srcImage, grayImage, dstImage, normImage, Scalednorm, resultImage;
int  thresh = 125;
int max_thresh = 255;
//ȫ�ֺ�������
void Harris_Conner(int, void*);
//������
int main(int argc, char** argv) {
	//��ȡ����ͼ��
	srcImage = imread("harris.png");
	if (srcImage.empty()) {
		cout << "could not load srcimage...\n" << endl;
		return -1;
	}
	//��������
	namedWindow("srcImage", WINDOW_AUTOSIZE);
	//��ʾԭͼ��
	imshow("srcImage", srcImage);
	//��ԭͼ��ת���ɻҶ�ͼ
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//�������ں͹�����
	namedWindow("HarrisConnerDetection", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "HarrisConnerDetection", &thresh, max_thresh, Harris_Conner);
	//��ʼ������
	Harris_Conner(0, 0);

	waitKey(0);
	return 0;
}
//ȫ�ֺ�������
void Harris_Conner(int, void*) {
	//����
	dstImage = Mat::zeros(grayImage.size(), CV_32FC1);
	//������ֵ
	int blocksize = 2;
	int ksize = 3;
	double k = 0.04;
	//���нǵ���
	cornerHarris(grayImage, dstImage, blocksize, ksize, k, BORDER_DEFAULT);
	//��һ��
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	//����һ�����ͼ���Ա任��8λ�޷�������
	convertScaleAbs(normImage, Scalednorm);
	//��¡
	resultImage = srcImage.clone();
	//ѭ���������أ����Ƴ������Ľǵ㣨Ҳ������ָ��ʵ�֣��ٶ���Կ�Щ��
	for (int i = 0; i < resultImage.rows; i++) {
		 //uchar* pixel_i = Scalednorm.ptr(i);
		for (int j = 0; j < resultImage.cols; j++) { 
			//int Pixel = (int)*pixel_i;
			//if(Pixel > thresh){
				if ((int)normImage.at<float>(i, j)  > thresh) {
					circle(resultImage, Point(j, i), 4, Scalar(0, 0, 255), 2, 8, 0);
					circle(Scalednorm, Point(j, i), 5, Scalar(1, 10, 255), 2, 8, 0);
			}
				//pixel_i++;
		}
	}
	//��ʾ�ǵ���Ľ��
	imshow("HarrisConnerDetection", resultImage);
	imshow("Detection", Scalednorm);
}
