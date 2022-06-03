import {addAlert, resolveAlert, isResolved} from App;

const http = require('http');


// Specify the port and IP our server will listen to
const port = 8000;
const host = '0.0.0.0';

// A wrapper function for handling all requests from the clients.
const requestHandler = function (request, response) {
    // For queries, check the corresponding alert.
    if (request.method === "GET") {
        
        let unparsedID = request.url;
        
        if (unparsedID.startsWith("/?id=")) {
            // Handle the query with the sensor's ID.
            queryHandler(response, unparsedID.slice("/?id=".length));
        } else {
            response.writeHead(200);
            response.end();
        }
    // For alerts, update the GUI.
    } else if (request.method === "POST") {
        alertHandler(request, response);
    }
};

// A function for handling alerts from the clients
const alertHandler = function (request, response) {
    // Get the parameters from the request datastream
    let data = '';
    request.on('data', chunk => {
        data += chunk;
    });
    request.on('end', () => {
        params = JSON.parse(data);
        if (params.resolved) {
            addAlert(params.location, params.waterHeight, params.ID);
        } else {
            resolveAlert(params.ID);
        }
        response.writeHead(200);
        response.end();
    });
};

// A function for handling "Was alert resolved?" queries
const queryHandler = function (response, ID) {
    response.writeHead(200);
    response.end(isResolved(ID).toString());
};

const server = http.createServer(requestHandler);
server.listen(port, host, () => {
    console.log(`Server listening on http://${host}:${port}`);
});