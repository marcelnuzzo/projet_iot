<?php


try { 
    $connect = new PDO('mysql:host=http://marcel1968.hopto.org/phpmyadmin/sql.php;dbname=mesure', 'Marcel&3436', 'mesure');
    $connect ->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);

    echo 'ok';

} catch (PDOException  $exc) {
    echo $exc->getMessage();
    die("NOP");
}

?>