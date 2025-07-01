# mygit

`mygit` is a minimal Git-like version control system written in C++.  
It aims to teach and demonstrate how Git works under the hood by re-implementing key features from scratch.

---

## 🚀 Features

- `mygit init` — Initialize a new repository (`.mygit/`)
- `mygit add <filename>` — Stage files by hashing and storing snapshots
- `mygit commit -m "<message>"` — Save current state (coming soon)
- `mygit log` — View commit history (coming soon)
- `mygit checkout <hash>` — Restore previous versions (coming soon)

---

## 🛠️ Build Instructions

### Prerequisites
- C++17 compiler (GCC, Clang, MSVC)
- CMake ≥ 4.0

### 🧱 Build Steps

```bash
git clone https://github.com/Aum-Patel1234/mygit.git
cd mygit
mkdir build && cd build
cmake ..
make
./mygit init