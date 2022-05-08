<?php

require_once('../config.php');

//create a connection
$conn =new mysqli(DB_HOST, DB_USER, DB_PASS, DB_DB);

//check the connection
if($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

//check if key exists in array (url from _GET)
if(!array_key_exists('sensor', $_GET)) {
    die("No Sensor-ID given");
}

if(!array_key_exists('temp', $_GET)) {
    die("No Sensor-Temperature given");
}

if(!array_key_exists('humid', $_GET)) {
    die("No Sensor-Humidity given");
}


//
$sensorID = $conn->real_escape_string($_GET['sensor']);
$sensorTemp = $conn->real_escape_string($_GET['temp']);
$sensorHumid = $conn->real_escape_string($_GET['humid']);

$query = <<<SQL
    insert into tbl_data (IoT_MAC, temp, humidity)
    value ('$sensorID', $sensorTemp, $sensorHumid);
SQL;

$result = $conn->query($query);

if (!$result) {
    printf("Error message: %s\n", $conn->error);
    print "$query";
}

else{
    print "Success";
}

$conn->close();