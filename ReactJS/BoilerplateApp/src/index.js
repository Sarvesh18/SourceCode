import React from 'react';
import ReactDom from 'react-dom';
import style from './style/style.css';
//import App from './App';

const App = () => {
    return <div className={ style.App }>ReactJS</div>;
} 

ReactDom.render (
    <App />,document.getElementById("root")
);