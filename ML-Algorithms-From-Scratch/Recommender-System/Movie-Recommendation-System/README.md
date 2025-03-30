# Multi-User Recommendation System

This code demonstrates a multi-user recommendation system built using a matrix factorization approach. It leverages manually defined latent factors to generate movie recommendations for multiple users. Each recommendation includes a scaled predicted rating (mapped to a conventional 1–5 range) and an explanation based on the dominant latent factor (e.g., genre).

---

## What It Does

- **Latent Factor Modeling:**  
  Users and movies are represented by latent factor vectors. These factors capture hidden attributes such as movie genres (Action, Comedy, Drama, SciFi, Romance) or user preferences.

- **Prediction & Scaling:**  
  The system computes the predicted ratings for a user by taking the dot product of the user’s and each movie’s latent factors. These raw ratings are then scaled linearly to the [1, 5] range for interpretability.

- **Single-User Recommendations:**  
  The function `recommend_movies_manual` returns the top-N movie recommendations for a single user, along with the dominant category and an explanation for each recommendation.

- **Multi-User Recommendations:**  
  The function `recommend_movies_for_users` aggregates recommendations for a list of users, making it easy to view recommendations across multiple profiles.

---

## How to Use

1. **Define your latent factors and movie titles:**  
   Manually specify the latent factor matrices for users (`U`) and movies (`V`), and define corresponding movie titles and category names.

2. **Generate Recommendations:**  
   Call the `recommend_movies_for_users` function with a list of user indices, the latent factor matrices, movie titles, and the category names. Adjust `top_n` to control how many recommendations per user are returned.

3. **View Results:**  
   The system prints out the recommendations for each user, showing:
   - Movie title
   - Scaled predicted rating (on a scale of 1–5)
   - Explanation highlighting the dominant latent factor (category)
