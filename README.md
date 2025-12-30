# High-Performance JSON Library in x86_64 Assembly & C

[![License: GPL-2.0](https://img.shields.io/badge/License-GPL%202.0-blue.svg)](https://opensource.org/licenses/GPL-2.0)
[![Stars](https://img.shields.io/github/stars/KatoKode/JSON?style=social)](https://github.com/KatoKode/JSON/stargazers)

A lightweight, dependency-free JSON parsing and building library with core components hand-optimized in x86_64 assembly language. Delivered as a shared library (`libjson.so`) with a clean C API.

### Highlights
- Full JSON support: nested objects, arrays, strings, numbers, booleans, null
- Significant low-level routines in pure assembly for fast tokenization and parsing
- Manual memory management — **100% Valgrind-clean** (zero leaks, even on complex nested inputs)
- No external dependencies — perfect for embedded systems, firmware, or performance-critical applications
- Builder + parser + tree walker in one cohesive library

---

### Quick Start


# Build the shared library
```bash
sh ./json_make.sh
```

# Run the demo (parses, builds, traverses, and cleans multiple JSON structures)
```bash
cd ./demo
./go_demo.sh
```

---

This repository is written for a Linux OS.  FYI, the JSON Library was created on an OpenSuse Linux distro.  I do all my development on OpenSuse.

---

### API Reference

Detailed function-by-function documentation, including parameters, returns, and usage notes:

📖 [Detailed API Reference](./json/API.md)

---

# LEAVE A STAR
If you like the KatoKode JSON repository by all means leave a STAR to encourage others to visit.

Thanks, and Have Fun!
