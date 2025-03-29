# 🎥 Recommender System via Matrix Factorization

This project demonstrates a collaborative filtering recommender system implemented from scratch using **low-rank matrix factorization**. The goal is to predict user-item ratings by approximating the original (sparse) rating matrix as the product of two lower-dimensional matrices.

---

## 🧠 What’s Implemented

- ✅ **Synthetic Ratings Generator**  
  Creates a low-rank user-item matrix with added noise and configurable sparsity.

- ✅ **Matrix Factorization via SGD**  
  Optimizes two matrices `U` (users) and `V` (items) using stochastic gradient descent on observed ratings.

- ✅ **Masked Evaluation**  
  Mean squared error is computed only on observed (non-zero) entries, mimicking real-world sparsity.

- ✅ **Optional Regularization**  
  L2 regularization terms can be added to reduce overfitting.

---

## 💡 Key Concepts

- Collaborative filtering
- Low-rank matrix approximation
- Loss minimization via SGD
- Cold-start and sparsity considerations

---

## 📊 Output

- Final predicted ratings matrix `U @ V.T`
- MSE on observed entries
- Optionally: error tracking across epochs

---

## 🛠️ Tools

- Python
- NumPy (no ML libraries used)
- Matplotlib (optional for plotting errors or convergence)

---

## 📁 File

- `matrix_factorization.ipynb` — Full implementation including data generation, training, and evaluation

---

## 🧠 Learning Objectives

- Understand recommender systems from a modeling and optimization perspective
- Implement matrix factorization without using high-level libraries
- Handle missing data and evaluate performance on sparse matrices

---
