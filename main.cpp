#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               cell0Ds_properties);
    }

    {
        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.MarkerCell1Ds)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {},
                                 cell1Ds_properties);
     }
     {
        vector<Gedim::UCDProperty<double>> cell2Ds_properties(1);
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();
        
        cell2Ds_properties[0].Label = "Marker";
        cell2Ds_properties[0].UnitLabel = "-";
        cell2Ds_properties[0].NumComponents = 1;

        vector<double> cell2Ds_marker(mesh.NumCell2Ds, 0.0);
        for (const auto& m : mesh.MarkerCell2Ds)
            for (const unsigned int id : m.second)
                cell2Ds_marker.at(id) = m.first;

        cell2Ds_properties[0].Data = cell2Ds_marker.data();

        Gedim::UCDUtilities utilities;
        utilities.ExportPolygons("./Cell2Ds.inp",
                                  mesh.Cell0DsCoordinates,
                                  mesh.Cell2DsVertices, 
                                  cell0Ds_properties,      
                                  cell2Ds_properties);
    }
	
	// implementazione dei test richiesti
	// verifico che la lunghezza dei segmenti sia diversa da zero
	for (int i = 0; i < mesh.NumCell1Ds; ++i){
		const unsigned int origin = mesh.Cell1DsExtrema(i, 0);
        const unsigned int end = mesh.Cell1DsExtrema(i, 1);
        Eigen::Vector2d a = mesh.Cell0DsCoordinates.row(origin);
        Eigen::Vector2d b = mesh.Cell0DsCoordinates.row(end);

        double length = (b - a).norm();
        if (length == 0.0) {
			cerr << "Errore: la lunghezza del segmento " << i << " (" << origin << " - " << end << ") è zero." << endl;
        }
	}
	
	// Verifico che l'area dei triangoli sia positiva
	for (int i = 0; i < mesh.NumCell2Ds; ++i) {
		const vector<unsigned int>& verts = mesh.Cell2DsVertices[i];
        if (verts.size() != 3) {
			cerr << "Errore: l'area del triangolo " << i << " con vertici " 
     << verts[0] << ", " << verts[1] << ", " << verts[2] << " è zero." << endl;

        continue;
        }

        Eigen::Vector2d a = mesh.Cell0DsCoordinates.row(verts[0]);
        Eigen::Vector2d b = mesh.Cell0DsCoordinates.row(verts[1]);
        Eigen::Vector2d c = mesh.Cell0DsCoordinates.row(verts[2]);

        double area = 0.5 * abs((b - a).x() * (c - a).y() - (b - a).y() * (c - a).x());
        if (area == 0.0) {
			cerr << "Errore: l'area del triangolo " << i << " è zero." << endl;
        }
    }

    return 0;
}
