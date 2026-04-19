#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct calculoSize{
    int maximo, minimo, promedio;
};

map<string,string> readFastaFile(string archivo){
    fstream fastaFile(archivo); 
    map<string,string> almacen;
    bool id_get = false;
    if(!fastaFile.is_open()){
        return almacen;
    }
    string line,ID;
    while(getline(fastaFile,line).good()){
        id_get = false;
        if(line[0] == '>'){
            ID = "";
            for(int i = 1; i < line.size(); i++){
                if(line[i] == ' ' ){
                    id_get = true;
                    break;
                }
                ID += line[i];
            }
        }
        if(!id_get) almacen[ID] += line;
    }
    return almacen;
}

calculoSize calculate(map<string,string> almacen){
    int minimo = INT_MAX, 
    maximo = INT_MIN,
    promedio = 0, 
    lenMapa = almacen.size(), 
    lenCadena;

    for(auto& i : almacen){
        lenCadena = i.second.size();
        if(lenCadena < minimo){
            minimo = lenCadena;
        }
        if(lenCadena > maximo){
            maximo = lenCadena;
        }
        promedio += lenCadena;
    }
    calculoSize ans;
    ans.maximo = maximo;
    ans.minimo = minimo;
    ans.promedio = promedio / lenMapa;
    return ans;
}

map<string,double> gcProportion(map<string,string> almacen){
    map<string,double> ans;
    for(auto&i : almacen){
        map<char, int> conteo; 
        for(auto&j : i.second){
            conteo[j] ++;
        }
        ans[i.first] = static_cast<float>(
            (conteo['G'] + conteo['C']) * 100.00 
            /
            (conteo['A'] + conteo['T'] + conteo['G'] + conteo['C'])
        );
    }
    return ans;
}


int main(){
    map<string,string> almacen = readFastaFile("test_bio.fasta");
    calculoSize q4 = calculate(almacen);
    cout << "Cadena maxima: " <<  q4.maximo<< "\n";
    cout << "Cadena minima: " << q4.minimo << "\n";
    cout << "Promedio: " << q4.promedio << "\n";
    map<string,double> q5 = gcProportion(almacen);
    for(auto& i : q5){
        cout << "ID: " << i.first << " gcProportion: " << i.second << "\n";
    }
}

