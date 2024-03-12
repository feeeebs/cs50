SELECT AVG(rating) FROM ratings
JOIN movies on movie_id = movies.id
WHERE movies.year = 2012;