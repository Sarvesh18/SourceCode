//var express = require('express');
import express from "express";
import cors from "cors";
import path from "path";

import React from "react";
import {renderToString} from "react-dom/server";
import App from "./components/App.jsx";

/*
import {createStore} from "redux";
import {Provider} from "react-redux";
import reducer from "./reducers";
*/

const app=express();

//app.use(bodyParser.json());
//app.use(bodyParser.text());
app.use(cors());
app.use(express.static('dist'));
//app.use(handleRender);

/*
function handleRender(req,res) {
    const store = createStore(reducer);
    const html = renderToString(
        <Provider store={store}>
            <App />
        </Provider>        
    )
    const preloadedState = store.getState();
    res.send(renderFullPage(html,preloadedState))
}

function renderFullPage(html, preloadedState) {
    return `
        <!doctype html>
        <html>
        <head>
            <title>Redux Universal Example</title>
        </head>
        <body>
            <div id="root">${html}</div>
            <script>
            // WARNING: See the following for security issues around embedding JSON in HTML:
            // http://redux.js.org/recipes/ServerRendering.html#security-considerations
            //window.__PRELOADED_STATE__ = ${JSON.stringify(preloadedState).replace(/</g, '\\u003c')}
            </script>
            <script src="/static/bundle.js"></script>
        </body>
        </html>
    `;
    
}
*/

/*
app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});
*/
app.get("*",(req,res,next) => {
    const jsx=(<App />);
    const reactDom=renderToString(jsx);
    console.log(reactDom);
    //res.writeHead(200,{"Content-Type":"text/html"});
    res.send(htmlTemplate(reactDom));
});
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
const port = 8090; 
app.listen(port, () => {
    console.log("Server Port:",`${port}`);
});

function htmlTemplate (reactDom) {
    return `
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link rel="stylesheet" type="text/css" href="/style.css">
            <title>
                ReactJS
            </title>
        </head> 
        <body>
            <div id="root">${reactDom}</div>
            <script src="/bundle.js"></script>
        </body>
        </html>
    `;
}