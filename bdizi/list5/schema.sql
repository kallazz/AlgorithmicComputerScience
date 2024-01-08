CREATE DATABASE blog_app;
USE blog_app;

/******************************************************** Tables ********************************************************/
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(30) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    created TIMESTAMP NOT NULL DEFAULT NOW()
);

CREATE TABLE users_info (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    user_id INTEGER,
    job VARCHAR(40),
    age INTEGER,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE blogs (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    user_id INTEGER,
    title VARCHAR(40) NOT NULL,
    body TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE comments (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    blog_id INTEGER,
    user_id INTEGER,
    body TEXT NOT NULL,
    FOREIGN KEY (blog_id) REFERENCES blogs(id),
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE tags (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    tag_name VARCHAR(30) UNIQUE NOT NULL
);

INSERT INTO tags (tag_name) VALUES
    ('Technology'),
    ('Travel'),
    ('Food'),
    ('Lifestyle'),
    ('Health'),
    ('Fitness'),
    ('Programming'),
    ('Fashion'),
    ('Science'),
    ('Photography'),
    ('Nature'),
    ('Art'),
    ('Music'),
    ('Books'),
    ('Movies'),
    ('Gaming'),
    ('DIY'),
    ('Finance'),
    ('Education'),
    ('Pets');

CREATE TABLE blogs_tags (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    tag_id INTEGER,
    blog_id INTEGER,
    FOREIGN KEY (blog_id) REFERENCES blogs(id),
    FOREIGN KEY (tag_id) REFERENCES tags(id)
);

/******************************************************** Triggers ********************************************************/

DELIMITER //
CREATE TRIGGER users_before_insert
BEFORE INSERT ON users
FOR EACH ROW
BEGIN
    IF LENGTH(NEW.username) < 4 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Minimum length for username is 4 characters';
    END IF;
END;
//
DELIMITER ;

DELIMITER //
CREATE TRIGGER before_blog_delete
BEFORE DELETE ON blogs
FOR EACH ROW
BEGIN
    DELETE FROM blogs_tags WHERE blog_id = OLD.id;
    DELETE FROM comments WHERE blog_id = OLD.id;
END;
//
DELIMITER ;
