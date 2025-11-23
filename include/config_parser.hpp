#include <cstddef>
#include <fstream>
#include <ostream>
#include <string>
#include <unordered_map>
#ifndef CONFIG_PARSER
#define CONFIG_PARSER

// [core]
//         repositoryformatversion = 0
//         filemode = true
//         bare = false
//         logallrefupdates = true

class Section {
   private:
    std::unordered_map<std::string, std::string> kv;

   public:
    void set(const std::string& key, const std::string& value);
    void write(std::ostream& out) const;
    const std::unordered_map<std::string, std::string> map() const;
};

/*
 *  write config in the config file
 */
class ConfigParser {
   private:
    std::unordered_map<std::string, Section> sections;

   public:
    Section& operator[](const std::string& name);

    void write(const std::string& file) const;
    const std::unordered_map<std::string, std::string> read(const char* CONFIG_FILE,
                                                            const std::string& sectionName) const;
};

#endif  // !CONFIG_PARSER
