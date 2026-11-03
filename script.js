let username = "Clemencerlln";
let activeKey = "aio_XlWC36lqfVYpL8zvZZ89fTq7RS7t";

const IO = new AdafruitIO(username, activeKey);

IO.setLimit(1);

// on cible les éléments HTML
let humidity    =   document.querySelector("#humidity");
let temperature =   document.querySelector("#temperature");



// on met en place un intervalle de temps pour récupérer les données toutes les 10 secondes sans avoir a refresh la page à chaque fois 
setInterval(function(){

    IO.getData("temperature", function(data) {
        let cTemp = parseInt(data.json[0].value);
    temperature.innerHTML = `${cTemp} °C`; 

    });
    IO.getData("humidity", function(data) {
    console.log(data.json[0].value);
    let humidityValue = parseInt(map(
                data.json[0].value, 
                0, 
                1540, 
                0, 
                100));
    humidity.innerHTML = `${humidityValue} %`;
    });

}, 10000)



const map = (v, vMin, vMax, dMin, dMax) => {
    return (v - vMin) * (dMax - dMin) / (vMax - vMin) + dMin;
}