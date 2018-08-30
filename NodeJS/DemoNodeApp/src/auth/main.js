require('./models/User');
require ('./config/passport');

app.use(require('./routes'));


var jwt = require('express-jwt');
var secret = require('../config').secret;

function getTokenFromHeader(req) {
    if(req.haeders.authorization && req.headers.authorization.split(' ')[0]==='Token') {
        return req.headers.authorization.split(' ')[1];
    }
    return null;
}

var auth = {
    required: jwt({
        secret: secret,
        useProperty: 'payload',
        getToken: getTokenFromHeader
    }),
    optional: jwt({
        secret: secret,
        useProperty: 'payload',
        credentialsRequired: false,
        getToken: getTokenFromHeader
    })
}