#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "data.hpp"

#include "ransac.hpp"





int main(){
    cout<<"gfsf"<<endl;
    
    float xfloat[] = {16.0,2.0,77.0,29.0};
    vector<float> x (xfloat,xfloat+4);
    
    float yfloat[] = {16.0,2.0,77.0,29.0};
    vector<float> y (yfloat,yfloat+4);
    
    Data<pair<float, float> >* d = new LinearRansac(x,y);
    
    vector<float> model = Ransac(d,20 , 2);
    
    
    
    /*
    Mat I1;
    Mat I2;
    Mat Match;
    
    I1 = imread("../IMG_0045.JPG");
    I2 = imread("../IMG_0046.JPG");

    cout<<I1.rows<<endl;
    imshow("1", I1);
    imshow("2",I2);
    waitKey();
    
    vector<KeyPoint> kpts1, kpts2;
    Mat desc1, desc2;
    
    Ptr<AKAZE> akaze = AKAZE::create();
    akaze->detectAndCompute(I1, noArray(), kpts1, desc1);
    akaze->detectAndCompute(I2, noArray(), kpts2, desc2);
    
    BFMatcher matcher(NORM_HAMMING);
    vector< vector<DMatch> > nn_matches;
    matcher.knnMatch(desc1, desc2, nn_matches, 2);
    
    drawMatches(I1, kpts1, I2, kpts2, nn_matches, Match);
    
    imshow("Match", Match);
    waitKey();
    
    vector<Point2f> scene1;
    vector<Point2f> scene2;
    
    for( int i = 0; i < nn_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        for ( int j = 0; j < nn_matches[i].size(); j++)
        {
            scene1.push_back( kpts1[ nn_matches[i][j].queryIdx ].pt );
            scene2.push_back( kpts2[ nn_matches[i][j].trainIdx ].pt );
        }
    }
    Mat mask(nn_matches[1].size(),1,CV_8U);
    Mat MaskMatch;
    
    Mat H = findHomography( scene1, scene2, CV_RANSAC, 3.0, mask);
    drawMatches(I1, kpts1, I2, kpts2, nn_matches, MaskMatch);
    
    
    imshow("Match", MaskMatch);
    waitKey();
    
    return 0;
    */
}