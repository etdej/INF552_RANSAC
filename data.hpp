//
//  data.cpp
//  
//
//  Created by Etienne Dejoie on 25/11/2015.
//
//

#ifndef DATA_H
#define DATA_H

using namespace std;
using namespace cv;

template <typename T> class Data{
    public:
        vector<T> vc;
    
        int minEstNb;
        int nbParameters;
    
    
        virtual vector<float> estimModel (vector<T> estimData); //renvoie un vecteur de taille nbParameter
        virtual float calculateError1(T sousData, vector<float> model); //renvoie l'erreur d'un modèle avec une donnée
        virtual float calculateError2(vector<T> sousData, vector<float> model);// renvoie l'erreur avec une liste de donnée
    
};

class LinearRansac : public Data<pair<float, float> >{
    
    public:
    vector<pair<float, float> > vc;
    
    int minEstNb = 2;
    int nbParameters = 2;
    
    LinearRansac (vector<float> source, vector<float> target){
        
        if (source.size() != target.size()) {
            cout << "la taille de target est différente de celle de source, problème" << endl;
        }
        else {
            for (int i = 0 ; i < source.size(); i++) {
                vc.push_back(make_pair(source[i], target[i]));
            }
            
        }
    }
    
    
    virtual vector<float> estimModel(vector<pair<float, float> > ll){
        
        int n = ll.size();
        
        // calculate the averages of arrays x and y
        float xa = 0, ya = 0;
        for (int i = 0; i < n; i++) {
            xa += ll[i].first;
            ya += ll[i].second;
        }
        xa /= n;
        ya /= n;
        
        // calculate auxiliary sums
        float xx = 0, yy = 0, xy = 0;
        for (int i = 0; i < n; i++) {
            float tmpx = ll[i].first- xa, tmpy = ll[i].second - ya;
            xx += tmpx * tmpx;
            yy += tmpy * tmpy;
            xy += tmpx * tmpy;
        }
        
        // calculate regression line parameters
        
        
        float m_b = xy / xx;
        float m_a = ya - m_b * xa;
        
        vector<float> params;
        params.push_back(m_b);
        params.push_back(m_a);
        
        return params;//return slope, intercept
    }
    
    virtual float calculateError1(pair<float, float> d, vector<float> model){
        return pow(d.second - model[0]*d.first - model[1], 2);
        
    }
    
    virtual float calculateError2(vector<pair<float,float> > dat, vector<float> model){
        
        float S = 0;
        int n = dat.size();
        
        for(pair<float,float> p : dat)
        S += calculateError1(p, model);
        
        return S/n;
        
    }
    
};


#endif