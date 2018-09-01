import React, { Component } from 'react';
import logo from '../logo.svg';
import './App.css';
import {firebaseApp} from '../firebase';
import {Link} from 'react-router';

console.log('signup');
class SignUp extends Component {
  constructor(props) {
    super(props);
    this.state={
      email: '',
      passwod: '',
      error: {
        message: ''
      }
    }
  }
  signUp() {
    const {email,password}=this.state;
    firebaseApp.auth().createUserWithEmailAndPassword(email,password)
    .catch(error => {
        this.setState({error})
    });
    console.log('signup error',this.state.error.message);
  }
  render() {
    return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h1 className="App-title">SignUp</h1>
        </header>
        <p className="App-intro">
          To get started, edit <code>src/App.js</code> and save to reload.
        </p>
        <form className="form-inline">
          <input type="text" placeholder="Enter Email"
            onChange={
              event=>this.setState({email:event.target.value})
            }
          />
          <input type="password" placeholder="Enter Password"
            onChange={
              event=>this.setState({password:event.target.value})
            }
          />
          <button type="button" className="btn btn-primary" onClick={
            ()=>this.signUp()
          }>SignUp</button>
        </form>
        <div>{this.state.error.message}</div>
        <Link to={'/signin'}>SignIn</Link>
      </div>
    );
  }
}

export default SignUp;
