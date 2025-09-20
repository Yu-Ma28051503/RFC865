const dgram = require('dgram');
const client = dgram.createSocket('udp4');

client.send('', 17, 'localhost', (err) => {
    if (err) {
        console.log(`client error:\n${err.stack}`);
    }
});

client.on('message', (msg, rinfo) => {
    console.log(msg.toString());
    client.close();
});

client.on('error', (err) => {
    console.log(`client error:\n${err.stack}`);
    client.close();
});

client.on('close', () => {
    console.log('client closed');
});
