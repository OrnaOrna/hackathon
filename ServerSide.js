const http = require('http');

const port = process.env.PORT || 3000;

const server = http.createServer((request, response) => {
    response.statusCode = 200;
    response.setHeader
});

class Alert {
    constructor(location, waterHeight, ID, resolved) {
        this.location = location;
        this.waterHeight = waterHeight;
        this.ID = ID;
        this.resolved = resolved;
    }
}