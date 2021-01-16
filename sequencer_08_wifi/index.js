const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function () {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

function wsSendVal(category, key, val, option = '') {
    fnKey = String(key).padStart(2, '0');
    const valStr = String(Math.abs(val)).padStart(4, '0');
    const sign = val < 0 ? '-' : '+';
    const msg = `${category}${fnKey}${sign}${valStr}${option}`;
    console.log('msg:', msg);
    ws.send(msg);
}

Array.prototype.slice
    .call(document.querySelectorAll('button.base-ctrl'))
    .map(el => {
        el.onclick = () => {
            const { val, key } = el.dataset;
            wsSendVal('#', key, val);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('input.base-ctrl'))
    .map(el => {
        el.onchange = () => {
            const { key } = el.dataset;
            wsSendVal('#', key, el.value);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('input.note-set'))
    .map(el => {
        el.onchange = () => {
            const { option } = el.dataset;
            const note = document.getElementById('note').value;
            wsSendVal('$', option, el.value, note);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('select.note-set'))
    .map(el => {
        el.onchange = () => {
            const { option } = el.dataset;
            const note = document.getElementById('note').value;
            wsSendVal('$', option, el.value, note);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('#set-pattern td'))
    .map(el => {
        const input = el.querySelector('input');
        input.onclick = (e) => e.stopPropagation();
        el.onclick = () => {
            input.checked = !input.checked;
        }
        input.onchange = () => {
            const { step } = input.dataset;
            if (document.getElementById('auto-send').checked) {
                sendStepPattern(step);
            }
        }
    });

document.getElementById('send-pattern').onclick = () => {
    for (let step = 0; step < 16; step++) {
        sendStepPattern(step);
    }
};

function sendStepPattern(step) {
    const val = Array.prototype.slice
        .call(document.querySelectorAll(`#set-pattern input[data-step="${step}"]`))
        .map(({ checked }, index) => checked ? Math.pow(2, index) : 0)
        .reduce((a, b) => a + b);
    wsSendVal('%', step, val);
}






console.log('yo midi');

// if (!("requestMIDIAccess" in navigator)) {
//     console.log(`<h1>:-/</h1><p>I'm sorry, but your browser does not support the WebMIDI API ☹️🚫🎹</p>`);
// }

// navigator.requestMIDIAccess()
//     .then((access) => {

//         console.log('access', access);

//         access.onstatechange = function (event) {
//             console.log("MIDIConnectionEvent on port", event);
//             if (event.port.type === "input" && event.port.connection === "open") {
//                 onMIDIConect(access);
//             }
//         }

//                 // Get lists of available MIDI controllers
//                 const inputs = access.inputs;
//                 const outputs = access.outputs;

//                 inputs.forEach((midiInput) => {
//                     console.log(`FOUND in: ${midiInput.name}`);
//                     midiInput.onmidimessage = function (message) {
//                         console.log(`# ${midiInput.name}
//           ${new Date()}
//           ==================================
//           - Status: ${message.data[0]}
//           - Data 1: ${message.data[1]}
//           - Data 2: ${message.data[2]}
//           ==================================\n\n`);
//                     }
//                 })

//         //         outputs.forEach((midiOutput) => {
//         //             console.log(`FOUND out: ${midiOutput.name}`);
//         //         })

//     });

// function onMIDIConect(midi) {
// console.log('midi connected');
//     for (let input of midi.inputs.values()) {
//         console.log("Input id:", input.id, input);
//         input.onmidimessage = function (event) {
//             var midiMessage = MIDIMessage(event);
//             console.log("Parsed", midiMessage);
//         }
//     }

//     for (let output of midi.outputs.values()) {
//         console.log("Output id:", output.id, output);
//     }
// }


// var midi = null;  // global MIDIAccess object
// var output = null;

// function echoMIDIMessage(event) {
//     console.log('midi', event);
//     if (output) {
//         output.send(event.data, event.timestamp);
//     }
// }

// function onMIDISuccess(midiAccess) {
//     console.log("MIDI ready!", midiAccess);
//     midiAccess.inputs.forEach((midiInput) => {
//         console.log('midiInput', midiInput);
//         midiInput.onmidimessage = echoMIDIMessage;
//     });
//     midiAccess.outputs.forEach(async (midiOutput) => {
//         setTimeout(() => {
//             midiOutput.send('hello').then(() => console.log('sent'))
//             .catch(console.warn);
//         }, 2000);

//         console.log('midiOutput', midiOutput);
//     });
// }

// function onMIDIFailure(msg) {
//     console.log("Failed to get MIDI access - " + msg);
// }

// navigator.requestMIDIAccess({
//     sysex: true // this defaults to 'false' and we won't be covering sysex in this article. 
// }).then(onMIDISuccess, onMIDIFailure);



var midi, data;
// request MIDI access
if (navigator.requestMIDIAccess) {
    navigator.requestMIDIAccess({
        sysex: true
    }).then(onMIDISuccess, onMIDIFailure);
} else {
    alert("No MIDI support in your browser.");
}

// midi functions
function onMIDISuccess(midiAccess) {
    // when we get a succesful response, run this code
    midi = midiAccess; // this is our raw MIDI data, inputs, outputs, and sysex status

    var inputs = midi.inputs.values();
    // loop over all available inputs and listen for any MIDI input
    for (var input = inputs.next(); input && !input.done; input = inputs.next()) {
        console.log('input', input);
        // each time there is a midi message call the onMIDIMessage function
        input.value.onmidimessage = onMIDIMessage;
    }
}

function onMIDIFailure(error) {
    // when we get a failed response, run this code
    console.log("No access to MIDI devices or your browser doesn't support WebMIDI API. Please use WebMIDIAPIShim " + error);
}

function onMIDIMessage(message) {
    data = message.data; // this gives us our [command/channel, note, velocity] data.
    console.log('MIDI data', data); // MIDI data [144, 63, 73]
}
