<?php
date_default_timezone_set('UTC');
try
{    // connection à la base de données
    // On se connecte à MySQL
    $bdd = new PDO('mysql:host=localhost;dbname=mesure', 'marcel1968', 'Marcel&3436');
}
catch(Exception $e)
{
    die('Erreur : '.$e->getMessage());  // En cas d'erreur, on affiche un message et on arrête tout
}
    
if (isset($_GET['M_distance1'])) // test si la variable existe
{
            
    $mesure = $_GET['M_distance1'];
    $detail = explode(",", $mesure);

    $mes = $detail[0];
    $dat1 = $detail[1];
    $dat2 = $detail[2];
    $dat = $dat1." ".$dat2;
//echo $mesure;exit;    
    $sql = "INSERT INTO Mesure_Table (M_distance,M_date) VALUES ('$mes','$dat')";
        
    if ($bdd->query($sql) === TRUE) {
        echo ('donnee mesure: ' .$mes. ' ecrite!');
        echo "<br>";
        echo ('donnée date: ' .$dat. 'écrite');
    }else{
	echo $mes;
	echo "<br>";
	echo $dat; 
    }
} else {
    echo "problème";
}
?>
