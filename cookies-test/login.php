<?php
if(isset($_COOKIE['uname'])) {
	$myuname = "mmardi";
	if($myuname == $_COOKIE['uname']) {
		session_start();
		$_SESSION['uname'] = $_COOKIE['uname'];
		header("Location: welcome.php", true, 301);
	}
	
}
else {
		echo "<a href=\"login.html\">Log in</a>";
	}
?>