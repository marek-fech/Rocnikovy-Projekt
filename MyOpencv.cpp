#include"Include.h"

using namespace cv;
using namespace std;

//positon of mouse
int globalX = 0;
int globalY = 0;

//1 = Zoom In   2 = Zoom Out    3 = Reset Zoom  4 = Move
int globalB = -1;

int globalIm1sw = 0;
int globalIm1sh = 0;
int globalIm1w = 0;
int globalIm1h = 0;

int globalIm2sw = 0;
int globalIm2sh = 0;
int globalIm2w = 0;
int globalIm2h = 0;

int zoomOfIm1 = 1;
int zoomOfIm2 = 1;

Rect ROI1;
Rect ROI2;

//global Image
Mat gImg1;
Mat gImg2;

void addPoints(int width, int height, Mat DispImage) {
    Scalar circleColor(0, 0, 0);
    Scalar squareColor(255, 255, 255);

    int radius = 15;
    int edge = 45;

    //circles points
    Point center1(edge / 2, edge / 2);
    Point center2(edge / 2, height - (edge / 2));
    Point center3(width - (edge / 2), edge / 2);
    Point center4(width - (edge / 2), height - (edge / 2));

    //squares points
    Point center11(0, 0);
    Point center12(0, height - edge);
    Point center13(width - edge, 0);
    Point center14(width - edge, height - edge);

    Point center21(edge, edge);
    Point center22(edge, height);
    Point center23(width, edge);
    Point center24(width, height);

    //drawing
    rectangle(DispImage, center11, center21, squareColor, FILLED);
    rectangle(DispImage, center12, center22, squareColor, FILLED);
    rectangle(DispImage, center13, center23, squareColor, FILLED);
    rectangle(DispImage, center14, center24, squareColor, FILLED);

    circle(DispImage, center1, radius, circleColor, FILLED);
    circle(DispImage, center2, radius, circleColor, FILLED);
    circle(DispImage, center3, radius, circleColor, cv::FILLED);
    circle(DispImage, center4, radius, circleColor, FILLED);

}

Mat rotateImage(Mat img) {
    double angle = 90;
    Mat finPic;

    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((img.cols - 1) / 2.0, (img.rows - 1) / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), img.size(), angle).boundingRect2f();

    // adjust transformation matrix
    rot.at<double>(0, 2) += bbox.width / 2.0 - img.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - img.rows / 2.0;

    //cv::Mat dst;
    cv::warpAffine(img, finPic, rot, bbox.size());

    return finPic;
}

int getMax(int x, int y) {
    return (x > y) ? x : y;
}

void addImage(int size, int width, bool image, Mat img, Mat DispImage, bool original) {
    Mat finPic;
    //start points of Width and Height
    double pointW;
    int pointH = 10;
    int pixelOffset = 10;

    if (img.cols > img.rows) {
        finPic = rotateImage(img).clone();
    }
    else {
        finPic = img.clone();
    }

    float scale = (float)((float)getMax(finPic.cols, finPic.rows) / size);
    if (image) 
        pointW = (width / 2) - pixelOffset - finPic.cols / scale;        //position of first image
    
    else
        pointW = (width / 2) + pixelOffset;                              //position of second image
    
    Rect ROI(pointW, pointH, (int)(finPic.cols / scale), (int)(finPic.rows / scale));
    Mat temp;
    resize(finPic, temp, Size(ROI.width, ROI.height));
    if (original) {
        if (image) {
            globalIm1h = temp.rows;
            globalIm1w = temp.cols;
            globalIm1sh = pointH;
            globalIm1sw = (int)pointW;
            ROI1 = ROI;
            gImg1 = temp;
        }
        else {
            globalIm2h = temp.rows;
            globalIm2w = temp.cols;
            globalIm2sh = pointH;
            globalIm2sw = (int)pointW;
            ROI2 = ROI;
            gImg2 = temp;
        }
    }

    temp.copyTo(DispImage(ROI));
}

void locator(int event, int x, int y, int flags, void* userdata) { //function to track mouse movement and click//
    if (event == EVENT_LBUTTONDOWN) { //when left button clicked//
        cout << "Left click has been made, Position:(" << x << "," << y << ")" << endl;
        globalB = 4;
        globalX = x;
        globalY = y;
    }
    else if (event == EVENT_RBUTTONDOWN) { //when right button clicked//
        cout << "Rightclick has been made, Position:(" << x << "," << y << ")" << endl;        
        globalB = 3;
        globalX = x;
        globalY = y;
    }
    else if (event == EVENT_MOUSEWHEEL) {  //when scrolling//
        if (getMouseWheelDelta(flags) > 0) {
            globalB = 1;
            globalX = x;
            globalY = y;
        }
        else {
            globalB = 2;
            globalX = x;
            globalY = y;
        }
    }
}

