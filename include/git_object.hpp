#ifndef GIT_OBJECT
#define GIT_OBJECT

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include "repo.h"
#include "utils.h"

enum class GitObjectType { Commit, Tree, Tag, Blob, Unknown };

static GitObjectType gitObjectTypeFromString(const std::string& s);

// --------------------
//       BASE CLASS
// --------------------
class GitObject {
   public:
    GitObject() {};
    /*
     *This function MUST be implemented by subclasses.

      It must read the object's contents from self.data, a byte string, and
      do whatever it takes to convert it into a meaningful representation.
      What exactly that means depend on each subclass.

      In mygit i have chosen to store the git object let say e2f88888....
      as
        dir - e2f (i.e first 3 chars but in real git it is first 2 chars as the dir path)

        remaining as the the file name

      // NOTE:
      // No particular reason just my stupid fantacy to do something different.
     */
    // virtual std::string serialize() const = 0;

    /*
     * here desserialize the previously serialized data
     */
    // virtual void deserialize(const std::string& data) = 0;

    /*
     * Read object sha from Git repository repo.  Return a
     * GitObject whose exact type depends on the object.
     *
     * Params:
     *
     * repo - path where .mygit directory is located can find using repoFind
     * sha - sha of the gtiObject\n
     *
     * let say this is the commit

     * git cat-file -p commitId

     * response :
          tree 24fcc7dbadc940ced7d4e5510620f8d29183273f
          author Aum Patel <email> 1751355306 +0530
          committer Aum Patel <email> 1751355306 +0530

          initial commit

    * IMPORTANT:
    * so internally what git does is that
    *
    * tree 166\x00 .....remaining
    *
    * 0. uncompress data using zlib
    * 1. tree is the GitObject Type
    * 2. 166 is the file size
    * 3. so this function fist interprets GitObject and then sends remaining
    *    data to the respective GitObject constructor
    *
     */
    static std::unique_ptr<GitObject> objectRead(const std::filesystem::path& repo, const std::string& sha);

    static std::string objectWrite(const std::unique_ptr<GitObject> obj,
                                   std::optional<std::filesystem::path> repo = std::nullopt);
};

// --------------------
//    Derived CLASSES
// --------------------

class GitCommit : public GitObject {
   public:
    GitCommit() = default;
    explicit GitCommit(const std::string& raw) {
        // deserialize(raw);
    }
    //
    //  std::string serialize() const override;
    //  void deserialize(const std::string& data) override;
};

class GitTree : public GitObject {
   public:
    GitTree() = default;
    explicit GitTree(const std::string& raw) {
        // deserialize(raw);
    }
    //
    //  std::string serialize() const override;
    //  void deserialize(const std::string& data) override;
};

class GitTag : public GitObject {
   public:
    GitTag() = default;
    explicit GitTag(const std::string& raw) {
        // deserialize(raw);
    }
    //
    //  std::string serialize() const override;
    //  void deserialize(const std::string& data) override;
};

class GitBlob : public GitObject {
   public:
    GitBlob() = default;
    explicit GitBlob(const std::string& raw) {
        // deserialize(raw);
    }
    //
    // std::string serialize() const override;
    // void deserialize(const std::string& data) override;
};

#endif  // !GIT_OBJECT
