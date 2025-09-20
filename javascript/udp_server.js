const dgram = require('dgram');

/* Quote processing */
quoteList = [
    "The only way to do great work is to love what you do. - Steve Jobs",
    "Life is what happens when you're busy making other plans. - John Lennon",
    "The purpose of our lives is to be happy. - Dalai Lama",
    "Get busy living or get busy dying. - Stephen King",
    "You have within you right now, everything you need to deal with whatever the world can throw at you. - Brian Tracy"
];

function getQuote() {
    const index = Math.floor(Math.random() * quoteList.length);
    return quoteList[index];
}

function todayKey(d = new Date()) {
    return String(d.getDate()).padStart(2, '0');
}

// 起動時に当日の名言を決めて保持
let lastDate = todayKey();
let currentQuote = getQuote();

function getDailyQuote() {
    const today =  todayKey();

    if (today !== lastDate) {
        lastDateKey = todayKeyStr;
        currentQuote = getQuote();
    }

    return currentQuote + "\n";
}

/* Server processing */
const server = dgram.createSocket('udp4');

server.on('listening', () => {
    const address = server.address();
    console.log(`server listening ${address.address}:${address.port}`);
});

server.on('message', (msg, rinfo) => {
    quote = getDailyQuote();

    console.log(`server got: ${msg} from ${rinfo.address}:${rinfo.port}`);
    server.send(quote, rinfo.port, rinfo.address, (err) => {
        if (err) {
            console.log(`server error:\n${err.stack}`);
        }
    });
});

server.on('error', (err) => {
    console.log(`server error:\n${err.stack}`);
    server.close();
});

server.on('close', () => {
    console.log('server closed');
});

server.bind(17);
