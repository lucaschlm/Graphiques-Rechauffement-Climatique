#pragma once

#include <vector> // std::vector
#include <string> // std::string
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map> // std::map
#include <utility> // std::pair

class SAE_Datas_Heat {
	// Private Datas
	std::vector<std::map<int, std::pair<float,float> > > _vRawData;
	std::vector<int> _vIdStation;
	std::vector<std::vector<float>> _vStationTmoy;

	// Private Functions
	std::string readFileIntoString(const std::string& path)const;
	std::vector<std::string> listAllFiles()const;
	std::map<int, std::pair<float, float> > parseContentFile(std::string filename);
	void convertDataInList();

public:
	// Public Functions
	SAE_Datas_Heat();
	size_t nbMonths()const;
	const std::vector<int>& getIdStation()const { return _vIdStation; }
	const std::vector<std::vector<float>>& getStationTmoy()const { return _vStationTmoy; }
};

