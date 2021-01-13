console.log('hello world js');

const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function (event) {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

document.getElementById('ctrl-play').onclick = () => ws.send(0xFA);
document.getElementById('ctrl-stop').onclick = () => ws.send(0xFC);
document.getElementById('ctrl-mute').onclick = () => ws.send(0xF1);
document.getElementById('ctrl-unmute').onclick = () => ws.send(0xF0);
