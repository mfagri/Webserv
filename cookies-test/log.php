<?php 
	$myuname = "mmardi";
	$pass = "123456";
	if (isset($_POST['login'])) {
		$uname = $_POST['uname'];
		$passwd = $_POST['password'];
		if ($uname == $myuname and $passwd == $pass) {
			if (isset($_POST["remember"]))
				setcookie('uname', $uname);
			session_start();
			$_SESSION['uname'] = $uname;
			header("Location: welcome.php", true, 301);
		}
		else {

			echo "<h3>User Name or Password is Invalid.</h3><br><a href=\"login.html\">Try again</a>";
		}
	}
	else{
			header("Location: login.html", true, 301);
	}
?>