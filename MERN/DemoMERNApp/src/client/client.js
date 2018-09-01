import React from "react";
import ReactDOM from "react-dom";
import App from "../jsx/App.jsx";
import Sign from '../jsx/Sign.jsx';

import {BrowserRouter} from "react-router-dom";
//import {firebaseApp} from './firebase';
/*
firebaseApp.auth().onAuthStateChanged (
  user=>{
    if(user) {
      console.log('user');
      browserHistory.replace('/app');

    }
    else {
      console.log('!user');
      browserHistory.replace('/signin');
    }
  }
)
*/
/*
export const Context = React.createContext({
  status: false,
  toggleStatus: () => {
    status ? console.log('true') : console.log('false') 
  }
});
<Context.Provider>
</Context.Provider>
*/

ReactDOM.hydrate (

  <BrowserRouter>
      <App auth={window.__preloaded__}/>
  </BrowserRouter>

  ,document.getElementById("root")
);