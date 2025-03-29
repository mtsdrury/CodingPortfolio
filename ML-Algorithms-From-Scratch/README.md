# Machine Learning Algorithms from Scratch 🧠✨

This repository showcases core machine learning algorithms implemented from scratch or with minimal libraries. The goal is to demonstrate a deep understanding of fundamental ML concepts by building and evaluating models manually — without relying heavily on high-level wrappers.

Each project is focused, self-contained, and highlights a specific category of machine learning, complete with performance analysis and visualizations.

---

## 🔍 What's Inside

### 📉 [Regression](./regression/)
Implementations of linear and ridge regression, including:
- Manual solution using the closed-form normal equation
- Ridge regression with L2 regularization
- MSE loss evaluation and plotting
- Synthetic dataset generation and scaling behavior

> File: `linear_vs_ridge.ipynb`

---

### 🔢 [Classification](./classification/)
Binary classification using:
- Logistic Regression
- Support Vector Machine (Hinge Loss)
- Feedforward Neural Network
- Convolutional Neural Network

All models trained on MNIST digits **1 vs 7**, implemented using PyTorch with custom loss functions where applicable.

> File: `mnist_classifiers_logreg_svm_nn_cnn.ipynb`

---

### 🎨 [Clustering](./clustering/)
Image segmentation via unsupervised clustering:
- Custom K-means and K-medoids algorithms
- Comparison of convergence behavior and outputs
- RGB-based compression of image data

> File: `image_segmentation_kmeans_kmedoids.ipynb`

---

### 🎥 [Recommender System](./recommender-system/)
Collaborative filtering using matrix factorization:
- Manual implementation of SGD optimization
- Synthetic low-rank data generation
- Evaluation on masked (observed) ratings
- Optional regularization and runtime tracking

> File: `matrix_factorization.ipynb`

---

## 🛠️ Tech Stack

- Python
- NumPy & SciPy
- PyTorch (for NN/CNN models)
- Matplotlib for visualizations
- Jupyter Notebooks

---

## 📌 Why This Repo?

Unlike most ML repos that rely on frameworks to hide complexity, this one focuses on **transparent, from-scratch implementations** to reinforce understanding of how these algorithms work under the hood.

It's also designed to be clean, modular, and extensible — each project stands on its own, but together they reflect a solid grasp of essential machine learning principles.

---

## 📬 Contact

Want to collaborate or discuss something here?
Reach out via [GitHub](https://github.com/mtsdrury) or feel free to open an issue.

