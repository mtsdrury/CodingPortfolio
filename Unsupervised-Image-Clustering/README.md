# K-means vs. K-medoids for Image Segmentation

This project implements and compares **K-means** and **K-medoids** clustering algorithms for unsupervised image segmentation based on color. The algorithms group similar pixels into clusters, and each cluster is represented by a centroid (K-means) or a medoid (K-medoids). The result is a compressed version of the image using `K` representative colors.

---

## 🧠 What’s Implemented

- ✅ **Custom implementation of K-means**  
- ✅ **Custom implementation of K-medoids**  
- ✅ **Efficient distance computations using NumPy**  
- ✅ **Image reconstruction and visualization**  
- ✅ **Export of segmented images**

---

## 🖼️ How It Works

1. Images are loaded and flattened into RGB pixel arrays.
2. Pixels are normalized to the range `[0, 1]`.
3. Clustering is performed using both algorithms for `K` clusters.
4. New images are reconstructed using the cluster centers/medoids.
5. Side-by-side comparisons are visualized and saved.

---

## 🧪 Example Output

Each image is processed and saved in two forms:
- `image_converted_mykmeans_5.jpg`
- `image_converted_mykmedoids_5.jpg`

Both are displayed side-by-side using `matplotlib`.

---

## 📂 How to Use

Place your image files in the working directory and run the script. Supported formats:
- `.jpg`, `.png`, `.jpeg`, `.bmp`, `.tiff`, `.gif`

```python
K = 5  # number of clusters
