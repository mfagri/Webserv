<?php 
    session_start();
    echo "welcome " . $_SESSION['uname'];
    echo "<br><a href=\"logout.php\">Log Out</a>"
?>