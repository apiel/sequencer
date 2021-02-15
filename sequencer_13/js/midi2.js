const SerialPort = require('serialport');
const easymidi = require('easymidi');

const createPort = () => {
    const port = new SerialPort('/dev/ttyUSB0', {
        baudRate: 115200,
        dataBits: 8,
        parity: 'none',
        stopBits: 1,
    });

    port.on('error', (err) => {
        console.error('Error', err);
        // process.exit(1);
    });

    port.on('close', (err) => {
        console.log('Closed', err);
        // process.exit(err ? 1 : 0);
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

    let msg;
    setInterval(() => {
        if (msg) {
            port.write(msg);
            msg = null;
        }
    }, 10);

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

        function send(data) {
            if (port.isOpen) {
                data = data.map((c) => String.fromCharCode(c));
                msg = `:${data.join('')}`;
                console.log(`write ${JSON.stringify(data)}:`, msg);
            }
        }
    });
};

createPort();
