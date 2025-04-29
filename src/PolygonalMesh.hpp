#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
	// VERTICI
    unsigned int NumCell0Ds = 0; // numero di celle 0D
    std::vector<unsigned int> Cell0DsId = {}; // id celle 0D, dimensione: 1 x NumberCell0D 
    Eigen::MatrixXd Cell0DsCoordinates = {}; // coordinate celle 0D, dimensione: 2 x NumberCell0D (x,y)
    std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; // marker celle 0D
    
    // LATI/SPIGOLI
    unsigned int NumCell1Ds = 0; // numero di celle 1D
    std::vector<unsigned int> Cell1DsId = {}; /// id celle 1D, dimensione: 1 x NumberCell1D
    Eigen::MatrixXi Cell1DsExtrema = {}; // indici dei vertici celle 1D, dimensione: 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; // marker celle 1D
    
    // POLIGONI
    unsigned int NumCell2Ds = 0; // numero celle 2D
    std::vector<unsigned int> Cell2DsId = {}; // id celle 2D, dimensione: 1 x NumberCell2D
    std::vector<std::vector<unsigned int>> Cell2DsVertices = {};
    std::vector<std::vector<unsigned int>> Cell2DsEdges = {};
    std::map<unsigned int, list<unsigned int>> MarkerCell2Ds = {};
};

}

