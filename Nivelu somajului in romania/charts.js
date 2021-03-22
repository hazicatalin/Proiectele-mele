var selectedChartToShow; // variabila care ne va spune de chart avem selectat ( ce chart vede utilizatorul )
function selectChart(numar) { // functie care creeaza chart-urile initial, iar apoi doar modifica datele de pe chart-uri cand este apelata
  selectedChartToShow = numar;
  if (numar === 0 && window.myPie === undefined) { // daca se vrea pie chart, creeam un pie
    document.getElementById('canvas').style.width = '100vw';
    var ctx = document.getElementById('chart-pie').getContext('2d');
    window.myPie = new Chart(ctx, pieChartData);
  } else if (numar === 1 && window.myLine === undefined) {
    document.getElementById('canvas-line').style.width = '90vw';
    var ctx = document.getElementById('chart-line').getContext('2d');
    window.myLine = new Chart(ctx, lineChartData);
  } else if (numar === 2 && window.myBar === undefined) {
    document.getElementById('canvas-bar').style.width = '90vw';
    var ctx = document.getElementById('chart-bar').getContext('2d');
    window.myBar = new Chart(ctx, barChartData);
  }
  modifyCharts(); // si modificam chart-urile
}

// array-uri care ne ajuta sa afisam diferite informatii
var luniAfisate = ['ian', 'feb', 'mar', 'apr', 'mai', 'iun', 'iul', 'aug', 'sept', 'oct', 'nov', 'dec'];
var luniSelectateAfisate = [];
var luni = ['ianuarie', 'februarie', 'martie', 'aprilie', 'mai', 'iunie', 'iulie', 'august', 'septembrie', 'octombrie', 'noiembrie', 'decembrie'];
var lun = "ianuarie;februarie;martie;aprilie;mai;iunie;iulie;august;septembrie;octombrie;noiembrie;decembrie";
var luniSelectate = [];
var ls="";
var judete = [];
var js="";
var metoda = "rata";
var index = 1;

function getSelectedChart() { // da chart-ul selectat
  return selectedChartToShow;
}

function fullMonthName(luna) { // transforma luna din format prescurtat in nume intreg
  switch (luna) {
    case 'ian':
      return "ianuarie";
    case 'feb':
      return "februarie";
    case 'mar':
      return "martie";
    case 'apr':
      return "aprilie";
    case 'mai':
      return "mai";
    case 'iun':
      return "iunie";
    case 'iul':
      return "iulie";
    case 'aug':
      return "august";
    case 'sept':
      return "septembrie";
    case 'oct':
      return "octombrie";
    case 'nov':
      return "noiembrie";
    case 'dec':
      return "decembrie";
  }
}

function getHeaders() { // intoarce in functie de caz, ce informatii afiseaza un chart (lunile, judetele)
  if (judete.length !== 0) {
    return judete;
  } else {
    if (luniSelectate.length === 0) {
      return luni;
    } else {
      return luniSelectate;
    }
  }
}

function getValues() { // intoarce valorile din chart
  return pieChartData.data.datasets[0].data;
}

function addOrRemoveMonth(luna) { // adauga sau sterge din array-uri o luna selectata, daca este o sterge, daca nu este o adauga
  var fullName = fullMonthName(luna);

  if (luniSelectateAfisate.includes(luna)) {
    luniSelectateAfisate.splice(luniSelectateAfisate.indexOf(luna), 1);
    luniSelectate.splice(luniSelectate.indexOf(fullName), 1);
    fullName = fullName.concat(";");
    ls = ls.replace(fullname, "");

  } else {
    luniSelectateAfisate.push(luna);
    luniSelectate.push(fullName);
    ls = ls.concat(fullName);
    ls=ls.concat(";");
  }
  modifyCharts(); // se face modificarea chart-urilor
}

function changeMetode(met, ind) { // schimba filtrul si index-ul, adica de ce date avem nevoie (mediu, rata, studiu, ani)
  if (metoda === met && index == ind) {
    metoda = "rata";
    index = 1;
  } else {
    metoda = met;
    index = ind;
  }
  modifyCharts();
}

