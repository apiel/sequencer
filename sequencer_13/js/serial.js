const SerialPort = require('serialport');
const port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 115200,
    // dataBits: 8,
    // parity: 'none',
    // stopBits: 1,
});

function open() {
    return new Promise((resolve, reject) => {
        port.open((err) => (err ? reject(err) : resolve(true)));
    });
}

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


let msg;
setInterval(() => {
    if (msg) {
        port.write(msg);
        msg = null;
    }
}, 10);

async function write(data) {
    if (port.isOpen || (await open())) {
        // port.write(data);
        msg = data;
    }
}

module.exports = {
    write,
};
