#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "data.cpp"

using namespace std;
using namespace cv;


template <typename T>
void Ransac(Data<T> data, int maxIter, int estimNb){
    int matchNbMin = (3* data.size())/10;
    Mat bestModel;
    float bestError = INFINITY;
    
    for( int it = 0; it<maxIter; it ++){
        vector<T> estimPoints = vector<T>();
        vector<T> otherPoints = vector<T>(data);
        //TODO: put estimNb points in estimPoints (chosen randomly in data)
        for( int i = 0; i<estimNb; i++){
            int rand = Math.rand() % data.size();
            vector<D> randPoint = otherPoints[rand];
            otherPoints.erase(rand);
            estimPoints.push(randPoint);
        }
        
        cout<< estimPoints.size() <<" + "<< otherPoints.size() << " = "<<data.size() << endl;
        
        //TODO: Mat homo = findHomography(imput,output)
        
        int matchNb;
        //itérateur sur otherPoints
        D input = otherPoints[itOther][0];
        D output = otherPoints[itOther][1];
        if( distance(homo(input) - output)< d){
            matchNb ++;
            // add (input,output) to estimPoints
        }
        
        float error  = 0.;
        if (matchNb > matchNbMin ){
            //TODO : evaluate new Homo with estim points
            
        }
        // calculater error
        if ( error< minError ){
            bestModel = model;
            minError = error;
        }
    }
}

int main(){

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
}