//Given a set of co-ordinates, this program finds the minimum total length of line segments required to connect the points in such a way that any point is reachable
//from any other point i.e. finds a MST(Minimum Spanning Tree)

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
double netDist = 0;
double label = 1;
double numComponents;

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
    while(numComponents>1){
        double distance = get<0>(edges[i]);
        double a = get<1>(edges[i]);
        double b = get<2>(edges[i]);
        if(search(a)!=search(b)){
            netDist += distance;
            Union(a,b);
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
    sort(edges.begin(),edges.end());
    constructMST();
    cout<<setprecision(11)<<netDist<<"\n";
    return 0;
}
