#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "pbPlots.hpp"
#include "supportLib.hpp"

class Pulsar{
public:
    explicit Pulsar(const std::vector<std::pair<std::string, std::string>>& v):length_(v.size()){
        for (int i = 0; i < length_; ++i){
            if (v[i].first == "PSRB"){
                Name.first = "PSRB";
                Name.second = v[i].second;
            }
            else if (v[i].first == "PSRJ"){
                JName.first = "PSRJ";
                JName.second = v[i].second;
            }
            else if (v[i].first == "RaJ"){
                RaJ.first = "RaJ";
                RaJ.second = v[i].second;
            }
        }
    }
    void GetName() const{
        std::cout << Name.first << " " << Name.second << std::endl;
    };
    void GetJName() const{
        std::cout << JName.first << " " << JName.second << std::endl;
    }
    void GetRaJ() const{
        std::cout << RaJ.first << " " << RaJ.second << std::endl;
    }
private:
    unsigned int length_;
    std::pair<std::string, std::string> Name, JName, RaJ;
};
int main() {
    std::string line;
    std::ifstream myfile ("C:/Users/dmitr/Desktop/psrcat/psrcat.txt");
    std::ofstream output ("C:/Users/dmitr/Desktop/psrcat/new_psrcat.txt");
    if (myfile.is_open() and output.is_open()) {
        while (getline (myfile, line)) {
            std::stringstream input (line);
            std::vector<std::pair<std::string, std::string>> v;
            if (!input){
                continue;
            }
            std::string first, second;
            input >> first;
            if (first[0] != '#' and first[0] != '@') {
                input >> second;
                std::pair<std::string, std::string> p(first, second);
                output << first << ' ' << second << std::endl;
                v.push_back(p);
            }
            if (first[0] == '@'){
                Pulsar p(v);
                output << '@' << std::endl;
                v.clear();
            }
            // new pulsar,  continue
        }
        myfile.close();
    }
    else {
        std::cout << "Unable to open file";
    }
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    std::vector<double> xs{-2, -1, 0, 1, 2};
    std::vector<double> ys{2, -1, -2, -1, 2};

    DrawScatterPlot(imageReference, 600, 400, &xs, &ys);

    std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
    WriteToFile(pngdata, "example1.png");
    DeleteImage(imageReference->image);
    return 0;
}