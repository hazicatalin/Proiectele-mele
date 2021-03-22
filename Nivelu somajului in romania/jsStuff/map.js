// array-uri cu toate id-urile si judetele de pe harta
var mapIds = ['pVS', 'pVN', 'pVL', 'pTR', 'pTM', 'pTL', 'pSV', 'pSM', 'pSJ', 'pSB', 'pPH', 'pOT', 'pNT', 'pMS', 'pMM', 'pMH', 'pIS', 'pIL', 'pIF', 'pHR', 'pHD', 'pGR', 'pGL', 'pGJ', 'pDJ', 'pDB', 'pCV', 'pCT', 'pCS', 'pCL', 'pCJ', 'pBZ', 'pBV', 'pBT', 'pBR', 'pBN', 'pBH', 'pBC', 'pAR', 'pAG', 'pAB'];
var judeteMapa = ['Vaslui', 'Vrancea', 'Valcea', 'Teleorman', 'Timis', 'Tulcea', 'Suceava', 'Satu-Mare', 'Salaj', 'Sibiu', 'Prahova', 'Olt', 'Neamt', 'Mures', 'Maramures', 'Mehedinti', 'Iasi', 'Ialomita', 'Ilfov', 'Harghita', 'Hunedoara', 'Giurgiu', 'Galati', 'Gorj', 'Dolj', 'Dambovita', 'Covasna', 'Constanta', 'Caras-Severin', 'Calarasi', 'Cluj', 'Buzau', 'Brasov', 'Botosani', 'Braila', 'Bistrita-Nasaud', 'Bihor', 'Bacau', 'Arad', 'Arges', 'Alba'];

// functie care atunci cand se face hover, se autosesizeaza si cere o valoare de la getMapValueByJudet
async function setMapValue(id) {
    document.getElementById(id).innerHTML = await getMapValueByJudet(judeteMapa[mapIds.indexOf(id)].toUpperCase());
}