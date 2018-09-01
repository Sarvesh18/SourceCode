import React, { Component } from 'react';
import {Link} from 'react-router-dom';
//import {firebaseApp} from '../firebase';

class Signout extends Component {
  constructor(props) {
    super(props);
    console.log('SignOut props',props);
  }
  render() {
    return (
      <div>        
        {console.log('Signout')}
        <h3>Please SignIn or SignUp!</h3>
        <Link to={'/signin'}>SignIn</Link><br/>
        <Link to={'/signup'}>SignUp</Link>
      </div>
      );
    }
  }
  export default Signout;
