# MST and Second-Best MST Analysis

This project explores algorithms for computing a **Minimum Spanning Tree (MST)** using both heap-based and array-based implementations of Prim's algorithm. It also computes a **second valid MST** (second-best MST) and analyzes their **runtime complexity**, **cost**, and **scalability** through both synthetic and real datasets.

---

## 🚀 Features

- **Prim's Algorithm (Heap & Array versions)**: 
  - Heap version approximates `O(m log n)`
  - Array version approximates `O(n^2)`
- **Second-Best MST Search**:
  - Finds an alternate MST with a different edge set and minimal increased cost
- **Complexity and Runtime Analysis**:
  - Empirical timing and cost comparison across varying input sizes
  - Synthetic graph generation and scaling behavior
- **Visualization**:
  - Plots spatial layouts of randomly generated points
  - Compares running times across algorithm variants

---

## 📊 Inputs

- Coordinates of nodes (stations) in 2D space
- Manhattan distance is used as the edge weight
- Optionally reads zipped input files (`.zip`) containing multiple test cases

---

## 📈 Outputs

- MST cost from both heap and array implementations
- Cost of the second-best MST
- Scatter plots of spatial input layouts
- Line plots comparing running times vs input sizes

---

## 🛠️ Tools & Libraries

- Python 3
- `heapq` for heap-based MST
- `zipfile` and `io` for batch input processing
- `matplotlib`, `numpy`, `random`, and `itertools` for analysis and plotting

---

## 📂 Notes

- Data files are not included in the repository.
- Outputs are shown in the notebook to demonstrate results.
- The zipped input dataset is referenced via an absolute path in the script (`HW2Q3_inputs.zip`). This path should be updated if rerunning locally.

---

## 🧠 Learning Highlights

- Trade-offs between different MST implementations
- Practical time complexity behavior vs theoretical bounds
- Graph algorithms, disjoint set (Union-Find), and edge normalization
- Data visualization and performance benchmarking in Python

---

