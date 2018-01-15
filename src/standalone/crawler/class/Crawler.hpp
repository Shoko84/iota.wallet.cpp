#ifndef NEXUS_LAUNCHER_STANDALONE_CRAWLER
#define NEXUS_LAUNCHER_STANDALONE_CRAWLER

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <experimental/filesystem>
#include <unordered_map>
#include <functional>

namespace fs = std::experimental::filesystem;

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

namespace nx {

	class  Crawler
	{
	public:
		enum ENTRY_TYPE
		{
			ANY = 0,
			BLOCK_FILE,
			CHARACTER_FILE,
			DIRECTORY,
			FIFO,
			OTHER,
			REGULAR,
			SOCKET,
			SYMLINK
		};
	
		std::unordered_map<nx::Crawler::ENTRY_TYPE, std::function<bool(fs::path)>, EnumClassHash> entryTypeModifier = 
		{
			{nx::Crawler::ENTRY_TYPE::ANY,              [](const fs::path& p) {return fs::exists(p);}},
			{nx::Crawler::ENTRY_TYPE::BLOCK_FILE,       [](const fs::path& p) {return fs::is_block_file(p);}},
			{nx::Crawler::ENTRY_TYPE::CHARACTER_FILE,   [](const fs::path& p) {return fs::is_character_file(p);}},
			{nx::Crawler::ENTRY_TYPE::DIRECTORY,        [](const fs::path& p) {return fs::is_directory(p);}},
			{nx::Crawler::ENTRY_TYPE::FIFO,             [](const fs::path& p) {return fs::is_fifo(p);}},
			{nx::Crawler::ENTRY_TYPE::OTHER,            [](const fs::path& p) {return fs::is_other(p);}},
			{nx::Crawler::ENTRY_TYPE::REGULAR,          [](const fs::path& p) {return fs::is_regular_file(p);}},
			{nx::Crawler::ENTRY_TYPE::SOCKET,           [](const fs::path& p) {return fs::is_socket(p);}},
			{nx::Crawler::ENTRY_TYPE::SYMLINK,          [](const fs::path& p) {return fs::is_symlink(p);}}
		};

	public:
		Crawler(const std::string& path = ".", const bool log = false);
		virtual ~Crawler();

	public:
		void setPath(const std::string&);
		const std::string& getPath(void) const;
		const std::vector<fs::path>& getEntries(void);
		const std::vector<fs::path>& getSearch(void) const;
		const std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>& getSearchHistory(void) const;


	public:
		const std::vector<fs::path>& update(void);
		
	public:
		const std::vector<fs::path>& getDirectoriesList(void);
		const std::vector<fs::path>& getEntriesListByType(const nx::Crawler::ENTRY_TYPE);

	public:
		const std::vector<fs::path>& getDirectoriesListByPath(const std::string&);
		const std::vector<fs::path>& getEntriesListByTypeAndPath(const nx::Crawler::ENTRY_TYPE, const std::string&);

	private:
		bool archiveSearch(const nx::Crawler::ENTRY_TYPE = nx::Crawler::ENTRY_TYPE::ANY);
		void displayEntriesList(const std::vector<fs::path>& entries, const nx::Crawler::ENTRY_TYPE& type, const fs::path& path, const std::string& header = "NEW ENTRIES LIST") const;

	private:
		bool																	_log;
		std::string		                   										_path;
		std::vector<fs::path>                                            		_search;
		std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>  _searchHistory;
		std::vector<fs::path>               									_entries;

	};
}

#endif // !NEXUS_LAUNCHER_STANDALONE_CRAWLER