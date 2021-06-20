<?php
try
{    // connection à la base de données
    // On se connecte à MySQL
    $bdd = new PDO('mysql:host=localhost;dbname=mesure', 'marcel1968', 'Marcel&3436');
}
catch(Exception $e)
{
    die('Erreur : '.$e->getMessage());  // En cas d'erreur, on affiche un message et on arrête tout
}


if (isset($_GET['id'])) {
    $id = $_GET['id'];
    $sql = "DELETE FROM Mesure_Table WHERE id=$id";
    if ($bdd->query($sql) === TRUE) {
        echo "Record deleted successfully";
    } 
}
?>