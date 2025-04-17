<?php
header("Content-Type: application/json");
header("Access-Control-Allow-Origin: *");

$host = 'localhost';
$dbname = 'car_crud_db';
$username = 'root';
$password = '';

try {
    $db = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8", $username, $password);
} catch (PDOException $e) {
    echo json_encode(['error' => 'Tietokantavirhe: ' . $e->getMessage()]);
    exit;
}

$table = isset($_GET['table']) ? $_GET['table'] : 'car';
$method = $_SERVER['REQUEST_METHOD'];

switch ($method) {
    case 'GET':
        $stmt = $db->query("SELECT * FROM $table");
        echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
        break;

    case 'POST':
        $branch = $_POST['branch'] ?? '';
        $model = $_POST['model'] ?? '';
        $stmt = $db->prepare("INSERT INTO $table (branch, model) VALUES (?, ?)");
        $success = $stmt->execute([$branch, $model]);
        echo json_encode(['success' => $success]);
        break;

    case 'PUT':
        parse_str(file_get_contents("php://input"), $_PUT);
        $id = $_PUT['id'] ?? '';
        $branch = $_PUT['branch'] ?? '';
        $model = $_PUT['model'] ?? '';
        $stmt = $db->prepare("UPDATE $table SET branch=?, model=? WHERE id=?");
        $success = $stmt->execute([$branch, $model, $id]);
        echo json_encode(['success' => $success]);
        break;

    case 'DELETE':
        parse_str(file_get_contents("php://input"), $_DELETE);
        $id = $_DELETE['id'] ?? '';
        $stmt = $db->prepare("DELETE FROM $table WHERE id=?");
        $success = $stmt->execute([$id]);
        echo json_encode(['success' => $success]);
        break;

    default:
        echo json_encode(['error' => 'Tuntematon pyyntö']);
        break;
}
