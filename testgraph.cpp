#include "/home/fernando/Snap-5.0/snap-core/Snap.h"
#include "stdafx.h"
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#include <stdlib.h>     
#include <ctime>


using namespace std;


void exportarGraphML(PNGraph Graph);
void exportarGEXF(PNGraph Graph);
void exportarGDF(PNGraph Graph);
void exportarGraphSON(PNGraph Graph);


int main() {

    typedef TPt<TNGraph> PNGraph;
    PNGraph G = TNGraph::New();
    
    for(int i = 0;i<= 10878;i++){
        G->AddNode(i);
    }
    ifstream archivo_entrada;
    char linea[128];
    
    archivo_entrada.open("p2p-Gnutella04.txt");
    
    if(archivo_entrada.fail()){
        cout<<"Error al abrir el archivo \n";
        return 0;
    }
    
    archivo_entrada.getline(linea,sizeof(linea));
    archivo_entrada.getline(linea,sizeof(linea));
    archivo_entrada.getline(linea,sizeof(linea));
    archivo_entrada.getline(linea,sizeof(linea));
    
    string origen, destino;
    int org, dest;
    while(!archivo_entrada.eof()){
        archivo_entrada.getline(linea,sizeof(linea));
        
        string str(linea);
        
        istringstream iss(str);
        
        if(iss){
            iss >> origen;
            iss >> destino;
            dest = stoi(destino);
            org = stoi(origen);
            
            G->AddEdge(org,dest);
        }
    }
    
    archivo_entrada.close();
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    t1 = high_resolution_clock::now();
    exportarGraphML(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Tiempo de ejecucion GraphML: " << time_span.count()  << "seconds" << endl;

    t1 = high_resolution_clock::now();
    exportarGEXF(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Tiempo de ejecucion GEXF: " << time_span.count()  << "seconds" << endl;

    t1 = high_resolution_clock::now();
    exportarGDF(G);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Tiempo de ejecucion GDF: " << time_span.count()  << "seconds" << endl;
    
   
    t1 = high_resolution_clock::now();
    exportarGraphSON(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Tiempo de ejecucion GraphSON: " << time_span.count()  << "seconds" << endl;

    return 0;
}





void exportarGraphML(PNGraph Graph){
    ofstream archivo_salida;
    archivo_salida.open("grafoGnutella.graphml");
    
    if (archivo_salida.is_open()){
        archivo_salida << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        archivo_salida << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        archivo_salida << "<graph id=\"G\" edgedefault=\"directed\">\n";
        
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
            archivo_salida << "<node id=\"n" << NI.GetId() << "\"/>\n";
        }
        int i = 0;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++,i++){
            archivo_salida << "<edge id=\"e" << i << "\" source=\"n" << EI.GetSrcNId() << "\" target=\"n" << EI.GetDstNId() << "\" />\n";
        }
        
        archivo_salida << "</graph>\n";
        archivo_salida << "</graphml>\n";
        archivo_salida.close();
    }
}

void exportarGEXF(PNGraph Graph){
    ofstream archivo_salida;
    archivo_salida.open("grafoGnutella.gexf");
    
    if (archivo_salida.is_open()){
        archivo_salida << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        archivo_salida << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        archivo_salida << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
        archivo_salida << "<nodes>\n";
        
        
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
            archivo_salida << "<node id=\"" << NI.GetId() << "\" />\n";
        }
        
        archivo_salida << "</nodes>\n";
        archivo_salida << "<edges>\n";
        int i = 0;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++,i++){
            archivo_salida << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        }
        archivo_salida << "</edges>\n";
        archivo_salida << "</graph>\n";
        archivo_salida << "</gexf>\n";
        archivo_salida.close();
    }
}

void exportarGDF(PNGraph Graph){
    ofstream archivo_salida;
    archivo_salida.open("grafoGnutella.gdf");
    
    if (archivo_salida.is_open()){
        archivo_salida << "nodedef>name\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
            archivo_salida << NI.GetId() << ",\n";
        }
        
        archivo_salida << "edgedef>node1,node2\n";
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
            archivo_salida << EI.GetSrcNId() << "," << EI.GetDstNId() << "\n";
        }

        archivo_salida.close();
    }
}


void exportarGraphSON(PNGraph Graph){
    ofstream archivo_salida;
    archivo_salida.open("grafoGnutella.json");
    
    if (archivo_salida.is_open()){
        archivo_salida << "{ \"graph\": {\n";
        archivo_salida << "\"nodes\": [\n";
        
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
            archivo_salida << "{\n \"_id\": \"" << NI.GetId() << "\" }";
            
            if (NI == Graph->EndNI()){
                archivo_salida << " ],\n";
            }else{
                archivo_salida << ",\n";
            }
        }
        
        archivo_salida << "\"edges\": [\n";
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
            archivo_salida << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            
            if (EI == Graph->EndEI()){
                archivo_salida << " ]\n";
            }else{
                archivo_salida << ",\n";
            }
        }
        archivo_salida << "} }";
        
    }
}



















