<?php
function theseus_header($redirect_content)
{
?>
<html>
<head>
<meta http-equiv="refresh" content="<?php print $redirect_content; ?>">
<link rel="shortcut icon" href="images/favicon.ico" type="image/vnd.microsoft.icon">
<link rel=StyleSheet href="/style.css" type="text/css">
<title>THESEUS Remote Monitoring System</title>
</head>
<body>
<center><img src="images/banner.png" width="990" height="40" border="0" vspace="0" hspace="0"></center>
<?php
}

function theseus_footer()
{
?>
</body>
</html>
<?php
}


function show_archive($dbh, $date)
{
   theseus_header("10");
   echo "<CENTER><P><h2>Archive ($date)</h2><CENTER>";

   $stmt = $dbh->prepare("SELECT DISTINCT rx_id FROM rsci_recordings WHERE CAST(recording_start AS DATE) = ?");
   $stmt->setFetchMode(PDO::FETCH_ASSOC);
   $stmt->execute(array($date));
   $rxValues = $stmt->fetchAll();

   $numRxs = count($rxValues);

   $stmt = $dbh->prepare("SELECT recording_start, state, rx_id, filename FROM rsci_recordings WHERE CAST(recording_start AS DATE) = ?");
   $stmt->setFetchMode(PDO::FETCH_ASSOC);
   $stmt->execute(array($date));
   $timeValues = $stmt->fetchAll();

   echo "<table>";

   echo "<tr>";
   echo "<th>Start time</th><th COLSPAN=$numRxs>Receiver IDs</th>";
   echo "</tr>";

   echo "<tr>";
   echo "<td></td>";

   foreach($rxValues as $row) {
       $id = $row['rx_id'];
       echo "<td>$id</td>";
   }
   echo "</tr>";

   $numTimes = count($timeValues);

   sort($timeValues);

   $table = array();

   foreach($timeValues as $row) {
     $hour = substr($row["recording_start"], 11, 2);
     $min = substr($row["recording_start"], 14, 2);
     $time = "$hour:$min";
     $recDate = substr($row["recording_start"], 0, 10);

     $state = $row["state"];
     $id = $row["rx_id"];
     $fileName = $row["filename"];

     if (!isset($table[$time])) {
       $table[$time] = array();
     }
     
     $tdString = "";
     switch ($state) {
       case "R":
         $tdString = "<A title=\"click to request upload from receiver\""
		." href=\"day.php?action=request&amp;filename=$fileName&amp;date=$date\">"
		."<img src=\"images/requestFile.gif\"/></A>";
         break;
       case "Q":
         $tdString = "<span title=\"file has been requested\">Q</span>";
         break;
       case "A":
         $tdString = "<A title=\"click to listen\""
		." href=\"/rsci/$id/$recDate/$fileName\">"
		."<img src=\"images/listen_icon.gif\"/></A>";
         break;
     }

     $table[$time][$id] = $tdString;
   }

   foreach($table as $key => $value) {
     echo "<tr>";
     echo "<td>$key</td>";

     foreach($rxValues as $row) {
      $rxValuesId = $row["rx_id"];
       if ( isset($value[$rxValuesId]) ) {
         echo "<td>$value[$rxValuesId]</td>";
       } else {
         echo "<td></td>";
       }
     }

     echo "</tr>";
   }

   echo "</table>";
   theseus_footer();
}


/* Change the state of an entry in 'rsci_recordings' table of the theseus database from "Remote" to "reQuested" */
function request_file($dbh, $date, $fileName)
{
   theseus_header("0,day.php?date=$date");
    try {
	$stmt = $dbh->prepare("UPDATE rsci_recordings SET state='Q' WHERE filename=?"); 
	$stmt->execute(array($fileName));
    } catch (PDOException $e) {
        print "Error!: " . $e->getMessage() . "<br/>";
    }
   theseus_footer();
}

?>
