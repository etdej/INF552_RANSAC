//
//  ransac.hpp
//  projet
//
//  Created by Etienne Dejoie on 11/01/2016.
//
//

#ifndef ransac_h
#define ransac_h


using namespace std;
using namespace cv;

template <typename T>
vector<float> Ransac(Data<T>* data, int iterNb, int estimNb){
    int matchNbMin = 3;
    vector<float> bestModel = vector<float>();
    float bestError = INFINITY;
    float matchError = 0.3;
    
    for( int it = 0; it<iterNb; it ++){
        vector<T> estimPoints = vector<T>();
        vector<T> otherPoints = vector<T>(data->vc);
        
        //put estimNb points in estimPoints (chosen randomly in data)
        for( int i = 0; i<estimNb; i++){
            int a = rand();
            int rand =(a % data->vc.size());
            T randPoint = otherPoints[rand];
            otherPoints.erase(otherPoints.begin() + rand);
            estimPoints.push_back(randPoint);
        }
        
        cout<< estimPoints.size() <<" + "<< otherPoints.size() << " = "<<data->vc.size() << endl;
        
        //find model
        
        vector<float> tempModel = data->estimModel(estimPoints);
        
        int matchNb = 0;
        //itérateur sur otherPoints
        for (int i = 0; i<otherPoints.size(); i ++) {
            float localError = data->calculateError1(otherPoints[i], tempModel);
            if (localError < matchError) {
                matchNb ++;
                estimPoints.push_back(otherPoints[i]);
            }
            
        }
        if (matchNb > matchNbMin ){
            vector<float> model = data->estimModel(estimPoints);
            float error = data->calculateError2(estimPoints, model);
            // calculater error
            if ( error< bestError ){
                bestModel = model;
                bestError = error;
            }
        }
        
    }
    
    return bestModel;
}
#endif /* ransac_h */
