#include "../include/git_object.hpp"

GitObjectType gitObjectTypeFromString(const std::string& s) {
    if (s == "commit")
        return GitObjectType::Commit;
    if (s == "tree")
        return GitObjectType::Tree;
    if (s == "tag")
        return GitObjectType::Tag;
    if (s == "blob")
        return GitObjectType::Blob;
    return GitObjectType::Unknown;
}

std::unique_ptr<GitObject> GitObject::objectRead(const std::filesystem::path& repo, const std::string& sha) {
    const std::string dirPrefix = sha.substr(0, 3);
    const std::string fileName = sha.substr(3);
    auto objectPath = repo / "objects" / dirPrefix / fileName;

    std::optional<std::filesystem::path> path = repoFile(repo, objectPath, true);

    if (!path) {
        throw std::runtime_error("File for path " + objectPath.string() + "not made.");
    }

    // Decompress git object
    std::string rawStr = decompressGitObject(path->string());

    // Parse: "<type> <size>\0<payload>"
    std::size_t sp = rawStr.find(' ');
    if (sp == std::string::npos)
        throw std::runtime_error("Malformed object header (no space)");

    std::string fmt = rawStr.substr(0, sp);  // type: "commit", "tree", etc.

    auto nz = rawStr.find('\x00', sp + 1);
    if (nz == std::string::npos)
        throw std::runtime_error("Malformed object header (no null terminator)");

    std::string sizeStr = rawStr.substr(sp + 1, nz - (sp + 1));
    std::size_t declaredSize = std::stoul(sizeStr);

    std::size_t actualSize = rawStr.size() - nz - 1;
    if (declaredSize != actualSize) {
        throw std::runtime_error("Malformed object: bad length, declared=" + sizeStr +
                                 " actual=" + std::to_string(actualSize));
    }

    std::string payload = rawStr.substr(nz + 1);

    GitObjectType typ = gitObjectTypeFromString(fmt);
    switch (typ) {
        case GitObjectType::Commit:
            return std::make_unique<GitCommit>(payload);
        case GitObjectType::Tree:
            return std::make_unique<GitTree>(payload);
        case GitObjectType::Tag:
            return std::make_unique<GitTag>(payload);
        case GitObjectType::Blob:
            return std::make_unique<GitBlob>(payload);
        default:
            throw std::runtime_error("Unknown git object type: " + fmt);
    }
}

// std::string GitObject::objectWrite(const std::unique_ptr<GitObject> obj, std::optional<std::filesystem::path> repo) {
//     std::string data = obj->serialize();
//
//     std::string result = data.substr(0, 3) + ' ' + std::string(data.size()).encode() + '\x00' + data;
//
//     // auto sha =
// }
