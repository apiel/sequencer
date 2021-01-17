const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function () {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
};

function wsSendMidi(data) {
    data = [...data].map((c) => String.fromCharCode(c));
    const msg = `:${data.join('')}`;
    console.log('msg:', msg);
    ws.send(msg);
}

// request MIDI access
if (navigator.requestMIDIAccess) {
    navigator
        .requestMIDIAccess({
            //   sysex: true,
        })
        .then(onMIDISuccess, onMIDIFailure);
} else {
    alert('No MIDI support in your browser.');
}

function onMIDISuccess(midiAccess) {
    midiAccess.inputs.forEach((midiInput) => {
        console.log('midiInput', midiInput);
        midiInput.onmidimessage = onMIDIMessage;
    });
}

function onMIDIFailure(error) {
    console.error(
        "No access to MIDI devices or your browser doesn't support WebMIDI API. Please use WebMIDIAPIShim ",
        error,
    );
}

function onMIDIMessage({ data }) {
    console.log('MIDI data', data);
    wsSendMidi(data);
}
