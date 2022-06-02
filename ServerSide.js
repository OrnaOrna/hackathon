const http = require('http');


// Specify the port and IP our server will listen to
const port = 8000;
const host = '0.0.0.0';

// A wrapper function for handling all requests from the clients.
const requestHandler = function (request, response) {
    if (request.method === "GET") {
        console.log(request.url);
        queryHandler(response, "");

    } else if (request.method === "POST") {
        alertHandler(response);

    }
    response.writeHead(200);
    response.end();
};

// A function for handling alerts from the clients
const alertHandler = function (response) {

};

// A function for handling "Was alert resolved?" queries
const queryHandler = function (response, ID) {

};

const server = http.createServer(requestHandler);
server.listen(port, host, () => {
    console.log(`Server listening on http://${host}:${port}`);
});

class Alert {
    constructor(location, waterHeight, ID, resolved) {
        this.location = location;
        this.waterHeight = waterHeight;
        this.ID = ID;
        this.resolved = resolved;
    }
}