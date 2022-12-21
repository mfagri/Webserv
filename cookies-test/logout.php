<?php
if (isset($_COOKIE['uname'])) {
    unset($_COOKIE['uname']);
    setcookie('uname', '', time() - 3600, '/'); // empty value and old timestamp
}
echo "<a href=\"login.html\">Log in</a>";
?>