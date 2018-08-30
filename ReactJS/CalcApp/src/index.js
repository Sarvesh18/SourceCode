import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
//import App from './App';
import {Provider} from 'react-redux';
import {createStore} from 'redux';
import View from './components/View';
import reducer from './reducers/index';
//import registerServiceWorker from './registerServiceWorker';

const store= createStore(reducer);
ReactDOM.render(
  <Provider store={store}>
    <View />
  </Provider>, document.getElementById('root')
);
//registerServiceWorker();
