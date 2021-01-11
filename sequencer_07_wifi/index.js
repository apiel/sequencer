console.log('hello world js');

const ws = new WebSocket("/ws", "protocolOne");
ws.onopen = function (event) {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

