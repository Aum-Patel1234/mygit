#ifndef REPO

#include <filesystem>
#include <optional>
#include "utils.h"
/**
 * Compute path under the repo's .git directory.
 *
 * Joins the current repo directory with a relative path.
 *
 * @param currDir      The base directory (usually the .git directory).
 * @param pathToJoin   The path segment to append.
 *
 * @return A combined filesystem path.
 */
inline std::filesystem::path repoPath(const std::filesystem::path& cwd, const std::filesystem::path pathToJoin);

/**
 * This functions makes makes directory if absent and specified mkdir=True
 *
 * returns path if present and nullptr if absent
 *
 */
std::optional<std::filesystem::path> repoDir(const std::filesystem::path& cwd,
                                             const std::filesystem::path& path,
                                             bool mkdir = false);

std::optional<std::filesystem::path> repoFile(const std::filesystem::path& cwd,
                                              const std::filesystem::path& filePath,
                                              bool mkdir = false);

/*
 * Write the default config file
 *
 * The returned ConfigParser object contains a single section "[core]"
 * with the following default settings:
 *
 *     repositoryformatversion = 0
 *     filemode                = false
 *     bare                    = false
 *
 * @return A ConfigParser object pre-filled with the default Git config.
 */
void repoDefaultConfig();

#endif  // !GITINIT
