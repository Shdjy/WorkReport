#include "pch.h"
#include "ReportStorage.h"

bool ReportStorage::Save(const std::string& baseDir, ReportBase& report)
{
	std::string filePath = baseDir + "/" + report.GetStorageFilePath();

	nlohmann::json root;

	std::ifstream ifs(filePath);
	if (ifs.is_open())
	{
		ifs >> root;
	}

	root[report.GetTimeString()].push_back(report.ToJson());

	std::ofstream ofs(filePath, std::ios::trunc);
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << root.dump(4);
	return true;
}
