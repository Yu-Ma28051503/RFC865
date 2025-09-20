const net = require('net');

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
const server = net.createServer((socket) => {
    console.log('Client connected');
    console.log('Remote address:', socket.remoteAddress);
    socket.write(getDailyQuote());
    socket.end();

    socket.on('close', () => {
        console.log('Connection closed');
    });
});

server.listen(17, '127.0.0.1', () => {
    console.log('Server listening on port 17');
});

server.on('error', (err) => {
    throw err;
});
