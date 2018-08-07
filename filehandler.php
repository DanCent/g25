<?php
$db_host = 'localhost'; // Server Name
$db_user = 'root'; // Username
$db_pass = 'ello3747'; // Password
$db_name = 'STM_G25'; // Database Name

$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
if (!$conn) {
	die ('Failed to connect to MySQL: ' . mysqli_connect_error());
}

  $file = fopen("ready.dat","r");

while(!feof($file)){

	$content = fgets($file);
	$carray = explode("\t",$content);
	list($TaskType,$job,$Date,$Time,$UserId) = $carray;
	$sql = mysqli_query($conn,"INSERT INTO `reading` (`TYPE`,`COMPLETED_TASKS`,`DATE`,`TIME`,`PROCESSING_DURATION`,`USER_ID`) VALUES ('$TaskType','$job','$Date','$Time','$processingTime','$UserId')");


}
echo "connection successful";
   
        fclose($file);
remove(ready.dat);

?>






