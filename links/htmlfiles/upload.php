<?php
$file = $_FILES["file"];

if (move_uploaded_file($file["tmp_name"], "/tmp/" .$file["name"]))
	echo "file uploaded";
else 
	echo "file not uploaded";

?>