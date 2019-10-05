//please fill in the code below in the google guage plugin field of Thingspeak

//html

<html>
  <head>

  <title>Google Gauge - ThingSpeak</title>

  %%PLUGIN_CSS%%
  %%PLUGIN_JAVASCRIPT%%

  </head>

  <body>
    <div id="container">
      <div id="inner">
        <div id="gauge_div"></div>
      </div>
    </div>
  </body>
</html>

//css

<style type="text/css">
  body { background-color: 	#FFFFFF; }
  #container { height: 100%; width: 100%; }
  #inner { }
  #gauge_div { margin: 0 auto; }
</style>


//js

<script type='text/javascript' src='https://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js'></script>
<script type='text/javascript' src='https://www.google.com/jsapi'></script>
<script type='text/javascript'>

  // set your channel id here
  var channel_id = 101657;
  // set your channel's read api key here if necessary
  var api_key = 'LBNMXSTUR5RRVDYO';
  // maximum value for the gauge
  var max_gauge_value = 1023;
  // name of the gauge
  var gauge_name = 'Temp';

  // global variables
  var chart, charts, data;

  // load the google gauge visualization
  google.load('visualization', '1', {packages:['gauge']});
  google.setOnLoadCallback(initChart);

  // display the data
  function displayData(point) {
    data.setValue(0, 0, gauge_name);
    data.setValue(0, 1, point);
    chart.draw(data, options);
  }

  // load the data
  function loadData() {
    // variable for the data point
    var p;

    // get the data from thingspeak
    $.getJSON('https://api.thingspeak.com/channels/' + channel_id + '/feed/last.json?api_key=' + api_key, function(data) {

      // get the data point
      p = data.field1;

      // if there is a data point display it
      if (p) {
        //  p = Math.round((p / max_gauge_value) * 100);
        displayData(p);
      }

    });
  }

  // initialize the chart
  function initChart() {

    data = new google.visualization.DataTable();
    data.addColumn('string', 'Label');
    data.addColumn('number', 'Value');
    data.addRows(1);

    chart = new google.visualization.Gauge(document.getElementById('gauge_div'));
   options = {
   width: 160, height: 160, min: 0, max: 40,
   majorTicks: [0, 10, 20, 30, 40], minorTicks: 10,
      
   greenFrom: 20,
   greenTo: 30,
   greenColor: "#00e600",    
   yellowFrom: 30,
   yellowTo: 35,
   yellowColor: "#ff751a",
   redFrom: 35,
   redTo: 40,
   redColor: "#FF0000"};
      
               
    loadData();

    // load new data every 15 seconds
    setInterval('loadData()', 15000);
  }

</script>

