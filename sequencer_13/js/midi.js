const easymidi = require('easymidi');
// const { write } = require('./serial');
const { write } = require('./serial');

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
    data = data.map((c) => String.fromCharCode(c));
    const msg = `:${data.join('')}`;
    console.log(`write ${JSON.stringify(data)}:`, msg);
    write(msg + '\n');
}
