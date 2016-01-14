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


using namespace std;


int main(){
    
    cout<<"It goes"<<endl;
    
    float xfloat[] = {16.0,2.0,77.0,29.0,30.0,45.0,60.0,120.0,123.0};
    vector<float> x (xfloat,xfloat+4);
    
    float yfloat[] = {-16.0+1,-2.0+1,-77.0+1,-29.0+1,-31.0+1,-44.0+1,-60.0+1,-121.0+1,-124.0+1};
    vector<float> y (yfloat,yfloat+4);
    
    Data<pair<float, float> >* d = new LinearRansac(x,y);
    
    vector<float> model = Ransac(d,20 , 2);
    cout << "y=" << model[0] << "*x+" << model[1] << endl;
    
    
    
    
    Mat I1;
    Mat I2;
    Mat Match;
    
    I1 = imread("../image0006.jpg");
    I2 = imread("../image0007.jpg");

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
    
    vector<float> model2;
    
    HomographyRansac hr(scene1, scene2);
    model2 = Ransac(&hr, 20, 50);
    
    Mat M2=Mat(2,2,CV_32FC1);
    memcpy(M2.data,model2.data(),model.size()*sizeof(float));
    
    imshow("Match", MaskMatch);
    waitKey();
    
    return 0;
    
};