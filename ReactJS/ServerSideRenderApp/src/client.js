import React from "react";
import ReactDOM from "react-dom";
import App from "./components/App.jsx";
//import {createStore} from "redux";
//import {Provider} from "react-redux";
//import reducer from "./reducers/index";

//const preloadedstate= window.__PRELOADED_STATE__;
//delete window.__PRELOADED_STATE__;
//const store =createStore(reducer,preloadedState);

ReactDOM.hydrate (
    //<Provider store={store}>
        <App />
    //</Provider>
    ,document.getElementById("root")
);