console.log('hello world js');

const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function (event) {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

// play: ws.send(0xFA);

