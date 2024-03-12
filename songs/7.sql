SELECT AVG(energy) from songs
JOIN artists on artist_id = artists.id
WHERE artists.name = 'Drake';
