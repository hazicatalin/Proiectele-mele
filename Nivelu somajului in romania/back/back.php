<?php
// asta e micul serviciu
if ($_SERVER["REQUEST_METHOD"] != "GET"){ // testam daca metoda cu care a fost apelat este GET
    $response = [
        'status' => 'error',
        'message' => 'BAD_REQUEST'
    ];
    echo json_encode($response); // daca nu returnam un mesaj corespunzator
    http_response_code(400); /// si un cod de eroare
    die(); // si iesim
}


$ln = $_GET["luna"];
$filtru = $_GET["filtru"];
$jd = $_GET["judet"];
$value = $_GET["value"];
$array = array();
//$lun = array();
//$jud = array();

$jud = explode(";", $jd);
$lun = explode(";", $ln);
/*
if(is_array($ln))
	$lun=array_merge($lun,$ln);
else
	array_push($lun, $ln);
if(is_array($jd))
	$jud=array_merge($jud,$jd);
else
    {array_push($jud, $jd);}
  */  

    //array_push($jud, "NEAMT");
    //array_push($lun, "ianuarie");

foreach($lun as $luna) {
    foreach($jud as $judet){

        if($luna == null || $filtru == null || $judet == null || $value == null){ // verificam ca acestia sa nu fie nuli
            $response = [
                'status' => 'error',
                'message' => 'NULL_PARAMETERS'
            ];
            echo json_encode($response); // daca sunt nuli, transmitem un mesaj corespunzator
            http_response_code(400); // si un cod de eroare
            die(); // si iesim
        }

        // array cu toate judetele posibile
        $judete = ["TOTAL","ALBA", "ARAD", "ARGES", "BACAU", "BIHOR", "BISTRITA-NASAUD", "BOTOSANI", "BRASOV", "BRAILA", "BUCURESTI", "BUZAU", "CARAS-SEVERIN", "CALARASI", "CLUJ", "CONSTANTA", "COVASNA", "DAMBOVITA", "DOLJ", "GALATI", "GIURGIU", "GORJ", "HARGHITA", "HUNEDOARA", "IALOMITA", "IASI", "ILFOV", "MARAMURES", "MEHEDINTI", "MURES", "NEAMT", "OLT", "PRAHOVA", "SATU-MARE", "SALAJ", "SIBIU", "SUCEAVA", "TELEORMAN", "TIMIS", "TULCEA", "VASLUI", "VALCEA", "VRANCEA"];

        if(!in_array(strtoupper($judet),$judete)){ // vedem daca judetul transmis ca parametru este chiar un judet valid
            $response = [
                'status' => 'error',
                'message' => 'INVALID_JUDET'
            ];
            echo json_encode($response);// daca nu, aceeasi procedura ca mai sus
            http_response_code(404);
            die();
        }


        // la fel si in cazul lunilor
        $luni = ['ianuarie', 'februarie', 'martie', 'aprilie', 'mai', 'iunie', 'iulie', 'august', 'septembrie', 'octombrie', 'noiembrie', 'decembrie'];

        if(!in_array(strtolower($luna),$luni)){ // daca nu e o luna valida, semnalam acest lucru
            $response = [
                'status' => 'error',
                'message' => 'INVALID_LUNA'
            ];
            echo json_encode($response);
            http_response_code(404);
            die();
        }

        if(!is_numeric($value)){ // daca valoarea transmisa nu este numar, nu e ok
            $response = [
                'status' => 'error',
                'message' => 'VALUE_NOT_NUMERIC_PARAMETER'
            ];
            echo json_encode($response);
            http_response_code(404);
            die();
        }

        if($filtru == 'rata'){  // apoi verificam ca coloana selectata pentru fiecare filtru in parte, se poate accesa
            if($value > 2){ // pentru rata, in csv exista doar 8 coloane
                $response = [
                    'status' => 'error',
                    'message' => 'INVALID_VALUE'
                ];
                echo json_encode($response);
                http_response_code(404);
                die();
            }
        } else if($filtru == 'mediu'){ // facem acest lucru pentru fiecare filtru
            if($value > 4){
                $response = [
                    'status' => 'error',
                    'message' => 'INVALID_VALUE'
                ];
                echo json_encode($response);
                http_response_code(404);
                die();
            }
        } else if($filtru == 'varsta'){
            if($value > 7){
                $response = [
                    'status' => 'error',
                    'message' => 'INVALID_VALUE'
                ];
                echo json_encode($response);
                http_response_code(404);
                die();
            }
        } else if($filtru == 'studii'){
            if($value > 8){
                $response = [
                    'status' => 'error',
                    'message' => 'INVALID_VALUE'
                ];
                echo json_encode($response);
                http_response_code(404);
                die();
            }
        } else { // iar daca filtrul nu este printre cele de mai sus, iar nu e ok
            $response = [
                'status' => 'error',
                'message' => 'INVALID_FILTRU'
            ];
            echo json_encode($response);
            http_response_code(404);
            die();
        }

        /*
        //$judet = "\r\n".$judet; // adaugam in fata judetului un enter pentru a gasi valoarea in csv, el avand un enter in fata
        $judet = "\n".$judet; // pe host acest spatiu este doar \n, pe windows el este \r\n
        $path = "csv/".$luna."/".$filtru.".csv"; // selectam csv-ul de care avem nevoie printr-un path
        $csv = file_get_contents ($path); // luam datele din csv
        $data = str_getcsv($csv);

        foreach($data as $key => $val){ // il parcurgem 
            if(strcmp($val,$judet) == 0){ // si cand gasim judetul
                $csvValue = $data[$key + $value]; // selectam valoarea de care avem nevoie
                break; // si iesim
            }
        }
        */
        $CONFIG = [
            'servername' => "localhost",
            'username' => "root",
            'password' => '',
            'db' => 'somaj'
        ];

        $conn = new mysqli($CONFIG["servername"], $CONFIG["username"], $CONFIG["password"], $CONFIG["db"]);
        /*
            if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
            } else { 
            echo "Successfully connected to DB";
            }*/
            if(strcmp(strtolower($filtru),"rata") == 0){
                
                if(strcmp($judet,"TOTAL") == 0)
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}'");
                else
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}'");
            $getUsersStatement -> execute();
        
            $users = $getUsersStatement -> get_result();
            }
            else if(strcmp(strtolower($filtru),"mediu") == 0){
                if($value == 2)
                    {$med = 'rural';}
                else if($value == 3)
                    {$med = 'urban';}              
                if($value > 1){
                    if(strcmp($judet,"TOTAL") == 0)
                        $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}' and mediu = '{$med}'");
                    else    
                        $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}' and mediu = '{$med}'");
                    }
                else{            
                if(strcmp($judet,"TOTAL") == 0)
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}'");
                else 
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}'");
                }
            $getUsersStatement -> execute();
        
            $users = $getUsersStatement -> get_result();
        }
        else if(strcmp(strtolower($filtru),"varsta") == 0){
            if($value == 2)
            { $var = 'sub25';}
            if($value == 3)
                {$var = '25-29';}
            if($value == 4)
                {$var = '30-39';}
            if($value == 5)
                {$var = '40-49';}
            if($value == 6)
                {$var = '50-55';}
            if($value == 7)
                {$var = 'peste55';}
            if($value>1)
                { 
                    if(strcmp($judet,"TOTAL") == 0)
                        $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}' and varsta = '{$var}'");
                    else
                        $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}' and varsta = '{$var}'");
                }
            else
                { 
                    if(strcmp($judet,"TOTAL") == 0)
                        $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}'");
                    else
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}'");}
            $getUsersStatement -> execute();
        
            $users = $getUsersStatement -> get_result();
        }
        else if(strcmp($filtru,"studii") == 0)
        {
            if($value == 2)
            { $std = 'fara';}
            else
            if($value == 3)
            { $std = 'primar';}
            if($value == 4)
            { $std='gimnazial';}
            if($value == 5)
            { $std = 'liceal';}
            if($value == 6)
            {$std = 'postliceal';}
            if($value == 7)
            { $std = 'profesional';}
            if($value == 8)
                {$std = 'universitar';}
            if($value > 1)
            {
                if(strcmp($judet,"TOTAL") == 0)
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}' and studii = '{$std}'");
                else
                $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}' and studii = '{$std}'");}
            else 
            { 
                if(strcmp($judet,"TOTAL") == 0)
                    $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE luna = '{$luna}'");
                else
                $getUsersStatement = $conn -> prepare("SELECT sum(numar) FROM {$filtru} WHERE judet = '{$judet}' and luna = '{$luna}'");}
            $getUsersStatement -> execute();
        
            $users = $getUsersStatement -> get_result();
        }
        foreach($users as $row) {   
            $a = $row["sum(numar)"];
        }
        array_push($array, $a);
    }
}
    $abc = $array[0];
  //foreach($users as $row) {
    $response = [ // apoi returnam un raspuns de success adecvat
        'status' => 'success',
        'message' => $array
    ];
    echo json_encode($response);
  //}

http_response_code(200); // si cod de success
?>