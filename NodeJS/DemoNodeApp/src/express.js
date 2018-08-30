var express = require('express');
var dotenv = require('dotenv').config(); //({path:''})

var app = express();
var nodemailer = require('nodemailer');


var transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
      user: 'sarvesh.smcs2@gmail.com',
      pass: 'xxxxxxxxxxxxxxxxxxxxxxx'
    }
});
  
var mailOptions = {
    from: 'Sarvesh Singh',
    to: 'sarvesh.singh@daffodilsw.com , sarvesh.singh18@hotmail.com',
    subject: 'Sending Email using Node.js',
    //text: 'That was easy!'
    html: '<h1>Welcome</h1><p>That was easy!</p>'
};

var schedule = require('node-schedule');

var date = new Date(2018, 7, 20, 15, 47, 0);

var task = schedule.scheduleJob(date, function(){
    //console.log('');
    transporter.sendMail(mailOptions, function(error, info){
    if (error) {
        console.log(error);
    } else {
        console.log('Email sent: ' + info.response);
    }
    });
});

app.get('/', function(req, res){
   res.send("Hello world!");
});

var PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log('Port: ',PORT);
});