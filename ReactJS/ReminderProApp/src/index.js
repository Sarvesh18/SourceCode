import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './components/App';
import  {Provider} from 'react-redux';
import {createStore} from 'redux';
import reducer from './reducers';
const store=createStore(reducer);
//import registerServiceWorker from './registerServiceWorker';

ReactDOM.render(
  <Provider store={store}>
    <App />
  </Provider>, document.getElementById('root')
);
//registerServiceWorker();
