#include "Crawler.hpp"

nx::Crawler::Crawler(const std::string& path, const bool log)
:
	_path(path),
	_log(log)
{
	this->update();
}

nx::Crawler::~Crawler()
{

}

void nx::Crawler::setPath(const std::string& path)
{
	this->_path = path;
	this->update();
}

const std::string& nx::Crawler::getPath() const
{
	return this->_path;
}

const std::vector<fs::path>& nx::Crawler::getEntries()
{
	return this->getEntriesListByType(nx::Crawler::ENTRY_TYPE::ANY);
}

const std::vector<fs::path>& nx::Crawler::getSearch() const
{
	return this->_search;
}

const std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>& nx::Crawler::getSearchHistory() const
{
	return this->_searchHistory;
}

const std::vector<fs::path>& nx::Crawler::update()
{
	this->_entries.clear();

	for (const fs::path & p : fs::directory_iterator(this->_path)) {
		this->_entries.push_back(p);
	}

	return this->_entries;
}

bool nx::Crawler::archiveSearch(const nx::Crawler::ENTRY_TYPE type)
{
	if (this->_search.size() > 0) {
		this->_searchHistory.push_back(std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>(type, _search));
		this->_search.clear();
		return true;
	}
	return false;
}

void nx::Crawler::displayEntriesList(const std::vector<fs::path>& entries, const nx::Crawler::ENTRY_TYPE& type, const fs::path& path, const std::string& header) const
{
	if (!this->_log) return;

	int   paddingVarName, currSize, idx;	
	paddingVarName = idx = currSize = 0;

	std::cerr << "_> " << header << std::endl;
	std::cerr << "_> There is " << entries.size() << " entries of type (" << type << ") in (" << path << ")" << std::endl;
	// Get Padding
	for (auto& it : entries) {
		paddingVarName = ((currSize = it.string().size()) > paddingVarName)? currSize: paddingVarName;
	}
	paddingVarName += 5;
	// Display table header
	for (int i = 0; i < paddingVarName + 17; i++) std::cerr << "-";
		std::cerr << "|" << std::endl << "|  " << std::setw(10) << "ID" << " | " << std::setw(paddingVarName) << " Results" << " |" << std::endl;
	// Display (header / content) separator
	for (int i = 0; i < paddingVarName + 17; i++) std::cerr << "-";
	std::cerr << "|" << std::endl;
	// Display content
	for (auto& it : entries) {
		std::cerr << "|  " << std::setw(10) << idx << " | " << std::setw(paddingVarName) << it << " |" << std::endl;
		idx++;
	}
	// Display footer
	for (int i = 0; i < paddingVarName + 17; i++) std::cerr << "-";
		std::cerr << "|" << std::endl;
	std::cerr << std::endl;
}

const std::vector<fs::path>& nx::Crawler::getEntriesListByType(const nx::Crawler::ENTRY_TYPE type)
{
	return this->getEntriesListByTypeAndPath(type, this->_path);
}

const std::vector<fs::path>& nx::Crawler::getDirectoriesList()
{
	return this->getEntriesListByTypeAndPath(nx::Crawler::ENTRY_TYPE::DIRECTORY, this->_path);
}

const std::vector<fs::path>& nx::Crawler::getDirectoriesListByPath(const std::string& path)
{
	return this->getEntriesListByTypeAndPath(nx::Crawler::ENTRY_TYPE::DIRECTORY, path);
}

const std::vector<fs::path>& nx::Crawler::getEntriesListByTypeAndPath(const nx::Crawler::ENTRY_TYPE type, const std::string& path)
{
	this->archiveSearch(type);

	for (const fs::path & p : fs::directory_iterator(path))
	{
		if (nx::Crawler::entryTypeModifier[type](p)) {
			this->_search.push_back(p);
		}
	}

	this->displayEntriesList(this->_search, type, path, "NEW SEARCH");

	return this->_search;
}