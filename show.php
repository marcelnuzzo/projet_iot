<?php

try { 
   //$connect = new PDO('mysql:host=marcel1968.hopto.org/phpmyadmin/sql.php;dbname=mesure', 'marcel1968', 'Marcel&3436');
    $connect = new PDO('mysql:host=localhost;dbname=mesure','marcel1968','Marcel&3436');	
    $connect->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);

//    echo 'ok';

} catch (PDOException  $exc) {
    echo $exc->getMessage();
    die("NOP");
}

//echo "coucou";

$sql = "SELECT * FROM Mesure_Table";

$query = $connect->prepare($sql);

$query->execute();

//print("result_mesure");

$myarray = array();

while($res = $query->fetch()) {
	array_push($myarray, array(
	"id"      => $res['id'],
	"heading" => $res['M_distance'],
	"body"    => $res['M_date'],
	)
);
	

	
}
		echo json_encode($myarray);
?>
