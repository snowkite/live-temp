var express = require('express');
var path = require('path');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var serialport = require('serialport');
var http = require('http');

var app = express();
var server = http.createServer(app);
var io = require('socket.io')(server);

server.listen(80);

var SerialPort = serialport.SerialPort;
var portName = process.argv[2];//dev/ttyACM0
var br = process.argv[3];//115200
console.log(portName);
var myPort = new SerialPort(portName, {
	baudrate: br,
	parser: serialport.parsers.readline("\n")
}, false);

myPort.open(function(err) {

function onOpen() {
	console.log("open connection");
}
});

io.on('connection', function (socket) {
	socket.emit('news', {hello: 'world'});
	socket.on('my other event', function (data) {
		console.log(data);
	});
	myPort.on('data', function (msg) {
		console.log("on Data " + msg);
		socket.emit('msg', msg);
	});
});

app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(cookieParser());
app.use(require('less-middleware')(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/aj', routes);
app.use('/users', users);

app.use(function (req, res, next) {
	var err = new Error('Not Found');
	err.status = 404;
	next(err);
});

if (app.get('env') === 'development') {
	app.use(function (err, req, res, next) {
		res.status(err.status || 500);
		res.render('error', {
			message: err.message,
			error: err
		});
	});
}

app.use(function (err, req, res, next) {
	res.status(err.status || 500);
	res.render('error', {
		message: err.message,
		error: {}
	});
});


module.exports = app;
