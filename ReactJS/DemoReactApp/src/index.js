import React from 'react';
import ReactDOM from 'react-dom';
import App from './jsx/App.jsx';
import reducer from './reducer';

import {BrowserRouter} from "react-router-dom";
import {Provider} from 'react-redux';
import {createStore, applyMiddleware} from "redux";
import thunk from 'redux-thunk';1

const store = createStore(reducer,applyMiddleware(thunk)); 

console.log('getState()',store.getState());
ReactDOM.render(
    <Provider store={store}>
        <BrowserRouter>
            <App />
        </BrowserRouter>
    </Provider>
    ,document.getElementById('root')
);

