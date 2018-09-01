import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './components/App';
import Default from './components/Default';
import SignIn from './components/SignIn';
import SignUp from './components/SignUp';
//import registerServiceWorker from './registerServiceWorker';
import {Router, Route, browserHistory} from 'react-router';
import {firebaseApp} from './firebase';

import {Provider} from 'react-redux';
import {createStore} from 'redux';
import {logUser} from './actions';
import reducer from './reducers';

console.log('index');
firebaseApp.auth().onAuthStateChanged(user => {
  if(user) {
    const {email} = user;
    store.dispatch(logUser(email));
    console.log("index user",user);
    browserHistory.push('/');
  }
  else {
    console.log("index ! user");
    browserHistory.replace('/signin');
  }
});

const store= createStore(reducer);
ReactDOM.render(
  <Provider store={store}>
    <Router path="/" history={browserHistory}>
      <Route path="/" component={App}/>
      <Route path="/signin" component={SignIn}/>
      <Route path="/signup" component={SignUp}/>
      <Route path="/*" component={Default}/>
    </Router>
  </Provider>
  ,
  document.getElementById('root')
);
//registerServiceWorker();
