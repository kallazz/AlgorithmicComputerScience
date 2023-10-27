-- 1.
SHOW FULL TABLES;

-- 2.
SELECT title
FROM film
WHERE length > 120;

-- 3.
SELECT title
FROM film
WHERE rating = "PG-13"
ORDER BY length ASC
LIMIT 4;

-- 4.
SELECT film.title, language.name
FROM film
INNER JOIN language
ON film.language_id = language.language_id
WHERE film.description LIKE "%Drama%";

-- 5.
SELECT film.title
FROM film
INNER JOIN film_category
ON film.film_id = film_category.film_id
INNER JOIN category
ON film_category.category_id = category.category_id
WHERE category.name = "Family" AND film.description LIKE "%Documentary%";

-- 6.
SELECT film.title
FROM film
INNER JOIN film_category
ON film.film_id = film_category.film_id
INNER JOIN category
ON film_category.category_id = category.category_id
WHERE category.name = "Children" AND film.rating <> "PG-13";

-- 7.
SELECT rating, COUNT(*) AS film_count
FROM film
GROUP BY rating;

-- 8.
SELECT DISTINCT film.title
FROM film
INNER JOIN inventory
ON film.film_id = inventory.film_id
INNER JOIN rental
ON inventory.inventory_id = rental.inventory_id
WHERE DATE(rental.rental_date) BETWEEN "2005-05-31" AND "2005-06-30"
ORDER BY film.title DESC;

-- 9.
SELECT DISTINCT actor.first_name, actor.last_name
FROM film
INNER JOIN film_actor
ON film.film_id = film_actor.film_id
INNER JOIN actor
ON film_actor.actor_id = actor.actor_id
WHERE film.special_features LIKE "%Deleted Scenes%";

-- 10.
SELECT DISTINCT customer.first_name, customer.last_name
FROM customer
INNER JOIN rental
ON customer.customer_id = rental.customer_id
INNER JOIN payment
ON rental.rental_id = payment.rental_id AND rental.staff_id <> payment.staff_id;

-- 11.
SELECT customer.first_name, customer.last_name, COUNT(*) AS rented_films
FROM customer
INNER JOIN rental
ON customer.customer_id = rental.customer_id
GROUP BY rental.customer_id
HAVING rented_films >
(SELECT COUNT(*)
FROM rental
INNER JOIN customer
ON rental.customer_id = customer.customer_id
WHERE email = "MARY.SMITH@sakilacustomer.org");

-- 12.
SELECT a1.first_name, a1.last_name, a2.first_name, a2.last_name
FROM actor a1, actor a2
INNER JOIN film_actor f1, film_actor f2
WHERE f1.actor_id = a1.actor_id
AND f2.actor_id = a2.actor_id
AND f1.film_id = f2.film_id
AND a1.actor_id < a2.actor_id
GROUP BY a1.actor_id, a2.actor_id
HAVING COUNT(*) > 1;

-- 13.
SELECT actor.last_name
FROM actor
WHERE actor_id NOT IN
(SELECT film_actor.actor_id
FROM film_actor
INNER JOIN film
ON film_actor.film_id = film.film_id
WHERE film.title LIKE "C%");

-- 14.
SELECT actor.last_name
FROM actor
WHERE
(SELECT COUNT(*)
FROM film_actor
INNER JOIN film_category
ON film_actor.film_id = film_category.film_id
INNER JOIN category
ON film_category.category_id = category.category_id
AND category.name = "Horror"
WHERE actor.actor_id = film_actor.actor_id)
    >
(SELECT COUNT(*)
FROM film_actor
INNER JOIN film_category
ON film_actor.film_id = film_category.film_id
INNER JOIN category
ON film_category.category_id = category.category_id
AND category.name = "Action"
WHERE actor.actor_id = film_actor.actor_id);

-- 15.
SELECT customer.first_name, customer.last_name
FROM customer
INNER JOIN payment
ON customer.customer_id = payment.customer_id
GROUP BY customer.customer_id
HAVING AVG(payment.amount) <
(SELECT AVG(amount)
FROM payment
WHERE DATE(payment_date) = "2005-07-30");

-- 16.
UPDATE film
SET language_id =
(SELECT language_id
FROM language
WHERE name = "Italian")
WHERE title = "YOUNG LANGUAGE";

-- 17.
INSERT INTO language(name)
VALUES("Spanish");

UPDATE film
SET language_id =
(SELECT language_id
FROM language
WHERE name = "Spanish")
WHERE film.film_id IN
(SELECT film_actor.film_id
FROM film_actor
INNER JOIN actor
ON film_actor.actor_id = actor.actor_id
WHERE actor.first_name = "ED" AND actor.last_name = "CHASE");

-- 18.
ALTER TABLE language
ADD films_no INT;

UPDATE language
SET films_no =
(SELECT COUNT(*)
FROM film
WHERE language.language_id = film.language_id);

-- 19.
ALTER TABLE film
DROP COLUMN release_year;