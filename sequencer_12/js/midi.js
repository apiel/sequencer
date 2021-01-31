const easymidi = require('easymidi');
const WebSocket = require('ws');

const inputs = easymidi.getInputs();

console.log('inputs', inputs);

// const input = new easymidi.Input('X-TOUCH MINI:X-TOUCH MINI MIDI 1 24:0');
const input = new easymidi.Input(inputs[1]);

input.on('message', ({ controller, value, _type, note }) => {
    if (_type === 'cc') {
        // console.log('knob:', JSON.stringify({ controller, value }));
        wsSend([186, controller, value]);
    } else if (_type === 'noteon') {
        // console.log('noteon:', note);
        wsSend([154, note, 0]);
    } else if (_type === 'noteoff') {
        // console.log('noteoff:', note);
        wsSend([138, note, 0]);
    }
});

let ws;
let wsIsConnected = false;

function wsSend(data) {
    if (wsIsConnected) {
        data = data.map((c) => String.fromCharCode(c));
        const msg = `:${data.join('')}`;
        console.log(`msg ${JSON.stringify(data)}:`, msg);
        ws.send(msg);
    }
}

function wsConnect() {
    console.log('WS init connection');
    ws = new WebSocket('ws://192.168.0.24/ws', {
        perMessageDeflate: false,
    });

    ws.on('open', function open() {
        console.log('WS connection open');
        wsIsConnected = true;
    });

    ws.on('message', function incoming(data) {
        console.log('WS msg received:', data);
    });

    ws.on('close', function() {
        console.log('socket close');
        wsIsConnected = false;
        setTimeout(wsConnect, 1000);
    });
}

wsConnect();
