#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat img, new_img, edges;
int blure = 2;
int threshold1 = 0;
int threshold2 = 10077;

static void blure_on_trackbar(int, void*){
    if(blure == 0) blure = 1;
    GaussianBlur(img, new_img, Size(0, 0), blure);
    cvtColor(new_img, new_img, COLOR_BGR2GRAY);
    imshow("Processed", new_img);
}

static void edges_on_trackbar(int, void*){
    Canny(new_img, edges, threshold1 / 100, threshold2 / 100);
    imshow("Edges", edges);
}

int main()
{
    img = imread("../Visual_Pattern_Recognition-Practice_6-8_semester/image.jpg", IMREAD_COLOR);
    if (img.empty()){
        cout << "Изображение не загружено" << endl;
        return -1;
    }
    copyMakeBorder(img, img, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(0, 0, 0));
    namedWindow("Original", WINDOW_NORMAL);
    imshow("Original", img);

    namedWindow("Processed", WINDOW_NORMAL);
    blure_on_trackbar(blure, 0);
    createTrackbar("blure", "Processed", &blure, 20, blure_on_trackbar);

    namedWindow("Edges", WINDOW_NORMAL);
    edges_on_trackbar(threshold1, 0);
    createTrackbar("threshold1", "Edges", &threshold1, 100000, edges_on_trackbar);
    createTrackbar("threshold2", "Edges", &threshold2, 100000, edges_on_trackbar);
    waitKey(0);
    return 0;
}
