import promise from 'promise';
import express from "express";
import cors from "cors";
import path from "path";
import bodyParser from "body-parser";
import cookieParser from 'cookie-parser';
import session from 'express-session';

import 'isomorphic-fetch';

import React from "react";
import {renderToString} from "react-dom/server";
import { StaticRouter } from 'react-router';
import App from "../jsx/App.jsx";
//import Sign from '../jsx/Sign.jsx';

const app=express();

app.use(bodyParser.json());

app.use(bodyParser.text());

app.use(cors());

app.use(express.static('dist'));

app.use(cookieParser());

app.use(session({
    secret: 'someRandomSecretValue',
    cookie: { maxAge: 1000 * 60 * 60 * 24 * 30 },//Millisec
    saveUninitialized: true
}));
 

let signin = {
    "user": [
        {"email":"user1", "pass":"pass1"},
        {"email":"user2", "pass":"pass2"}
    ]
}

app.get('/check-login', function (req, res) {
    if (req.session && req.session.auth && req.session.auth.username) {
        res.send('You are logged in:' + req.session.auth.username.toString());
    }
    else {                  
        res.send('You are ! logged in');
    }
 });

app.get('/session', function (req, res) {
    req.session.auth= {username: 'sarvesh'};
    res.send('Session');
});
 app.get('/logout', function (req, res) {
     delete req.session.auth;
     res.send('Logout');
 });

app.post('/signup',function(req,res,next) {
    var request=req.body;
    console.log('signup',request.email);
    console.log('signup',request.password);
    try {
      signin.user.push({"email":request.email, "pass":request.password});
      //res.json(respond);
      req.session.auth = {username: request.email};
      res.status(200).send('Account Created');
    }
    catch(err) {
      res.status(500).send('Something Went Wrong');
    }
});

app.post('/signin',function(req,res) {
    var request=req.body;
    console.log('signin',request.email);
    console.log('signin',request.password);
    var response='Something Went Wrong';
    var promise= new Promise((resolve,reject) => {
        //throw new Error('Error1');
        let flag=-1;
        for (let i=0; i<signin.user.length;i++) {
            if(signin.user[i].email==request.email) //&& signin.user[i].pass==requst.password
            {
              flag=i;
              break;
            }
        }
        console.log('flag',flag);
        if(flag > -1 ) {
          console.log('if')
          resolve(flag);
        }
        else {
          console.log('else');
          response='Email ! Exist';
          reject(false);
        }
    })
    .then(check=> {
      console.log('check1');
      if( signin.user[check].pass==request.password)
      {
        console.log('check1 if');
        response='Signin Successful';
        req.session.auth = {username: request.email};
        res.send(response);
        return true;
      }
      response='Password ! Match';
      throw new Error('Error');
    })
    .catch(err => {
        console.log('catch',err);
        res.send(response);
    });
});

//Promise on '/get'
app.get('/get',function(req,res) {
    var request=req.query;
    console.log('get',request);

    var promise= new Promise((resolve,reject) => {
        //throw new Error('Error1');
        var val1=true;
        if(val1) {
          console.log('val1',val1);
          resolve(1);
          console.log('val1',val1);
          //res.send('val1');
        }
        else {
          console.log('err');
          reject(Error('Error Msg'));
          //res.send('Error Msg');
        }
    })
    .then(val2=> {
      //throw new Error('Error2');
      console.log('val2',val2);
      val2=val2+1;
      //res.send('val2');
      console.log('val2',val2);
      return val2;
    })
    .then(val3=> {
      //throw new Error('Error3');
      console.log('val3',val3);
      val3=val3+1;
      console.log('val3',val3);
      res.send('Successfull');
      return val3;
    //},err =>{
      //console.log('err',err);
        //return err;
    })
    .catch(err => {
        console.log('err',err,'end');
        res.send('Error');
    });
    console.log('Promise',promise);
    var response = { "status":"ok", "code":300};
    //var myJSON = JSON.stringify(response);
    //res.send(myJSON);
    //res.json(response).end();
});


app.get("*",(req,res,next) => {
    let auth;
    if(req.session && req.session.auth && req.session.auth.username)
    {
        console.log(req.session.auth.username.toString());
        auth=true;        
    }
    else 
    {
        auth=false;
    }
    const context = {};
    //const jsx=(<App />);

    const reactDom=renderToString(
        <StaticRouter location={req.url} context={context}>
                <App auth={auth}/>
        </StaticRouter>
    )

    console.log('context.url',context.url);
    if (context.url) {
        res.redirect(301, context.url)
    } else {
        //console.log(reactDom);
        //res.writeHead(200,{"Content-Type":"text/html"});
        res.send(htmlTemplate(reactDom,auth));
    }
});

const port = 8090;
app.listen(port, () => {
    console.log("Server Port:",`${port}`);
});

function htmlTemplate (reactDom,auth) {
    return `
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
            <link rel="stylesheet" type="text/css" href="/style.css">
            <title>

                ReactJS
            </title>
            <script>window.__preloaded__=${auth}</script>
        </head>
        <body>
            <div id="root">${reactDom}</div>
            <script src="/bundle.js"></script>
        </body>
        </html>
    `;
}
/*
//Post Request
app.post('/signup', function (req, res) {
    var usernameS = req.body.usernameS;
    var passwordS = req.body.passwordS;
    var emailS = req.body.emailS;
	var salt = crypto.randomBytes(128).toString('hex');
	var dbString = hash(passwordS, salt);
    pool.query('INSERT INTO "user" (username, password, email) VALUES ($1, $2, $3)', [usernameS, dbString,  emailS], function(err, result) {
    if(err) {
        res.status(500).send(err.toString());
    }
    else {
        res.send('User Successfully Registered:');
    }
  });
});

//Post Request
app.post('/login', function (req, res) {
    var username = req.body.username;
    var password = req.body.password;
    pool.query('SELECT id, password FROM "user" WHERE username = $1', [username], function(err, result) {
    if(err) {
        res.status(500).send(err.toString());
    }
    else {
        if(result.rows.length === 0) {
            res.send(403).send('Username/Password is Invalid');
        }
        else {
           var dbString = result.rows[0].password;
           var salt = dbString.split('$')[2];
           var hashedPassword  = hash(password, salt);
           if(hashedPassword == dbString) {
            req.session.auth = {userId: result.rows[0].id};
            res.send('Credentials Correct!');
           }
           else {
            res.send(403).send('Username/Password is Invalid');
           }
        }
    }
   });
});
*/



/*
app.get('/index',function(req,res) {
    res.sendFile(path.join(__dirname, '/reactapp/public', 'index.html'));
});
app.get('/get',function(req,res) {
    var request=req.query;
    console.log('get',request);

    var obj = { "name":"get", "age":30, "city":"New York"};
    var myJSON = JSON.stringify(obj);
    res.send(myJSON);
});

app.get('/testget/:text',function(req,res) {
    var request=req.params.text;
    console.log('testget',request);

    var obj = { "name":"testget", "age":30, "city":"New York"};
    var myJSON = JSON.stringify(obj);
    res.send(myJSON);
});
app.post('/testpost',function(req,res) {
    var request=req.body;
    console.log('testpost',request);

    var obj = { "name":"testpost", "age":30, "city":"New York"};
    var myJSON = JSON.stringify(obj);
    res.send(myJSON);
});
app.post('/post',function(req,res) {
    var request=req.body;

    console.log('post',request);
    res.send('post');
});
*/
