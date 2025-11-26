# Notes

1. A git repository is made of two things: a “work tree”, where the files meant to be in version control live, and a “git directory”, where Git stores its own data. In most cases, the worktree is a regular directory and the git directory is a child directory of the worktree, called .git.

---

## C++

1. ```cpp
    // IMPORTANT:
    file.seekg(0, file.end);    // Move pointer to end of file
    int length = file.tellg();  // Get file size in bytes
    file.seekg(0, file.beg);    // Reset pointer to start for reading data
    ```
    

## 2. IMPORTANT: weakly_canonical(path)

**fs::weakly_canonical(path)** returns an absolute, normalized version of a path,
but **does NOT require the full path to exist**. This avoids exceptions and
makes it ideal for directory walking (e.g., searching for a `.git` folder).

### What it does:
1. Converts the given path into an **absolute path**
2. Removes `.` and `..` components (normalization)
3. Resolves symlinks **only** for existing directories
4. Leaves non-existing parts untouched (no throw)

### Example:
Input : `"src/../build/output"`  
Output: `"/home/user/project/build/output"`  
*(Even if `/build/output` does NOT exist)*

### Why it's useful:
Perfect for recursive upward searches where some directories might not exist,
such as locating a `.git` directory by moving toward the root.

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
