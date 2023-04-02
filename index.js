function demoKnob1() {
    // Create knob element, 300 x 300 px in size.
    const knob = pureknob.createKnob(300, 300);

    // Set properties.
    knob.setProperty('angleStart', -0.75 * Math.PI);
    knob.setProperty('angleEnd', 0.75 * Math.PI);
    knob.setProperty('colorFG', '#88ff88');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', 0);
    knob.setProperty('valMax', 100);

    function getData1()
    {
        var api_key = "04JO9LMXGEQYNGJG";
        var url = "https://api.thingspeak.com/channels/2052369/fields/1/last.json?api_key=" + api_key;

        // Replace CHANNEL_ID and FIELD_NUMBER with your own values

        $.getJSON(url, function(data) {
        var temperature = data.field1;
        knob.setValue(temperature);
        if(temperature => 33 && temperature <= 25)
            {
                tempStatus.innerHTML="Temperature Status : Normal  ✅"
                tempStatus.style.color="green";
            }
            if(temperature < 25)
            {
                tempStatus.innerHTML="Temperature Status : Low ❌"
                tempStatus.style.color="yellow";
            }
            if(temperature > 33)
            {
                tempStatus.innerHTML="Temperature Status : High ❌"
                tempStatus.style.color="red";
            }
        // Code to display the temperature data in the gauge
        });
    }

    setInterval(getData1,1000)

    // Set initial value.
    const listener = function(knob, value) {
        console.log(value);
    };

    knob.addListener(listener);

    // Create element node.
    const node = knob.node();

    // Add it to the DOM.
    const elem = document.getElementById('temp');
    elem.appendChild(node);
}


function demoKnob2() {
    // Create knob element, 300 x 300 px in size.
    const knob = pureknob.createKnob(300, 300);

    // Set properties.
    knob.setProperty('angleStart', -0.75 * Math.PI);
    knob.setProperty('angleEnd', 0.75 * Math.PI);
    knob.setProperty('colorFG', 'cyan');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', 0);
    knob.setProperty('valMax', 300);

    function getData2()
    {
        var api_key = "04JO9LMXGEQYNGJG";
        var url = "https://api.thingspeak.com/channels/2052369/fields/2/last.json?api_key=" + api_key;

        // Replace CHANNEL_ID and FIELD_NUMBER with your own values

        $.getJSON(url, function(data) {
        var bpm = data.field2;
        console.log(bpm)
        knob.setValue(bpm);
        bpmStatus=document.getElementById('bpmStatus');
        if(bpm => 57 && bpm <= 105)
            {
                bpmStatus.innerHTML="BPM Status : Normal ✅"
                bpmStatus.style.color="green";
            }
            if(bpm < 57)
            {
                bpmStatus.innerHTML="BPM Status : Low ❌"
                bpmStatus.style.color="yellow";
            }
            if(bpm > 105)
            {
                bpmStatus.innerHTML="BPM Status : High ❌"
                bpmStatus.style.color="red";
            }
        
        
        // Code to display the temperature data in the gauge
        });

    }

    setInterval(getData2,1000)

    
    // Set initial value.
    const listener = function(knob, value) {
        console.log(value);
    };

    knob.addListener(listener);

    // Create element node.
    const node = knob.node();

    // Add it to the DOM.
    const elem = document.getElementById('bpm');
    elem.appendChild(node);
}


function demoKnob3() {
    // Create knob element, 300 x 300 px in size.
    const knob = pureknob.createKnob(300, 300);

    // Set properties.
    knob.setProperty('angleStart', -0.75 * Math.PI);
    knob.setProperty('angleEnd', 0.75 * Math.PI);
    knob.setProperty('colorFG', 'pink');
    knob.setProperty('label', '');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', 0);
    knob.setProperty('valMax', 100);

    function getData3()
    {
        var api_key = "04JO9LMXGEQYNGJG";
    var url = "https://api.thingspeak.com/channels/2052369/fields/3/last.json?api_key=" + api_key;

    // Replace CHANNEL_ID and FIELD_NUMBER with your own values

    $.getJSON(url, function(data) {
    var oxi=data.field3;
    knob.setValue(oxi);
    oxiStatus=document.getElementById('oxiStatus');
        if(oxi =>85)
            {
                oxiStatus.innerHTML="SPo2 Status : Normal ✅"
                oxiStatus.style.color="green";
            }
            if(oxi < 85)
            {
                oxiStatus.innerHTML="Spo2 Status : Low ❌"
                bpmStatus.style.color="red";
            }
    
    
    // Code to display the temperature data in the gauge
    });

    }

    setInterval(getData3,1000)
    

    // Set initial value.
    const listener = function(knob, value) {
        console.log(value);
    };

    knob.addListener(listener);

    // Create element node.
    const node = knob.node();

    // Add it to the DOM.
    const elem = document.getElementById('oxi');
    elem.appendChild(node);

}

function ready() {
    /*setInterval("showTime()", 1000);*/
    demoKnob1();
    demoKnob2();
    demoKnob3();
}

document.addEventListener('DOMContentLoaded', ready, false);

function sendMail() {
    event.preventDefault();
    var formData = {
        name: document.getElementById('name').value,
        email: document.getElementById('email').value,
        message: document.getElementById('message').value
      };
    
      emailjs.send("service_kf7dtjy","template_gvo8jm6",{
        from_name: "Health Buddy",
        to_name: formData.name,
        message: formData.message,
        to_mail: formData.email
        }).then(function(response) {
          console.log('SUCCESS!', response.status, response.text);
          alert('Mail sent successfully')
        }, function(error) {
          console.log('FAILED...', error);
          alert('Failed')
        });
  
  }
