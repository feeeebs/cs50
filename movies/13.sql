SELECT DISTINCT people.name FROM people
    JOIN stars s1 on people.id = s1.person_id
    JOIN movies on s1.movie_id = movies.id
    JOIN stars s_kb on movies.id = s_kb.movie_id
    join people p_kb on s_kb.person_id = p_kb.id
WHERE p_kb.name = 'Kevin Bacon' AND p_kb.birth = 1958
    AND people.name != 'Kevin Bacon';