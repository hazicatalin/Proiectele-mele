// functiic are ascund si activeza div-urile cu filtre, in functie de categoria de filtre selectata
function showDivJud() {
    document.getElementById('judete').style.display = "flex";

    document.getElementById('luni').style.display = "none";
    document.getElementById('varsta').style.display = "none";
    document.getElementById('mediu').style.display = "none";
    document.getElementById('studii').style.display = "none";
}
function showDivStudii() {
    if (document.getElementById('studii').style.display === "flex")
        document.getElementById('studii').style.display = "none";
    else
        document.getElementById('studii').style.display = "flex";

    document.getElementById('luni').style.display = "none";
    document.getElementById('varsta').style.display = "none";
    document.getElementById('mediu').style.display = "none";
    document.getElementById('judete').style.display = "none";
}
function showDivMediu() {
    if (document.getElementById('mediu').style.display === "flex")
        document.getElementById('mediu').style.display = "none";
    else
        document.getElementById('mediu').style.display = "flex";

    document.getElementById('luni').style.display = "none";
    document.getElementById('varsta').style.display = "none";
    document.getElementById('studii').style.display = "none";
    document.getElementById('judete').style.display = "none";
}
function showDivVarsta() {
    if (document.getElementById('varsta').style.display === "flex")
        document.getElementById('varsta').style.display = "none";
    else
        document.getElementById('varsta').style.display = "flex";

    document.getElementById('luni').style.display = "none";
    document.getElementById('mediu').style.display = "none";
    document.getElementById('studii').style.display = "none";
    document.getElementById('judete').style.display = "none";
}
function showDivLuni() {
    if (document.getElementById('luni').style.display === "flex")
        document.getElementById('luni').style.display = "none";
    else
        document.getElementById('luni').style.display = "flex";

    document.getElementById('varsta').style.display = "none";
    document.getElementById('mediu').style.display = "none";
    document.getElementById('studii').style.display = "none";
    document.getElementById('judete').style.display = "none";
}

// functii care afiseaza si ascund div-urile cu chart-uri in functie de chart-ul selectat (sau harta)
function showDivPie() {
    document.getElementById('mainPie').style.display = "block";

    document.getElementById('mainFirst').style.display = "none";
    document.getElementById('mainBar').style.display = "none";
    document.getElementById('mainLine').style.display = "none";
    document.getElementById('mainMap').style.display = "none";
}

function showDivBar() {
    document.getElementById('mainBar').style.display = "block";

    document.getElementById('mainFirst').style.display = "none";
    document.getElementById('mainPie').style.display = "none";
    document.getElementById('mainLine').style.display = "none";
    document.getElementById('mainMap').style.display = "none";
}

function showDivLine() {
    document.getElementById('mainLine').style.display = "block";

    document.getElementById('mainFirst').style.display = "none";
    document.getElementById('mainBar').style.display = "none";
    document.getElementById('mainPie').style.display = "none";
    document.getElementById('mainMap').style.display = "none";
}

function showDivMap() {
    document.getElementById('mainMap').style.display = "flex";

    document.getElementById('mainFirst').style.display = "none";
    document.getElementById('mainBar').style.display = "none";
    document.getElementById('mainPie').style.display = "none";
    document.getElementById('mainLine').style.display = "none";
}
