#include "mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <QDebug>
#include <QFileInfo>

using namespace cv;

MainWindow::MainWindow(QString dir_path, QWidget *parent)
    : QMainWindow(parent)
{
    Mat im_src, im_bin, im_blur, im_dst, im_color_dst, im_dilate;

    // read an image
    QString img_path = dir_path + "/../images/1.jpg";
    qDebug() << img_path;
    im_src = imread(img_path.toStdString(), 1);
    if (!im_src.empty()) {

        //1)  Step get rid of color
        cvtColor(im_src, im_src,  COLOR_RGB2GRAY);

        //2) Inverse
        bitwise_not(im_src, im_src);


//        //2) Get rid of small details
//        blur( im_src, im_blur, Size(3,3) );
//        namedWindow( "Blur", 1 );
//        imshow( "blur", im_blur );

        //3) Binarization
        threshold(im_src, im_bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
        namedWindow( "Binarization", 1 );
        imshow( "Binarization", im_bin );

        //4) Dilate
        int dilation_size = 3;
        Mat element = getStructuringElement( MORPH_ELLIPSE,
                               Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                               Point( dilation_size, dilation_size ) );
        dilate(im_bin, im_dilate, element);
        namedWindow( "Dilation", 1 );
        imshow( "Dilation", im_dilate );


//        std::vector<Vec3f> circles;
//        HoughCircles(im_bin, circles, HOUGH_GRADIENT, 1,
//                     im_bin.rows/16,  // change this value to detect circles with different distances to each other
//                     100, 30, 1, 30 // change the last two parameters
//                // (min_radius & max_radius) to detect larger circles
//        );
//        for( size_t i = 0; i < circles.size(); i++ )
//        {
//            Vec3i c = circles[i];
//            Point center = Point(c[0], c[1]);
//            // circle center
//            circle( im_bin, center, 1, Scalar(0,100,100), 3, LINE_AA);
//            // circle outline
//            int radius = c[2];
//            circle( im_bin, center, radius, Scalar(255,0,255), 3, LINE_AA);
//        }
//        imshow("detected circles", im_bin);


        Canny( im_src, im_dst, 50, 200, 3 );
        cvtColor( im_dst, im_color_dst, COLOR_GRAY2BGR );

//        std::vector<std::vector<Point> > contours;
////        std::vector<Vec4i> hierarchy;
//        findContours(im_src, contours, RETR_LIST, CHAIN_APPROX_TC89_L1);
//        for( size_t i = 0; i< contours.size(); i++ )
//        {
//            drawContours( im_src, contours, (int)i, Scalar(128), 2, LINE_8, 0 );
//        }
//        imshow( "Contours", im_src );





//        std::vector<Vec4i> lines;
//        HoughLinesP( dst, lines, 1, CV_PI/180, 40, 5, 10 );
//        for( size_t i = 0; i < lines.size(); i++ )
//        {
//            line( color_dst, Point(lines[i][0], lines[i][1]),
//                  Point( lines[i][2], lines[i][3]), Scalar(0,0,255), 2, 0 );
//        }

        namedWindow( "Source", 1 );
        imshow( "Source", im_src );
        namedWindow( "Detected Lines", 1 );
        imshow( "Detected Lines", im_color_dst );








//        // create image window named "My Image"
//        namedWindow("My Image");
//        // show the image on window
//        imshow("My Image", src);















    } else {
        qDebug() << "Empty image";
    }


}

MainWindow::~MainWindow()
{
}

