#include "../include/config_parser.hpp"

void Section::set(const std::string& key, const std::string& value) {
    this->kv[key] = value;
}

void Section::write(std::ostream& out) const {
    for (const auto& [key, value] : this->kv) {
        out << "\t" << key << " = " << value << "\n";
    }
}

Section& ConfigParser::operator[](const std::string& name) {
    return sections[name];
}

void ConfigParser::write(const std::string& file) const {
    std::ofstream out(file);

    for (const auto& [sectionName, section] : sections) {
        out << "[" << sectionName << "]\n";
        section.write(out);
        out << "\n";
    }
}

const std::unordered_map<std::string, std::string> Section::map() const {
    return this->kv;
}

const std::unordered_map<std::string, std::string> ConfigParser::read(const char* CONFIG_FILE,
                                                                      const std::string& sectionName) const {
    // DOCS: https://cplusplus.com/reference/istream/istream/read/
    std::ifstream file(CONFIG_FILE, std::ifstream::binary);
    std::unordered_map<std::string, std::string> result;

    if (file) {
        // IMPORTANT:
        file.seekg(0, file.end);    // Move pointer to end of file
        int length = file.tellg();  // Get file size in bytes
        file.seekg(0, file.beg);    // Reset pointer to start for reading data

        std::string buffer(length, '\0');
        file.read(&buffer[0], length);
        file.close();

        // Parse buffer (INI logic)
        bool inSection = false;

        auto trim = [](std::string& s) {
            size_t start = s.find_first_not_of(" \t\r");
            size_t end = s.find_last_not_of(" \t\r");
            if (start == std::string::npos) {
                s = "";
                return;
            }
            s = s.substr(start, end - start + 1);
        };

        size_t pos = 0;
        while (pos < length) {
            size_t next = buffer.find('\n', pos);
            if (next == std::string::npos)
                next = buffer.size();

            std::string line = buffer.substr(pos, next - pos);
            pos = next + 1;

            trim(line);
            if (line.empty())
                continue;

            if (line.front() == '[') {
                std::string currentSection = line.substr(1, line.size() - 2);
                trim(currentSection);
                inSection = (sectionName == currentSection);
                continue;  // form here below lines will be our key value pairs
            }

            if (!inSection)  // break if not in section
                continue;

            size_t equalToPos = line.find('=');
            if (equalToPos == std::string::npos)
                continue;

            std::string key = line.substr(0, equalToPos);
            std::string val = line.substr(equalToPos + 1);

            trim(key);
            trim(val);

            result[key] = val;
        }
    }

    return result;
}
