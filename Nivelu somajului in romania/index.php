<?php
// router-ul
$request = $_SERVER['REQUEST_URI']; // se ia URL-ul

$splitedRequest = explode('/', $request); // retinem aici URL-ul spart in bucati dupa /

$styles = scandir(__DIR__ .'/front/style'); // luam in variabila styles denumira tuturor fisierele de style pe care le avem
$scripts = scandir(__DIR__ .'/jsStuff'); // luam in scripts denumira tuturor fisierele javascript pe care le avem
$pictures = scandir(__DIR__ .'/front/pics'); // luam in scripts styles denumira tuturor imaginilor pe care le avem

switch ($request) { // in functie de request
    case '/' : // daca este doar / mergem la pagina principala
        require __DIR__ . '/front/index.html';
        break;
    case '' :// daca este gol, la fel, mergem la pagina principala
        require __DIR__ . '/front/index.html';
        break;
    case '/main.html' :// daca se cere main.html, ii dam main.html
        require __DIR__ . '/front/main.html';
        break;
    case '/scholary.html' : // la fel si la scholary
        require __DIR__ . '/front/scholary.html';
        break;
    default: // iar daca nu e unul de mai sus
        switch ($splitedRequest[1]) { // facem un alt switch, sa vedem ce se vrea
            case 'style' : // daca se vrea style
                if(in_array($splitedRequest[2],$styles)){ // si exista foia de stiluri care se vrea
                    header('Content-type: text/css');
                    require __DIR__ .'/front/'.$splitedRequest[1].'/'.$splitedRequest[2]; // o dam
                    break;
                } else{ // daca nu, eroare
                    http_response_code(404);
                    require __DIR__ . '/front/errors.html';
                    break;
                }
                break;
            case 'pics' : // daca se vor imagini, la fel
                if(in_array($splitedRequest[2],$pictures)){
                    header('Content-type: image/png');
                    require __DIR__ .'/front/'.$splitedRequest[1].'/'.$splitedRequest[2];
                    break;
                } else{
                    http_response_code(404);
                    require __DIR__ . '/front/errors.html';
                    break;
                }
                break;
            case 'jsStuff' : // daca se vrea javascript, pai ii dam javascript (daca se poate)
                if(in_array($splitedRequest[2],$scripts)){
                    header('Content-type: application/javascript');
                    require __DIR__ .'/front/'.$splitedRequest[1].'/'.$splitedRequest[2];
                    break;
                } else{
                    http_response_code(404);
                    require __DIR__ . '/front/errors.html';
                    break;
                }
                break;
            default: // daca nu are nici macar o categorie -> eroare
                http_response_code(404);
                require __DIR__ . '/front/errors.html';
                break;
        }
}