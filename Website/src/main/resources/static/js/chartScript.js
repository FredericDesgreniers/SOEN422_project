window.onload = function () {



  var dps = []; // dataPoints
  var chart = new CanvasJS.Chart("chartContainer", {
    title :{
      text: "Force applied"
    },
    axisY: {
      includeZero: false
    },
    data: [{
      type: "line",
      dataPoints: dps
    }]
  });

  var dataLength = 20; // number of dataPoints visible at any point




    var socket = new SockJS("/guide");
    stompClient = Stomp.over(socket);
    stompClient.connect({}, function (frame) {
        console.log("Connected");
        stompClient.subscribe('/data/sub', function (message){
            var dataToShow = JSON.parse(message.body);
            dps.push({
                x: dataToShow.time,
                y: dataToShow.force
            });
            if (dps.length > dataLength) {
                dps.shift();
            }
            chart.render();
        });

    });


}