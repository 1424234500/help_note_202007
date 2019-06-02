
var server = require('http').createServer();
var io = require('socket.io')(server);
io.on('connection', function(client){
  console.log('connected');
  //when get data on message
  client.on('message', function(obj){
	  console.log("get message and return to client...");
	  io.emit('message', {'a':'messagetest'});
	  console.log("login backed...");
  });
  // when get data on login
  client.on('login', function(obj){
	  console.log("get login data and return to client...");
	  io.emit('login', {'a':'logintest'});
	  console.log("login backed...");
  });
  client.on('event', function(data){});
  client.on('disconnect', function(){
    console.log('client disconnected');
  });
});
console.log("server started on port 8087");
server.listen(8087);



