//
//  data.cpp
//  
//
//  Created by Etienne Dejoie on 25/11/2015.
//
//

#include <stdio.h>
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


using namespace std;
using namespace cv;

template <typename T>
class Data{
    vector<T> vc;
    int size;
    
    static int minEstNb;
    static int nbParameter;
    
    vector<float> estimModel (vector<T> estimData); //renvoie un vecteur de taille nbParameter
    float calculateError(T sousData, vector<float> model); //renvoie l'erreur d'un modèle avec une donnée
    float calculateError(vector<T> sousData, vector<float> model);// renvoie l'erreur avec une liste de donnée
    
    
};
