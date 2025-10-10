#include <iostream>
#include <string>

struct SampleData {
    double Entries;
    double SumofLHEWeights;
    double SumofGENWeights;
    double XSec;
    double XsecDB;
    double XsecWeight;
};

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

std::unordered_map<std::string, SampleData> CalculateXsecWeights(std::string& fileName, bool isSIGNAL = false, bool use_LHE_weights=false, bool use_xsecDB = false) 
{
	std::unordered_map<std::string, SampleData> sampleMap;

	cout<<"Reading cross section weights from "<<fileName<<endl;
	std::ifstream mc_info_file(fileName);
	if (!mc_info_file.is_open()) {
		std::cerr << "Error: Could not open file." << std::endl;
	}

    std::string line;
    
    while (getline(mc_info_file, line)) {
        
        istringstream iss(line);

        string sample;
        double entries, sumLHE, sumGEN, xsec, xsecDB;

        // Read and parse the line
        if (getline(iss, sample, '\t')) { // Read the sample name (until tab)
			if(isSIGNAL){
				iss >> entries >> sumLHE >> sumGEN; // Read the rest of the fields
				xsec = 1.;
				xsecDB = 1.;
			}
			else{
				iss >> entries >> sumLHE >> sumGEN >> xsec >> xsecDB; // Read the rest of the fields
			}
            sample = trim(sample); // Trim any extra spaces from the sample name
            // Store the data in the map
            if(sumGEN<1.e-6) {   sumGEN = 1.e-6;  xsec = 0.; xsecDB = 0.; }
            float xsecWeight = 1000*xsec/sumGEN;
            if(use_LHE_weights) { xsecWeight = 1000*xsec/sumLHE; }
            if(use_xsecDB) { xsecWeight = 1000*xsecDB/sumGEN; }
            if(use_LHE_weights && use_xsecDB) { xsecWeight = 1000*xsecDB/sumLHE; }
            sampleMap[sample] = {entries, sumLHE, sumGEN, xsec, xsecDB, xsecWeight};
        }
    }

    mc_info_file.close();
    
    return sampleMap;
}
