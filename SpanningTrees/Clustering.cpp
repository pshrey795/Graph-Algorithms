//Given some coordinates and an integer k, this program finds the largest value of d such that when the given points are clustred into k non-empty subsets, the 
//distance between any two points in different clusters is at least d.

#include<bits/stdc++.h>
using namespace std;

struct Point{
    double x;
    double y;

    Point(double a,double b){
        x = a;
        y = b;
    }
};

double dist(Point p1,Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

vector<tuple<Point,double,double>> Points;
vector<tuple<double,double,double>> edges;
double label = 1;
double minDist;
double numComponents;
double maxComponents;

double search(double x){
    double root = x;
    while(get<1>(Points[root])>=0){
        root = get<1>(Points[root]);
    }
    return root;
}

void Union(double x,double y){
    double root1 = search(x);
    double root2 = search(y);
    if(get<2>(Points[root1])>=get<2>(Points[root2])){
        get<2>(Points[root1]) += get<2>(Points[root2]);
        get<1>(Points[root2]) = root1;
    }else{
        get<2>(Points[root2]) += get<2>(Points[root1]);
        get<1>(Points[root1]) = root2;
    }
    numComponents--;
}

void constructMST(){
    double i=0;
    while(true){
        double distance = get<0>(edges[i]);
        double a = get<1>(edges[i]);
        double b = get<2>(edges[i]);
        if(search(a)!=search(b)){
            if(numComponents>maxComponents){
                Union(a,b);
            }else{
                minDist = get<0>(edges[i]);
                return;
            }
        }
        i++;    
    }
}

int main(){
    double n;cin>>n;
    numComponents = n;
    for(double i=0;i<n;i++){
        double x,y;cin>>x>>y;
        Point p1 = Point(x,y);
        Points.push_back(make_tuple(p1,(-1)*label,1));
        for(double j=0;j<i;j++){
            Point p2 = get<0>(Points[j]);
            edges.push_back(make_tuple(dist(p1,p2),i,j));
        }
        label++;
    }
    cin>>maxComponents;
    sort(edges.begin(),edges.end());
    constructMST();
    cout<<setprecision(11)<<minDist<<"\n";
    return 0;
}