void zoomIn(int size, int width, double scale, Mat DispImage, int imStartWidth, int imStartHeight, int imWidth, int imHeight, bool first) {
    double startWidth = 0;
    double startHeight = 0;

    //Of Interest -> new weight and height
    double widthOI = imWidth / scale;
    double heightOI = imHeight / scale;

    startWidth = globalX - (widthOI / 2);
    startHeight = globalY - (heightOI / 2);

    //check if we are withing acceptable width
    if (startWidth < imStartWidth) {
        startWidth = imStartWidth;
    }
    if ((startWidth + widthOI) > (imStartWidth + imWidth)) {
        startWidth = (imStartWidth + imWidth) - widthOI;
    }

    //check if we are withing acceptable height
    if (startHeight < imStartHeight) {
        startHeight = imStartHeight;
    }
    if ((startHeight + heightOI) > (imStartHeight + imHeight)) {
        startHeight = (imStartHeight + imHeight) - heightOI;
    }

    Rect ROI((int)startWidth, (int)startHeight, (int)widthOI, (int)heightOI);
    Mat finPic = DispImage(ROI);

    addImage(size, width, first, finPic, DispImage, false);

    globalB = -1;
}

void ShowManyImages(string title, Mat img1, Mat img2) {
    if (img1.empty() || img2.empty()) {
        cout << "Invalid number of arguments!";
        waitKey(0);
    }

    //int width = 1500;//(int)GetSystemMetrics(SM_CXSCREEN) - 20;
    //int height = 800;//(int)GetSystemMetrics(SM_CYSCREEN) - 80;
    
    int width = -20 + (int)GetSystemMetrics(SM_CXSCREEN);
    int height = -80 + (int)GetSystemMetrics(SM_CYSCREEN);
    int size = height - 20;
    double scale = 2;

    // Create a new window, and show the Single Big Image
    namedWindow(title, 1); //change 1 to WINDOW_NORMAL for fullscreen but destroy resoluton
    setWindowProperty(title, WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN); //for full screen, only works with WINDOW_NORMAL
    moveWindow(title, 0, 0);

    // Create a new 3 channel image
    Mat DispImage(Size(width, height), CV_8UC3, Scalar(35, 35, 35));


    //addPoints(width, height, DispImage);
    addImage(size, width, true, img1, DispImage, true);
    
    addImage(size, width, false, img2, DispImage, true);
    
    imshow(title, DispImage);

   while (!GetAsyncKeyState(VK_ESCAPE)) {
       setMouseCallback(title, locator);

       if (globalB == 3) {
           if (globalX >= globalIm1sw && globalX <= (globalIm1sw + globalIm1w) &&
               globalY >= globalIm1sh && globalY <= (globalIm1sh + globalIm1h)) {

               addImage(size, width, true, img1, DispImage, false);
               globalB = -1;
           }
           else if (globalX >= globalIm2sw && globalX <= (globalIm2sw + globalIm2w) &&
                    globalY >= globalIm2sh && globalY <= (globalIm2sh + globalIm2h)) {
               
               addImage(size, width, false, img2, DispImage, false);
               globalB = -1;
           }
       }
       else if (globalB == 1){
           if (globalX >= globalIm1sw && globalX <= (globalIm1sw + globalIm1w) &&
               globalY >= globalIm1sh && globalY <= (globalIm1sh + globalIm1h)) {

               zoomIn(size, width, scale, DispImage, globalIm1sw, globalIm1sh, globalIm1w, globalIm1h, true);
               zoomOfIm1++;
           }
           else if (globalX >= globalIm2sw && globalX <= (globalIm2sw + globalIm2w) &&
                    globalY >= globalIm2sh && globalY <= (globalIm2sh + globalIm2h)) {
               
               zoomIn(size, width, scale, DispImage, globalIm2sw, globalIm2sh, globalIm2w, globalIm2h, false);
               zoomOfIm2++;
           }
       }
       //TODO
       else if (globalB = 2) {

       }
       //TODO
       else if (globalB = 4) {
           
       }

       imshow(title, DispImage);
       waitKey(1);

   }
   destroyWindow(title);


    

    
}

