const easymidi = require('easymidi');
// const SerialPort = require('serialport');
const SerialPort = require('@serialport/stream');
SerialPort.Binding = require('@serialport/bindings');
const port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 115200,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
});

// function openPort() {
//     port.open((err) => {
//         err && console.log('Open error: ', err.message);
//     });
// }

port.on('error', function (err) {
    console.log('Error: ', err.message);
});

let buffer = '';
port.on('data', (data) => {
    process.stdout.write(data.toString());
    buffer += data.toString();
    // if (buffer.includes('POWERON_RESET')) {
    if (buffer.includes('download')) {
        port.close();
        console.log('port close');
    } else if (buffer.includes('\n')) {
        buffer = '';
    }
});

const inputs = easymidi.getInputs();

console.log('inputs', inputs);

// const input = new easymidi.Input('X-TOUCH MINI:X-TOUCH MINI MIDI 1 24:0');
const input = new easymidi.Input(inputs[1]);

// ToDo: avoid midi convertion...
input.on('message', ({ controller, value, _type, note }) => {
    if (_type === 'cc') {
        // console.log('knob:', JSON.stringify({ controller, value }));
        send([186, controller, value]);
    } else if (_type === 'noteon') {
        // console.log('noteon:', note);
        send([154, note, 0]);
    } else if (_type === 'noteoff') {
        // console.log('noteoff:', note);
        send([138, note, 0]);
    }
});

function send(data) {
    if (port.isOpen) {
        data = data.map((c) => String.fromCharCode(c));
        const msg = `:${data.join('')}`;
        console.log(`write ${JSON.stringify(data)}:`, msg);
        port.write(msg + '\n');
        // port.write(Buffer.from(msg + "\n", 'ascii'));
    }
}
