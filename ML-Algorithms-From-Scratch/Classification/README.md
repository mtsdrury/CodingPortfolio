# 🔢 Classification: MNIST Digit Recognition (1 vs 7)

This project demonstrates multiple classification algorithms — all implemented and trained on a binary classification task using the MNIST dataset. The focus is on comparing performance and behavior across classic and deep learning approaches using **PyTorch**.

---

## 🧠 What’s Implemented

- **Logistic Regression**  
  Linear classifier trained with binary cross-entropy loss

- **Support Vector Machine (SVM)**  
  Uses hinge loss for margin-based classification

- **Feedforward Neural Network (NN)**  
  Single hidden layer with ReLU nonlinearity

- **Convolutional Neural Network (CNN)**  
  Two-layer convolutional feature extractor with fully connected head

---

## 🧪 Task: MNIST 1 vs 7

All models are trained on a filtered version of MNIST containing only digits **1 and 7**, reshaped and preprocessed for different input formats:
- Flattened vectors for linear/logistic/SVM/NN
- Raw 28x28 grayscale images for CNN

---

## 📊 Evaluation

Each model is evaluated using:
- Accuracy on the test set
- Print statements showing training loss (or accuracy) per epoch

---

## 🛠️ Tools & Libraries

- Python
- PyTorch
- torchvision
- NumPy
- Matplotlib (optional for visualization)

---

## 📁 File

- `mnist_classifiers_logreg_svm_nn_cnn.ipynb`  
  Full implementation and comparison of all models

---

## 🧠 Learning Objectives

- Compare classic ML (logistic/SVM) vs deep learning approaches
- Implement custom training loops in PyTorch
- Understand loss functions like BCE and hinge loss
- Work with image data in both vector and 2D formats

---
