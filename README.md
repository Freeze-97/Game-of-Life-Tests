# 🧬 Game of Life – C++ Project

This is a modular and extensible implementation of **Conway's Game of Life**, written in modern C++. The project is structured around core components like cells, populations, and rules of existence, and is complemented by unit tests for validation.

## 🧪 Testing

This project includes **unit tests** for the following components:

- **Cells & Populations** – Ensures individual cell behavior and population updates work as expected.
- **Rules of Existence** – Each rule implementation (Conway, Erik, Von Neumann) has isolated tests to verify proper life/death behavior.
- **Rule Factory** – Tests that the factory correctly instantiates rules based on user input or configuration.

## 🌱 Rule Variants
The following rules of existence are implemented and can be selected dynamically:

- Conway – Traditional Game of Life rules

- Erik – Custom rule variant

- Von Neumann – Based on Von Neumann neighborhood

## 📄 Documentation

Documentation is available in the `Docs/` folder and can be generated using **Doxygen**.

To generate docs:

```bash
cd Docs
doxygen Doxyfile
```

## ▶️ How to Build and Run

1. Clone and initialize submodules:
```bash
git clone --recurse-submodules <repo-url>
```

2. Build using CMake:
```bash
mkdir build && cd build
cmake ..
make
```

3. Run the game:
```bash
./GameOfLife
```
