<!DOCTYPE html>
<html>
<body>

<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
  Name: <input type="text" name="fname">
  <input type="submit">
</form>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // collect value of input field
    // fscanf(STDIN, "%s", $s);
    // echo 'hiii '; echo $s;
    $name = $_POST['fname'];
    if (empty($name)) {
        echo "Name is empty";
    } else {
        echo $name;
        if (isset($_COOKIE["name"]))
            echo "ck fnd";
    }
}
?>

</body>
</html>