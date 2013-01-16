var http = require('http')
, url = require('url')
, fs = require('fs')
, server;

server = http.createServer(function(req, res) {
  // your normal server code
  var path = url.parse(req.url).pathname;
  switch (path){
    case '/':
      res.writeHead(200, {'Content-Type': 'text/html'});
			res.write('<h1> <a href="/simple.html">Simple Control</a></h1>');
      res.write('<h1> <a href="/GUI.html">Maps GUI</a></h1>');
	
      res.end();
      break;
    case '/GUI.html':
      fs.readFile(__dirname + path, function(err, data){
        if (err) return send404(res);
        res.writeHead(200, {'Content-Type': path == 'json.js' ? 'text/javascript' : 'text/html'})
        res.write(data, 'utf8');
        res.end();
      });
      break;
    case '/simple.html':
      fs.readFile(__dirname + path, function(err, data){
        if (err) return send404(res);
        res.writeHead(200, {'Content-Type': path == 'json.js' ? 'text/javascript' : 'text/html'})
        res.write(data, 'utf8');
        res.end();
      });
      break;

    default: send404(res);
  }
}),

send404 = function(res){
  res.writeHead(404);
  res.write('404');
  res.end();
};

server.listen(8081);

// socket.io, I choose you
var io = require('socket.io').listen(server);

// on a 'connection' event
io.sockets.on('connection', function(socket){

  console.log("Connection " + socket.id + " accepted.");
  var coords = "";
	//clear out anything that was in the output file
	fs.writeFile('./inst.txt', "" ,'ASCII', function(err, data) {
            if(err) throw err;  
        });
  // now that we have our connected 'socket' object, we can
  // define its event handlers
  socket.on('message', function(message){
        console.log("Received message: " + message + " - from client " + socket.id);
	fs.writeFile('./inst.txt', message,'ASCII', function(err, data) {
            if(err) throw err;  
        });
  });

	socket.on('coordinate', function(coord){
        console.log("Received coordinate: " + coord + " - from client " + socket.id);
		coords = coords + coord + "\n";
  });
   
	socket.on('doneCoords', function(){
        console.log("Received message: " + coords + " - from client " + socket.id);
	fs.writeFile('./inst.txt', coords ,'ASCII', function(err, data) {
            if(err) throw err;  
        });
	coords = "";
  });

  socket.on('disconnect', function(){
    console.log("Connection " + socket.id + " terminated.");
  });
   
});
