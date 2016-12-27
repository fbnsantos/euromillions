<html>
 <head> 

  <title>PHP Test</title>
 </head>
 <body>
 <form>
 
<input type="submit" name="stop" value="STOP" />
<br />
<input type="submit" name="run" value="RUN" />
<br />
<input type="submit" name="null" value="reload" />
</form>
<?php


function startMyScript(){

    exec('nohup  sh run.sh > report.txt 2>&1 &  ');
}

if( isset( $_REQUEST['run'] )){
    echo '<p>Configured to RUN</p>';
    $myfile = fopen("status.txt", "w") or die("Unable to open file!");
    $txt = "run\n";
    fwrite($myfile, $txt);
    $txt = "Jane Doe\n";
    fwrite($myfile, $txt);
    fclose($myfile);
    startMyScript();
    header("Location: http://fbnsantos.duckdns.org/editor/workspace/Euromillions/");
}else if( isset( $_REQUEST['stop'] )){
    echo '<p>Configured to STOP</p>';
    $myfile = fopen("status.txt", "w") or die("Unable to open file!");
    $txt = "stop\n";
    fwrite($myfile, $txt);
    $txt = "Jane Doe\n";
    fwrite($myfile, $txt);
    fclose($myfile);
    header("Location: http://fbnsantos.duckdns.org/editor/workspace/Euromillions/");
   die();
}else{
	header("Refresh:40");	
}

echo "</br></br></br> "

?>

<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h1.html" height="400" width="1000"></iframe>
</br>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h2.html" height="400" width="1000"></iframe>

<?php



echo "</br></br></br>";
readfile("report_file.html");
echo "</br></br></br>";
readfile("report.txt");

echo "</br></br></br> "
?>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h3.html" height="400" width="1000"></iframe>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h4.html" height="400" width="1000"></iframe>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h5.html" height="400" width="1000"></iframe>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h6.html" height="400" width="1000"></iframe>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h7.html" height="400" width="1000"></iframe>
<iframe src="http://fbnsantos.duckdns.org/editor/workspace/Euromillions/report_file_h8.html" height="400" width="1000"></iframe>


</body>
</html>