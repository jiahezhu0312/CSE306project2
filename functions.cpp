#include "svg.cpp"
#include <random>
using namespace std;
static std::default_random_engine engine(10); // random seed = 10
static std::uniform_real_distribution<double> uniform(0,1);

bool check(Vector a, Vector b, Vector c){
    return (dot(a - b, c) <= 0);
}

Polygon PolygonAlgorithm(Polygon subjectPolygon, Polygon clipPolygon){
    Polygon outPolygon;
    for(int clipEdge = 0; clipEdge < clipPolygon.vertices.size(); clipEdge++){
        outPolygon = Polygon();
        Vector clipVertexCur = clipPolygon.vertices[clipEdge];
        Vector clipVertexPre = clipPolygon.vertices[(clipEdge>0)?(clipEdge-1):(clipPolygon.vertices.size()-1)];
        int cnt = 0;
        (clipPolygon.vertices.size() - 1 > clipEdge)?(cnt = clipEdge + 1):(cnt = 0);
        Vector E = clipPolygon.vertices[cnt] - clipPolygon.vertices[clipEdge];
        Vector N(clipVertexCur[1] - clipVertexPre[1], clipVertexPre[0] - clipVertexCur[0], 0);
        (dot(E, N) > 0)?(N = N * -1):(N = N);

        for(int i = 0; i < subjectPolygon.vertices.size(); i++){
            Vector VertexCur = subjectPolygon.vertices[i];
            Vector VertexPre = subjectPolygon.vertices[(i>0)?(i-1):(subjectPolygon.vertices.size()-1)];
            double t = dot(clipVertexPre - VertexPre, N) / dot(VertexCur - VertexPre, N);
            Vector P = VertexPre + t * (VertexCur - VertexPre);
            if(check(VertexCur, clipVertexPre, N)) {
                if(!check(VertexPre, clipVertexPre, N)){
                    if(t >=0 and t <= 1){
                        outPolygon.vertices.push_back(P);
                    }
                }
                outPolygon.vertices.push_back(VertexCur);
            }
            else if(check(VertexPre, clipVertexPre, N)){
                if(t >=0 and t <= 1){
                    outPolygon.vertices.push_back(P);
                }
            }

        }
        subjectPolygon = outPolygon;
    }
    return subjectPolygon;
}


Polygon VPLE(Polygon subjectPolygon, Polygon clipPolygon, int index){
    Polygon outPolygon;
    Vector Pi = clipPolygon.vertices[index];
    for(int clipEdge = 0; clipEdge < clipPolygon.vertices.size(); clipEdge++ ){
        if(index == clipEdge){
            continue;
        }
        outPolygon = Polygon();
        Vector Pj = clipPolygon.vertices[clipEdge];
        Vector M = (Pj + Pi) / 2;
        Vector D = Pj - Pi;


    for(int i = 0; i < subjectPolygon.vertices.size(); i++){
            Vector VertexCur = subjectPolygon.vertices[i];
            Vector VertexPre = subjectPolygon.vertices[(i>0)?(i-1):(subjectPolygon.vertices.size()-1)];
            double t = dot(M - VertexPre, D) / dot(VertexCur - VertexPre,D);
            Vector P = VertexPre + t * (VertexCur - VertexPre);
            if(check(VertexCur, M, D)) {
                if(!check(VertexPre, M, D)){
                    if(t >=0 and t <= 1){
                        outPolygon.vertices.push_back(P);
                    }
                }
                outPolygon.vertices.push_back(VertexCur);
            }
            else if(check(VertexPre, M, D)){
                if(t >=0 and t <= 1){
                    outPolygon.vertices.push_back(P);
                }
            }

        }
        subjectPolygon = outPolygon;
    }
    return subjectPolygon;

}

Polygon DiagP(Polygon subjectPolygon, Polygon clipPolygon, int index, vector<double> w){
    Polygon outPolygon;
    Vector Pi = clipPolygon.vertices[index];
    double wi = w[index];
    double wj;
    for(int clipEdge = 0; clipEdge < clipPolygon.vertices.size(); clipEdge++ ){
        if(index == clipEdge){
                continue;
        }
        wj = w[clipEdge];
        outPolygon = Polygon();
        Vector Pj = clipPolygon.vertices[clipEdge];
        Vector D = Pj - Pi;
        Vector M = (Pj + Pi) / 2;
        Vector M_ = M + ((wi - wj) /( 2 *  (Pi - Pj).length_squared())) *  D;

        for(int i = 0; i < subjectPolygon.vertices.size(); i++){
            Vector VertexCur = subjectPolygon.vertices[i];
            Vector VertexPre = subjectPolygon.vertices[(i>0)?(i-1):(subjectPolygon.vertices.size()-1)];
            double t = dot(M_ - VertexPre,  (Pi - Pj)) / dot(VertexCur - VertexPre,  (Pi - Pj));
            Vector P = VertexPre + t * (VertexCur - VertexPre);
            if(check(VertexCur, M_, D)) {
                if(!check(VertexPre, M_, D)){
                    if(t >=0 and t <= 1){
                        outPolygon.vertices.push_back(P);
                    }
                }
                outPolygon.vertices.push_back(VertexCur);
            }
            else if(check(VertexPre, M_, D)){
                if(t >=0 and t <= 1){
                    outPolygon.vertices.push_back(P);
                }
            }

        }
        subjectPolygon = outPolygon;
    }
    return subjectPolygon;
}

Polygon GeneratePolygon(int s){
    Polygon pol;
    for (int i = 0; i < s;i++){
        double x = uniform(engine);
        double y = uniform(engine);
        pol.vertices.push_back(Vector(x, y, 0));
    }
    return pol;
}

vector<double> GenerateWeights(int s){
    vector<double> w;
    for (int i = 0; i < s;i++){
        w.push_back(uniform(engine));
    }
    return w;
}