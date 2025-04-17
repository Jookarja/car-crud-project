CREATE DATABASE IF NOT EXISTS car_crud_db;
USE car_crud_db;

CREATE TABLE IF NOT EXISTS car (
    id INT AUTO_INCREMENT PRIMARY KEY,
    branch VARCHAR(100) NOT NULL,
    model VARCHAR(100) NOT NULL
);

INSERT INTO car (branch, model) VALUES
('Toyota', 'Corolla'),
('Volkswagen', 'Golf'),
('Ford', 'Focus'),
('Honda', 'Civic'),
('Tesla', 'Model 3');
