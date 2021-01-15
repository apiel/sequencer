const ws = new WebSocket(`ws://${window.location.host}/ws`, 'protocolOne');
ws.onopen = function () {
    ws.send("Here's some text that the server is urgently awaiting!");
};
ws.onmessage = function (event) {
    console.log('ws:', event.data);
}

function wsSendVal(category, key, val, option = '') {
    fnKey = String(key).padStart(2, '0');
    const valStr = String(Math.abs(val)).padStart(4, '0');
    const sign = val < 0 ? '-' : '+';
    const msg = `${category}${fnKey}${sign}${valStr}${option}`;
    console.log('msg:', msg);
    ws.send(msg);
}

Array.prototype.slice
    .call(document.querySelectorAll('button.base-ctrl'))
    .map(el => {
        el.onclick = () => {
            const { val, key } = el.dataset;
            wsSendVal('#', key, val);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('input.base-ctrl'))
    .map(el => {
        el.onchange = () => {
            const { key } = el.dataset;
            wsSendVal('#', key, el.value);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('input.note-set'))
    .map(el => {
        el.onchange = () => {
            const { option } = el.dataset;
            const note = document.getElementById('note').value;
            wsSendVal('$', option, el.value, note);
        }
    });

Array.prototype.slice
    .call(document.querySelectorAll('select.note-set'))
    .map(el => {
        el.onchange = () => {
            const { option } = el.dataset;
            const note = document.getElementById('note').value;
            wsSendVal('$', option, el.value, note);
        }
    });
