<?php
// here I use argv for URL, but you can adapt it however you like
$url = "/Users/mfagri/Desktop/gitwebserv/mfagri/send_post.php";
$data = array('var1' => 'value1', 'var2' => 'value2');

$options = array(
    'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($data)));

$response = file_get_contents($url, false, stream_context_create($options));

// you can echo the response if you're interrested, or just dump it
echo $response;
?>