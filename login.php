<?php
	$username = "root";
	$password = "ello3747";
	$hostname = "localhost";

	$dbhandle = mysql_connect($hostname, $username, $password) or die("could not connect");
	
	$selected = mysql_select_db("stringtaskmanagement", $dbhandle);

	$myusername = $_POST['user'];
	$mypassword = $_POST['pass'];

	$myusername = stripslashes($myusername);
	$mypassword = stripslashes($mypassword);

	$query = "SELECT * FROM admintable WHERE username = '$myusername' AND password = '$mypassword'";
	$result = mysql_query($query);
	$count = mysql_num_rows($result);

	mysql_close();	

	if($count==1){
	   $seconds = 120 + time();
	   setcookie()loggedin, date("F jS - g:i a"), $seconds);
	   header("location:admin.php");
	}else{
	   echo 'Incorrect username or password';
	}
?>
