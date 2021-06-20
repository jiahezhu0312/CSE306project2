#include <cstring>
#include "functions.cpp"
using namespace std;


int main(){

    Polygon subjectPolygon = Polygon({Vector(0.1,0.8,0),Vector(0.1,0.1,0),Vector(0.8,0.1,0),Vector(0.8,0.8,0)});
    Polygon clipPolygon = Polygon({Vector(0.4,0.2,0), Vector(0.1,0.5, 0), Vector(0.1, 0.6, 0)});
    Polygon  Pol = PolygonAlgorithm(subjectPolygon, clipPolygon);
    vector<Polygon> i0;
    i0.push_back(subjectPolygon);
    i0.push_back(clipPolygon);
    vector<Polygon> i1;
    i1.push_back(Pol);
    save_svg(i0,"TwoPolygons.svg");
    save_svg(i1,"ResultPolygon.svg");





    //voronoi and power diagram
    Polygon Box = Polygon({Vector(0,0,0), Vector(0,1,0), Vector(1,1,0), Vector(1,0,0)});
    Polygon V = Polygon({Vector(0,0.3,0),Vector(0.9,0.6,0),Vector(0.5,0.5,0),Vector(0.3,0.7,0)});
    vector<double> w = {0.03, 0.03, 0.03, 0.03};
    vector<Polygon> P;
    vector<Polygon> P1;
    for(int i = 0;i < int(V.vertices.size()); i++){
        Polygon v = VPLE(Box, V, i);
        Polygon v1 = DiagP(Box, V, i, w);
        P.push_back(v);
        P1.push_back(v1);
    }
    save_svg(P, V, "Veronoi.svg");
    save_svg(P1, V, "PowerDiagram.svg");









    //random voronoi and power diagram
    Polygon randomPolygon250 = GeneratePolygon(250);
    Polygon randomPolygon500 = GeneratePolygon(500);
    Polygon randomPolygon1000 = GeneratePolygon(1000);

    vector<double> randomW250 = GenerateWeights(250);
    vector<double> randomW500 = GenerateWeights(500);
    vector<double> randomW1000 = GenerateWeights(1000);

    vector<Polygon> randoms;
    vector<Polygon> randomp;
    vector<vector<double>> randomws;
    
    randoms.push_back(randomPolygon250);
    randoms.push_back(randomPolygon500);
    randoms.push_back(randomPolygon1000);
    randomp.push_back(randomPolygon250);
    randomp.push_back(randomPolygon500);
    randomp.push_back(randomPolygon1000);
    randomws.push_back(randomW250);
    randomws.push_back(randomW500);
    randomws.push_back(randomW1000);

    for (int i = 0; i < randoms.size(); i++){
        vector<Polygon> Pr;
        
        for(int j = 0;j < int(randoms[i].vertices.size()); j++){
            Polygon v = VPLE(Box, randoms[i], j);
            Pr.push_back(v);
        }
        save_svg(Pr, randoms[i], "random" + to_string(i) + ".svg");
    }

    for (int i = 0; i < randomp.size(); i++){
        vector<Polygon> Pp;
        for(int j = 0;j < int(randomp[i].vertices.size()); j++){
            Polygon v = DiagP(
                Box, randomp[i],j, randomws[i]);
            Pp.push_back(v);
        }
        save_svg(Pp, randomp[i], "randomw" + to_string(i) + ".svg");
    }

    return 0;
}