function addJudet(judet) { // adauga un judet in array
  judete.push(judet);
  js = js.concat(judet);
  js = js.concat(";");
  modifyCharts();
}
function removeJudet(judet) { // scoate un judet din array
  judete.splice(judete.indexOf(judet), 1);
  judet = judet.concat(";");
  js = js.replace(judet, "");
  modifyCharts();
}
function destroyJudete() { // sterge tot de e in array-ul judete
  judete = [];
  modifyCharts();
}
function modifyDataCharts(data) { // adauga in datele chart-urile ultimele date modifcate
  pieChartData.data.datasets[0].data.push(data);
  lineChartData.data.datasets[0].data.push(data);
  barChartData.data.datasets[0].data.push(data);
}
function modifyLabelsCharts(value) { // modifica informatiile ce se afiseaza in chart-uri
  if (value == 1) {
    pieChartData.data.labels = luniAfisate;
    lineChartData.data.labels = luniAfisate;
    barChartData.data.labels = luniAfisate;
  } else if (value == 2) {
    pieChartData.data.labels = luniSelectateAfisate;
    lineChartData.data.labels = luniSelectateAfisate;
    barChartData.data.labels = luniSelectateAfisate;
  } else if (value == 3) {
    pieChartData.data.labels = judete;
    lineChartData.data.labels = judete;
    barChartData.data.labels = judete;
  }
}
async function modifyCharts() { // modifica datele si chart-urile 
  pieChartData.data.datasets[0].data = [];
  lineChartData.data.datasets[0].data = [];
  barChartData.data.datasets[0].data = [];
  if (luniSelectate.length === 0) { // daca nu avem luni selectate afisam toate lunile
    if (judete.length === 0) { // daca nu avem judete selectate ar trebui sa afiseze judete
      modifyLabelsCharts(1);
      var valoare = await getData(lun, 'TOTAL', metoda, index); // si pentru fiecare luna luam datele inregistrate
      for (var i = 0; i < luni.length; i++) { // parcurgem lunile 
        modifyDataCharts(parseInt(valoare[i]));
      }
    } else { // daca da, afisam judete
      modifyLabelsCharts(3);
      var aux = 0;
      var valoare = await getData(lun, js.substring(0, js.length - 1), metoda, index);
      for (var j = 0; j < judete.length; j++) {
        var suma = 0;
        for (var i = 0; i < luni.length; i++) {
          suma = suma + parseInt(valoare[aux]);
          aux = aux+1;
        }
        modifyDataCharts(suma);
      }
    }
  } else { // daca avem luni selectate, luam date doar din astea
    if (judete.length === 0) { // asta daca nu cumva avem judete selectate
      modifyLabelsCharts(2);
      var valoare = await getData(ls.substring(0, ls.length - 1), 'TOTAL', metoda, index);
      for (var i = 0; i < luniSelectate.length; i++) {
        modifyDataCharts(parseInt(valoare[i]));        
      }

    } else { //  daca avem judete selectate, afisam judetele
      modifyLabelsCharts(3);  

      var valoare = await getData(ls.substring(0, ls.length - 1), js.substring(0, js.length - 1), metoda, index);
      var aux = 0;
      for (var j = 0; j < judete.length; j++) {
        var suma = 0;
        for (var i = 0; i < luniSelectate.length; i++) {
          suma = suma + parseInt(valoare[aux]);
          aux = aux+1;
        }
        modifyDataCharts(suma);
      }
    }
  }


  if (window.myPie !== undefined) // facem update la fiecare chart
    window.myPie.update();
  if (window.myLine !== undefined)
    window.myLine.update();
  if (window.myBar !== undefined)
    window.myBar.update();
}

async function getMapValueByJudet(judet) { // functia pe care o folosim la afisarea cartografica
  // pentru judetul pe care facem hover, o sa returneze datele adunate din toate cele 12 luni, tinand cont si de filtre
  var suma = 0;
  if (luniSelectate.length === 0) {
    var valoare = await getData(lun, judet, metoda, index);
    for (var i = 0; i < luni.length; i++) {
      suma = suma + parseInt(valoare[i]);
    }
  } else {
    var valoare = await getData(ls.substring(0, ls.length - 1), judet, metoda, index);
    for (var i = 0; i < luniSelectate.length; i++) {
      suma = suma + parseInt(valoare[i]);
    }
  }
  return suma;
}

var getData = async function (luna, judet, filtru, data) { // face apel la serviciu si ia datele pentru o luna, un judet si un filtru
  const url = 'back/back.php?luna=' + luna + '&judet=' + judet + '&filtru=' + filtru + '&value=' + data;
  response = await fetch(url);
  return (await response.json())['message'];
};


var pieChartData = { // definim datele necesare pentru contruirea unui pieChart 
  type: 'pie',
  data: {
    datasets: [{
      data: null,
      backgroundColor: [
        'rgb(50, 255, 255)',
        'rgb(255, 250, 150)',
        'rgb(255, 100, 50)',
        'rgb(255, 50, 0)',
        'rgb(200, 250, 200)',
        'rgb(200, 150, 50)',
        'rgb(200, 100, 0)',
        'rgb(100, 250, 100)',
        'rgb(100, 200, 50)',
        'rgb(100, 100, 0)',
        'rgb(50, 250, 100)',
        'rgb(50, 150, 150)'
      ],
      label: 'Dataset 1'
    }],
    labels: null
  },
  options: {
    responsive: true,
    fullWidth: true,
    legend: {
      labels: {
        fontColor: 'black',
        fontSize: 10
      }
    }
  }
};


var lineChartData = { // si a unui lineChart
  type: 'line',
  data: {
    labels: null,
    datasets: [{
      label: 'Somajul',
      backgroundColor: 'red',
      borderColor: 'red',
      data: null,
      fill: false,
    }]
  },
  options: {
    responsive: true,
    tooltips: {
      mode: 'index',
      intersect: false,
    },
    hover: {
      mode: 'nearest',
      intersect: true
    },
    scales: {
      x: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Month',
          fontSize: 10
        }
      },
      y: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Value',
          fontSize: 10
        }
      }
    },
    fullWidth: true,
    legend: {
      labels: {
        fontColor: 'black',
        fontSize: 10
      }
    }
  }
};

var barChartData = { // si a unui barChart
  type: 'bar',
  data: {
    labels: null,
    datasets: [{
      label: 'Somajul',
      backgroundColor: 'rgb(79, 83, 22)',
      borderColor: 'rgb(79, 83, 22)',
      borderWidth: 1,
      data: null
    }]
  },
  options: {
    responsive: true,
    legend: {
      position: 'top',
      fontSize: 10
    },
  }
};