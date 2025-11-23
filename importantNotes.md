# Notes

1. A git repository is made of two things: a “work tree”, where the files meant to be in version control live, and a “git directory”, where Git stores its own data. In most cases, the worktree is a regular directory and the git directory is a child directory of the worktree, called .git.

---

## C++

1. ```cpp
    // IMPORTANT:
    file.seekg(0, file.end);    // Move pointer to end of file
    int length = file.tellg();  // Get file size in bytes
    file.seekg(0, file.beg);    // Reset pointer to start for reading data

--- 

### `.git/` Directory Layout

A Git repository’s internal structure consists of the following key files and directories:

#### **1. `.git/objects/`**
- pending

#### **2. `.git/refs/`**
- The **reference store**
- Contains pointers to commits
- Includes two important subfolders:
  - `heads/` → branch references  
  - `tags/` → tag references  

#### **3. `.git/HEAD`**
- a reference to the current HEAD (more on that later!)
#### **4. `.git/config`**
- Repository-specific configuration file
- Contains settings such as:
  - remotes
  - user information
  - hooks configuration
  - branch settings

#### **5. `.git/description`**
- Human-readable description of the repository
- Mostly used by GitWeb and rarely used otherwise.
