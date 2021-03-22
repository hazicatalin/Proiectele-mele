function downloadCSV() { // se realizeaza download-ul in format CSV
    const rows = [
        getHeaders(),
        getValues()
    ]; // si iau informatiile din chart-uri
    if (rows[1] !== null) { // daca avem informatii in chart-uri
        let csvContent = "data:text/csv;charset=utf-8,";

        rows.forEach(function (rowArray) { // le parcurgem
            let row = rowArray.join(",");
            csvContent += row + "\r\n"; // si creeam un string in format csv
        });


        var encodedUri = encodeURI(csvContent); // apoi punem informatiile intr-un fisier, si il descarcam
        var link = document.createElement("a");
        link.setAttribute("href", encodedUri);
        link.setAttribute("download", "csvData.csv");
        document.body.appendChild(link);

        link.click();
    }
}
function downloadXML() { // descarcarea in format XML
    // semana cu cea in CSV
    const data = getHeaders();
    const data1 = getValues();
    if (data1 != null) {
        const toXml = (data, data1) => {
            var result = '<?xml version="1.0" encoding="UTF-8"?> \n<valori> \n';
            for (var i = 0; i < data.length; i++) { // doar ca aici creem un string in format XML
                result = result + `\t <${data[i]}><value>${data1[i]}</value></${data[i]}>\n`
            }
            return result + '</valori>';
        }

        var xmltext = toXml(data, data1);

        var filename = "xmlData.xml";
        var pom = document.createElement('a');
        var bb = new Blob([xmltext], { type: 'text/plain' });

        pom.setAttribute('href', window.URL.createObjectURL(bb));
        pom.setAttribute('download', filename);

        pom.dataset.downloadurl = ['text/plain', pom.download, pom.href].join(':');
        pom.draggable = true;
        pom.classList.add('dragout');

        pom.click();
    }
}
function downloadPDF() { // pentru PDF am folosit jsPDF
    const data = getHeaders();
    const data1 = getValues();
    if (data1 != null) {
        var doc = new jsPDF();
        var specialElementHandlers = {
            '#bypassme': function (element, renderer) {
                return true;
            }
        };
        var margin = {
            top: 0,
            left: 0,
            right: 0,
            bottom: 0
        };

        var source = "";
        for (var i = 0; i < data.length; i++) {
            source = source + "<p>" + data[i] + " : " + data1[i] + "</p><br/>"; // creeam un string corespunzator
        }
        doc.fromHTML(source, 50, 50, {
            'width': 100,
            'elementHandlers': specialElementHandlers
        },
            function (bla) { doc.save('pdfData.pdf'); }, // si descarcam pdf-ul folosind magia jsPDF
            margin);
    }
}
function tweakLib() { // functie adaugata pentru canvas2svg pentru a putea transforma chart-ul in svg
    C2S.prototype.getContext = function (contextId) {
        if (contextId == "2d" || contextId == "2D") {
            return this;
        }
        return null;
    }

    C2S.prototype.style = function () {
        return this.__canvas.style
    }

    C2S.prototype.getAttribute = function (name) {
        return this[name];
    }

    C2S.prototype.addEventListener = function (type, listener, eventListenerOptions) {
        console.log("canvas2svg.addEventListener() not implemented.")
    }
}

function downloadSVG() { // pentru SVG am folosit canvas2svg 
    var selectedChart = getSelectedChart(); // luam chart-ul selectat
    if (selectedChart !== undefined) {
        var chartType;
        var context;
        var W = 500;
        var H = 500;
        if (selectedChart === 0) {
            chartType = pieChartData;
            context = document.getElementById("chart-pie").getContext("2d");
        } else if (selectedChart === 1) {
            chartType = lineChartData;
            context = document.getElementById("chart-line").getContext("2d");
            H = 700;
        } else if (selectedChart === 2) {
            chartType = barChartData;
            context = document.getElementById("chart-bar").getContext("2d");
            H = 700;
        }
        // si practic se deseneaza iar un chart in format svg folosind canvas2svg
        if (chartType !== undefined && context != undefined) {
            var chart = new Chart(context, chartType);

            tweakLib();
            chartType.options.responsive = false;
            chartType.options.animation = false;

            var svgContext = C2S(H, W);
            var mySvg = new Chart(svgContext, chartType);

            var bb = new Blob([svgContext.getSerializedSvg(true)], { type: 'text/plain' });

            var filename = "svgData.svg";
            var pom = document.createElement('a');
            pom.setAttribute('href', window.URL.createObjectURL(bb));
            pom.setAttribute('download', filename);

            pom.dataset.downloadurl = ['text/plain', pom.download, pom.href].join(':');
            pom.draggable = true;
            pom.classList.add('dragout');

            pom.click();
        }
    }
}
