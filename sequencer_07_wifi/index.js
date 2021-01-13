const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function () {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

function wsSendVal(el, val) {
    const { key } = el.dataset;
    fnKey = String(key).padStart(2, '0');
    const valStr = String(Math.abs(val)).padStart(4, '0');
    const sign = val < 0 ? '-' : '+';
    const msg = `#${fnKey}${sign}${valStr}`;
    console.log('msg:', msg);
    ws.send(msg);
}

Array.prototype.slice
    .call(document.querySelectorAll('button'))
    .map(el => {
        el.onclick = () => {
            const { val } = el.dataset;
            wsSendVal(el, val);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('input'))
    .map(el => {
        el.onchange = () => {
            wsSendVal(el, el.value);
        }
    });
