<?php

require_once('../config.php');

//create a connection
$conn =new mysqli(DB_HOST, DB_USER, DB_PASS, DB_DB);

//check the connection
if($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if(!array_key_exists('sensor', $_GET)) {
    die("No Sensor-ID given");
}

$sensor = $conn->real_escape_string($_GET['sensor']);

$query = <<<SQL
    select IoT_MAC, from_unixtime(time) as time , temp, humidity 
    from tbl_data
    where IoT_MAC = "$sensor";
SQL;

$result = $conn->query($query);

if (!$result) {

    printf("Error message: %s\n", $conn->error);
    print "$query";
}
else{

    while ($row = $result->fetch_assoc()){
        printf("%s: %s°C %s%%<br/>\n", $row["time"], $row["temp"], $row["humidity"]);
    }
    $result->close();
}

$conn->close();
