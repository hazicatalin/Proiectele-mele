function disappear(judet) { // da mai departe judetul sa fie sters din chart,  si sterge si judetul de pe ecran
    removeJudet(judet.toUpperCase());
    document.getElementById(judet).style.display = "none";
}

function showJud(judet) { // afiseaza sau ascunde (dupa caz) un judet
    if (document.getElementById(judet).style.display === "block") {
        disappear(judet);
    }
    else {
        document.getElementById(judet).style.display = "block";
        addJudet(judet.toUpperCase());
    }
}

function dissactivate(element) { // face un buton sa fie de culoare normala
    document.getElementById(element).style.background = "wheat";
}

function disappearAll() { // sterge toate judetele
    var judete = ["Alba", "Arad", "Arges", "Bacau", "Bihor", "Bistrita-Nasaud", "Botosani", "Brasov", "Braila", "Bucuresti", "Buzau", "Caras-Severin", "Calarasi", "Cluj", "Constanta", "Covasna", "Dambovita", "Dolj", "Galati", "Giurgiu", "Gorj", "Harghita", "Hunedoara", "Ialomita", "Iasi", "Ilfov", "Maramures", "Mehedinti", "Mures", "Neamt", "Olt", "Prahova", "Satu-Mare", "Salaj", "Sibiu", "Suceava", "Teleorman", "Timis", "Tulcea", "Vaslui", "Valcea", "Vrancea"];
    for (var i = 0; i < judete.length; i++) {
        document.getElementById(judete[i]).style.display = "none";
    }
    document.getElementById('judete').style.display = "none";
    destroyJudete();
}
function changeColorMonth(id) { // seteaza ori culoarea normala, ori un rosu, pentru a marca sa un buton este selectat (pentru luni)
    if (document.getElementById(id).style.background === "red")
        document.getElementById(id).style.background = "wheat";
    else
        document.getElementById(id).style.background = "red";

    addOrRemoveMonth(id);
}

function changeColor(id) { // schimba culoarea celorlalte filtre in functie de ce s-a selectat (mediu, studii, ani)
    var elemente = ['faraS', 'primar', 'gimnazial', 'liceal', 'postliceal', 'profesional', 'universitar', 'rural', 'urban', 'ani25', 'ani2529', 'ani30', 'ani40', 'ani50', 'ani55'];
    var studii = ['faraS', 'primar', 'gimnazial', 'liceal', 'postliceal', 'profesional', 'universitar'];
    var mediu = ['rural', 'urban'];
    var ani = ['ani25', 'ani2529', 'ani30', 'ani40', 'ani50', 'ani55'];

    for (var i = 0; i < elemente.length; i++) {
        if (elemente[i] === id) {
            if (document.getElementById(id).style.background === "red")
                document.getElementById(id).style.background = "wheat";
            else
                document.getElementById(id).style.background = "red";
        } else {
            dissactivate(elemente[i]);
        }
    }

    if (studii.includes(id)) {
        if (id === 'faraS') {
            changeMetode('studii', 2);
        } else if (id === 'primar') {
            changeMetode('studii', 3);
        } else if (id === 'gimnazial') {
            changeMetode('studii', 4);
        } else if (id === 'liceal') {
            changeMetode('studii', 5);
        } else if (id === 'postliceal') {
            changeMetode('studii', 6);
        } else if (id === 'profesional') {
            changeMetode('studii', 7);
        } else if (id === 'universitar') {
            changeMetode('studii', 8);
        }
    } else if (mediu.includes(id)) {
        if (id === 'rural') {
            changeMetode('mediu', 2);
        } else if (id === 'urban') {
            changeMetode('mediu', 3);
        }
    } else if (ani.includes(id)) {
        if (id === 'ani25') {
            changeMetode('varsta', 2);
        } else if (id === 'ani2529') {
            changeMetode('varsta', 3);
        } else if (id === 'ani30') {
            changeMetode('varsta', 4);
        } else if (id === 'ani40') {
            changeMetode('varsta', 5);
        } else if (id === 'ani50') {
            changeMetode('varsta', 6);
        } else if (id === 'ani55') {
            changeMetode('varsta', 7);
        }
    }
}

window.onclick = function (event) { // se activeaza dropdown-ul
    if (!event.target.matches('.dropbtn')) {
        document.getElementById("myDropdown").style.display = "none";
    }
}

function myFunction() { // asculde sau afiseaza dropdown-ul
    if (document.getElementById("myDropdown").style.display === "block")
        document.getElementById("myDropdown").style.display = "none";
    else
        document.getElementById("myDropdown").style.display = "block";
}

function filterFunction() { // functia care filtreaza rezultatele de la dropdown, in funtie de text-ul introdus 
    var input, filter, ul, li, a, i;
    input = document.getElementById("myInput");
    filter = input.value.toUpperCase();
    div = document.getElementById("myDropdown");
    a = div.getElementsByTagName("button");
    for (i = 0; i < a.length; i++) {
        txtValue = a[i].textContent || a[i].innerText;
        if (txtValue.toUpperCase().indexOf(filter) > -1) {
            a[i].style.display = "";
        } else {
            a[i].style.display = "none";
        }
    }
}