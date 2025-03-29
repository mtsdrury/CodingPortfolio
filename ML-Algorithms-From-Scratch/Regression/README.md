# 📉 Linear & Ridge Regression

This notebook explores core regression techniques by implementing both **Linear Regression** and **Ridge Regression** from scratch using NumPy. It demonstrates how regularization affects performance and stability, particularly in high-dimensional settings.

---

## 🧠 What’s Implemented

- ✅ **Linear Regression (Closed-form)**  
  Uses the normal equation to find the optimal weights without regularization.

- ✅ **Ridge Regression**  
  Incorporates L2 regularization to penalize large weights and improve generalization.

- ✅ **Synthetic Data Generation**  
  Creates random datasets with a controllable noise level and dimensionality to test model performance.

- ✅ **Mean Squared Error (MSE)**  
  Used to evaluate model predictions on unseen data.

- ✅ **Visualization**  
  Plot of MSE values vs. different regularization strengths (`lambda` values).

---

## 📂 Files

- `linear_vs_ridge.ipynb` — Contains the full implementation, evaluation, and analysis

---

## 📈 Example Plot

The notebook includes a plot showing how increasing the regularization parameter `λ` affects test error:

